#include <stdio.h>
#include <unistd.h>
#include "src/screen.c"
#include "src/loop.c"

// macros
#define WIDTH  60
#define HEIGHT 30

#define MAXBLOCKS 1000


int loopc;

int ix, iy = 0;


void e_loop(int kcode){

	char *text = "";
	char coord[100];
	switch(kcode){
		case -1: --iy; text = "UP"; break;
		case -2: ++iy; text = "DOWN"; break;
		case -3: ++ix; text = "RIGHT"; break;
		case -4: --ix; text = "LEFT"; break;
		default: break;
	}

	struct BLOCK blocks[MAXBLOCKS] = {
		{10, 10, 0},
	};

	blocks[0].x = blocks[0].x + ix;
	blocks[0].y = blocks[0].y + iy;

	sprintf(coord, "[%i, %i]", blocks[0].x, blocks[0].y);


	draw_frame(WIDTH, HEIGHT, blocks);
	printf("loop count: %i, coordinates: %s, movement: %s\n", loopc, coord, text);

	++loopc;
	if(kcode == 113)  // detect "q" and exit the game
		exit(0);
}

int main(void){
	loopc = 0;



	loop_event(e_loop);
	return 0;
}

