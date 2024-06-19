#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void cls(void){
	system("clear");
}


void draw_frame(int w, int h, struct BLOCK blocks[], void (*on_hit)(void), void (*on_get)(void), char title[]){
	int x, y;
	x = y = 0;
	
	cls();

	int tlen = (int)strlen(title);
	int tcount = 0;

	while(y < (h + 1)){
		while(x < (w + 1)){

			if(x == w || x == 0)
				if(y == 0 && x == 0 )
					printf("┌");
				else if(y == 0 && x == w )
					printf("┐");
				else if(y == h && x == 0 )
					printf("└");
				else if(y == h && x == w )
					printf("┘");
				else if(y == 2 && x == 0 )
					printf("├");
				else if(y == 2 && x == w )
					printf("┤");
				else
					if((contain_coord(x, y - 2, blocks) != -1)){
						// exit(0);
						printf("│");
						on_hit();
					}
					else
						printf("│");
			else
				if(y == 1){
					if(tcount < tlen)
						printf("%c", title[tcount]);
					else
						printf(" ");
					tcount++;
				} else
					if(y == 2 || y == 0 || y == h){
						if(contain_coord(x, y - 2, blocks) != -1){
							// exit(0);
							printf("─");
							on_hit();
						}
						else
							printf("─");
					} else{
						int ic = contain_coord(x, y - 2, blocks);
						if(ic != -1){
							printf("%s", blocks[ic].body);
						} else{
							printf(" ");
						}
					}
			++x;
		}
		putchar('\n');
		++y;
		x = 0;
	}
}

