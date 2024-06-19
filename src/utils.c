#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "structs.h"
 
// wait by milli seconds
void delay_ms(int ms){
	clock_t start_time = clock();
	while (clock() < start_time + (1000 * ms));
}


int contain_coord(int x, int y, struct BLOCK blocks[]){
	int i;
	for(i = 0; blocks[i].x; ++i){
		if(blocks[i].x - 1 == x && blocks[i].y == y){
			return i;
		}
	}
	return -1;
}

// copy array of blocks pr to se
void copy_blocks(struct BLOCK se[], struct BLOCK pa[]){
	int idx;
	for(idx = 0; pa[idx].x; ++idx){
		se[idx] = pa[idx];
	}
}


int randint(int min, int max){
	return rand() % max + min;
}

