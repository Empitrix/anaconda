#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "./structs.c"
 
void delay_ms(int number_of_seconds){
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;
	// Storing start time
	clock_t start_time = clock();
	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds);
}


// int contain_coord(int x, int y, struct BLOCK blocks[]){
int contain_coord(int x, int y, struct BLOCK blocks[]){

	// int max = (int)sizeof((void *)blocks) / sizeof(blocks[0]);

	// int count = 0;
	int i;
	for(i = 0; blocks[i].x; ++i){
		if(blocks[i].x == x && blocks[i].y == y){
			return 1;
		}
		// ++count;
	}
	// printf("MAX:%i|", count);
	return 0;
}

