#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void cls(void){
	system("clear");
}

char *fill_char(char t[], int expand){
	int i;
	char *n = (char *)malloc(sizeof(char));
	for(i = 0; t[i] != '\0'; ++i){
		n[i] = t[i];
	}
	// n[i] = '\0';
	if(i < expand)
		for(; i < expand - 1; ++i){
			n[i] = ' ';
		}
	// n[i] = '\0';
	return n;
}


// void draw_frame(int w, int h, struct BLOCK blocks[], void (*on_hit)(void), void (*on_get)(void), char title[]){
void draw_frame(int w, int h, struct BLOCK blocks[], void (*on_hit)(void), void (*on_get)(void), char *headers[3]){ int x, y;
	x = y = 0;
	
	cls();
	char title[w];

	int divider = (w / 3) - 1;
	
	int i;
	char collect[100];

	for(i = 0; i < 3; ++i){
		if(i == 2){
			sprintf(title, "%s%s", title, fill_char(headers[i], divider));
		}else {
			sprintf(title, "%s%s│", title, fill_char(headers[i], divider));
		}
	}

	// sprintf(title, "%s%s│", title, "  ");
	int tlen = (int)strlen(title);
	// int tlen = 39;
	int tc = 0;


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
						if(y == 1 && x == w)
							// printf("   1");
							printf("    │");
						else
							printf("│");
							//printf("0");
						//printf("│");
			else
				if(y == 1){
					if(tc < tlen){
						// if(title[tc] != '\0')
						printf("%c", title[tc]);
					}
					else
						printf("*");
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

