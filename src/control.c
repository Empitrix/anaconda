#include <termios.h>
#include <stdio.h>

static struct termios old, current;

void initTermios(int echo){         /* terminal i/o settings */
	tcgetattr(0, &old);               /* grab old terminal i/o settings */
	current = old;                    /* make new settings same as old settings */
	current.c_lflag &= ~ICANON;       /* disable buffered i/o */
	current.c_lflag &= ~ECHO;         /* set no echo mode */
	tcsetattr(0, TCSANOW, &current);  /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void){
	tcsetattr(0, TCSANOW, &old);
}

char getl(void){
	char ch;
	initTermios(0);
	ch = getchar();
	resetTermios();
	return ch;
}

/*
Explain:
the arrow keys returns as negative integer:
	-1: Up
	-2: Down
	-3: Right
	-4: Left

Other keys returns as their integer values:
for example:
	113: q
	...
*/

int getkey(void){
	int k, o;
	switch ((k = getl())) {
		case '\033':{
			getl();  // skip
			switch(k = getl()){
				case 'A': o = -1; break;  // UP
				case 'B': o = -2; break;  // Down
				case 'C': o = -3; break;  // Right
				case 'D': o = -4; break;  // Left
				default: break;
			}
			break;
		}
		default: o = k; break;
	}
	return o;
}

