#include <stdio.h>
#include <unistd.h>
#include "src/screen.c"
#include "src/utils.c"
#include "src/loop.c"

// macros
#define WIDTH  60
#define HEIGHT 30



int loopc;

void e_loop(int kcode){
	draw_frame(WIDTH, HEIGHT);
	printf("loop count: %i, keyboard input char: %c\n", loopc, kcode);

	++loopc;
	if(kcode == 113)  // detect "q" and exit the game
		exit(0);
}

int main(void){
	loopc = 0;
	loop_event(e_loop);
	return 0;
}

