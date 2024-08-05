#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void cls(void){
	system("clear");
}

char *fill_char(char t[], int expand){
	int i;
	char *n = (char *)malloc(1000 * sizeof(char));
	for(i = 0; t[i] != '\0'; ++i){
		n[i] = t[i];
	}
	if(i < expand)
		for(; i < expand - 1; ++i){
			n[i] = ' ';
		}
	return n;
}


void draw_frame(int w, int h, struct BLOCK blocks[], void (*on_hit)(void), void (*on_get)(void), char *headers[3]){ int x, y;
	x = y = 0;
	
	cls();
	char title[w];

	for(int i = 0; i < w; i++)
		title[i] = '\0';

	int divider = (w / 3);
	
	int i;
	char collect[100];

	for(i = 0; i < 3; ++i)
		sprintf(title, "%s%s│", title, fill_char(headers[i], divider));

	int tlen = (int)strlen(title);
	int tc = 0;
	int ecount = 0;


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
						printf("│");
						on_hit();
					}
					else{
						if(ecount == 1)
							printf("    │");  // this should be here because of the chars are not 1 byte
						else
							printf("│");
						ecount++;
					}
			else
				if(y == 1){
					if(tc < tlen)
						printf("%c", title[tc]);
					tc++;
				} else
					if(y == 2 || y == 0 || y == h){
						if(contain_coord(x, y - 2, blocks) != -1){
							printf("─");
							on_hit();
						}else{
							if((x == divider || x == (divider * 2)) && y == 0)
								printf("┬");
							else if((x == divider || x == (divider * 2)) && y == 2)
								printf("┴");
							else
							printf("─");
						}
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

