#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "src/screen.h"
#include "src/loop.h"

// macros
#define WIDTH  60
#define HEIGHT 30

#define MAXBLOCKS 1000

// #define HEAD_BLOCK "\x1B[31m\x1B[0m"
// #define BODY_BLOCK "\x1B[32m\x1B[0m"
#define HEAD_BLOCK "\x1B[31m8\x1B[0m"
#define BODY_BLOCK "\x1B[32m0\x1B[0m"


static int ix, iy = 0;
static enum DIRECTION pre_move = D_UP;
int loopc;


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


static struct BLOCK blocks[MAXBLOCKS] = {
	{(int)(WIDTH / 2) - 2, (int)(HEIGHT / 2) - 2, A_HEAD, HEAD_BLOCK},
	{(int)(WIDTH / 2) - 2, (int)(HEIGHT / 2) - 1, A_BODY, BODY_BLOCK},
	{(int)(WIDTH / 2) - 2, (int)(HEIGHT / 2) - 0, A_BODY, BODY_BLOCK},
};

void e_loop(int kcode){
	ix = iy = 0;
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
		new_blocks[idx].x = blocks[idx - 1].x;
		new_blocks[idx].y = blocks[idx - 1].y;
	}
	copy_blocks(blocks, new_blocks);    // save state
	pre_move = dir;


	draw_frame(WIDTH, HEIGHT, new_blocks);

	printf("loop count: %i\n", loopc);

	++loopc;
	if(kcode == 113)  // detect "q" and exit the game
		exit(0);
}

int main(void){
	loopc = 0;
	loop_event(e_loop);
	return 0;
}

