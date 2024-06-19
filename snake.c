#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "src/rules.h"
#include "src/screen.h"
#include "src/loop.h"

volatile int game_over = 0;

// macros
#define WIDTH  60
#define HEIGHT 30

#define MAXBLOCKS 1000

// #define HEAD_BLOCK "\x1B[31m\x1B[0m"
// #define BODY_BLOCK "\x1B[32m\x1B[0m"
#define HEAD_BLOCK "\x1B[31m8\x1B[0m"
#define BODY_BLOCK "\x1B[32m0\x1B[0m"

#define CHEE_BLOCK "\x1B[33m\x1B[0m"


// static int game_over = 0;
static int ix, iy = 0;
static enum DIRECTION pre_move = D_UP;
int loopc;
int points = 0;


void continuous(enum DIRECTION dir){
	int *out = malloc(2);
	ix = iy = 0;
	if(dir == D_UP)
		--iy;
	else if(dir == D_DOWN)
		++iy;
	else if(dir == D_RIGHT)
		++ix;
	else
		--ix;
}



void on_hit(void){
	init_termios();
	reset_termios();
	game_over = 1;
}
void on_get(void){ points = points + 1; }


static struct BLOCK blocks[MAXBLOCKS] = {
	{(int)(WIDTH / 2) - 2, (int)(HEIGHT / 2) - 2, A_HEAD, HEAD_BLOCK},
	{(int)(WIDTH / 2) - 2, (int)(HEIGHT / 2) - 1, A_BODY, BODY_BLOCK},
	{(int)(WIDTH / 2) - 2, (int)(HEIGHT / 2) - 0, A_BODY, BODY_BLOCK},
	
	{20, 20, A_POINT, CHEE_BLOCK},
};

void e_loop(int kcode){
	ix = iy = 0;
	char title[WIDTH];
	enum DIRECTION dir = NONE;

	switch(kcode){
		// Up
		case -1:{
			if(pre_move == D_DOWN){
				if(dir == NONE) dir = pre_move;
				continuous(dir);
				break;
			}
			--iy;
			dir = D_UP;
			break;
		}
		// Down
		case -2:{
			if(pre_move == D_UP){
				if(dir == NONE) dir = pre_move;
				continuous(dir);
				break;
			}
			++iy;
			dir = D_DOWN;
			break;
		}
		// Right
		case -3:{
			if(pre_move == D_LEFT){
				if(dir == NONE) dir = pre_move;
				continuous(dir);
				break;
			}
			++ix;
			dir = D_RIGHT;
			break;
		}
		// Left
		case -4:{
			if(pre_move == D_RIGHT){
				if(dir == NONE) dir = pre_move;
				continuous(dir);
				break;
			}
			--ix;
			dir = D_LEFT;
			break;
		}
		// continue
		default: {
			if(dir == NONE) dir = pre_move;
			continuous(dir);
			break;
		};
	}


	int idx;
	static struct BLOCK new_blocks[MAXBLOCKS];
	// continuous movement
	copy_blocks(new_blocks, blocks);
	new_blocks[0].x = blocks[0].x + ix;  // head x
	new_blocks[0].y = blocks[0].y + iy;  // head y
	for(idx = 1; blocks[idx].x; ++idx){
		if(new_blocks[idx].act == A_BODY){
			new_blocks[idx].x = blocks[idx - 1].x;
			new_blocks[idx].y = blocks[idx - 1].y;
		}
	}

	if(new_blocks[idx - 1].x == new_blocks[0].x && new_blocks[idx - 1].y == new_blocks[0].y){
		points++;
		// new_blocks[idx - 1].x = randint(1, WIDTH - 1);
		// new_blocks[idx - 1].y = randint(3, HEIGHT - 4);

		// new_blocks[idx - 1].x = randint(1, WIDTH - 1);
		// new_blocks[idx - 1].y = randint(3, HEIGHT - 4);

		// struct BLOCK newb = {(int)(WIDTH / 2) - 2, (int)(HEIGHT / 2) - 1, A_BODY, BODY_BLOCK};
		struct BLOCK newb = {new_blocks[idx - 2].x, new_blocks[idx - 2].y, A_BODY, BODY_BLOCK};


		int tx = randint(2, WIDTH - 2);
		int ty = randint(3, HEIGHT - 4);
		struct BLOCK newt = {tx, ty, A_POINT, CHEE_BLOCK};
		

		new_blocks[idx - 1] = newb;
		new_blocks[idx] = newt;

		// new_blocks[idx]
		// new_blocks[idx].x = randint(1, WIDTH - 2);
		// new_blocks[idx].y = randint(3, HEIGHT - 4);
	}

	copy_blocks(blocks, new_blocks);    // save state
	pre_move = dir;

	sprintf(title, "loop count: %i, points: %i", loopc, points);

	draw_frame(WIDTH, HEIGHT, new_blocks, on_hit, on_get, title);

	// printf("loop count: %i, points: %i\n", loopc, points);



	if(kcode == 113){  // detect "q" and exit the game
		init_termios();
		reset_termios();
		exit(0);
	}

	if(game_over){
		init_termios();
		reset_termios();
		exit(0);
	}

	++loopc;
}

int main(void){
	loopc = 0;
	loop_event(e_loop);
	return 0;
}

