#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include "src/rules.h"
#include "src/screen.h"
#include "src/loop.h"


// macros
#define WIDTH  60
#define HEIGHT 30
#define MAXBLOCKS 10000


static int ix, iy = 0;
static int game_over = 0;
static enum DIRECTION pre_move = D_UP;
volatile int points = 0;


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


void on_hit(void){ game_over = 1; }
void on_get(void){ points = points + 1; }


void gof(int score, char *format, ...){
	char message[1000];
	va_list aptr;
	int ret;
	va_start(aptr, format);
	ret = vsprintf(message, format, aptr);
	va_end(aptr);
	printf("Point%s: %i\n", points <= 1 ? "" : "s", points);
	printf("%s\n", message);
	nrm_termios();
	exit(0);
}


static int lvl = 1;
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

		switch((int)(points / 10) + 1){
			case 1: lvl = 1; game_speed = 200; break;
			case 2: lvl = 2; game_speed = 150; break;
			case 3: lvl = 3; game_speed = 100; break;
			case 4: lvl = 4; game_speed = 50; break;
			default: break;
		}

		struct BLOCK newb = {new_blocks[idx - 2].x, new_blocks[idx - 2].y, A_BODY, BODY_BLOCK};
		new_blocks[idx - 1] = newb;
		// get new point block and added into the stack
		int _max[2] = {WIDTH, HEIGHT};
		new_blocks[idx] = unique_block(new_blocks, _max, CHEE_BLOCK, A_POINT);
	}

	copy_blocks(blocks, new_blocks);  // save state
	pre_move = dir;

	// detect cross-over
	if(bock_corssed(new_blocks[0], blocks) != -1)
		gof(points, "You can't cross yourself");


	char h1[20];
	char h2[20];
	char *h3 = " [q]uit";
	sprintf(h1, " points: %i", points);
	sprintf(h2, " lvl: %i", lvl);
	char *headers[3] = { h1, h2, h3 };

	draw_frame(WIDTH, HEIGHT, new_blocks, on_hit, on_get, headers);

	
	if(kcode == 113)  // detect "q" and exit the game
		gof(points, "Quitting game");

	if(game_over)
		gof(points, "You can't cross frame");

}

int main(void){
	lvl = 1;
	loop_event(e_loop);
	return 0;
}

