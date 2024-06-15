#include <curses.h>
#include <termios.h>
#include <stdio.h>
#include "getl.c"

void w_all(char*);

int main(void){
	int c;
	while(1){
		if(getl() == '\033'){
			getl();
			switch ((c = getl())) {
				case 'A': w_all("UP"); break;
				case 'B': w_all("DOWN"); break;
				case 'C': w_all("RIGHT"); break;
				case 'D': w_all("LEFT"); break;
				default: w_all("~"); break;
			}
		}else{
			switch ((c = getl())) {
				default: {
					printf("%i\n", c);
			 }
			}
		}
	}
}


void clear_buffer(){
	int i;
	char spaces[1000];
	for(i = 0; i < 10; ++i)
		spaces[i] = ' ';
	spaces[i] = '\0';
	printf("\r%s", spaces);
	fflush(stdout);
}

void w_all(char *l){
	clear_buffer();
	printf("\r  %s\r", l);
	fflush(NULL);
}

