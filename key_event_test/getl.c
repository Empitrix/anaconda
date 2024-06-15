#include <termios.h>
#include <stdio.h>

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo){
	tcgetattr(0, &old);               /* grab old terminal i/o settings */
	current = old;                    /* make new settings same as old settings */
	current.c_lflag &= ~ICANON;       /* disable buffered i/o */
	if (echo) {
		current.c_lflag |= ECHO;        /* set echo mode */
	} else {
		current.c_lflag &= ~ECHO;       /* set no echo mode */
	}
	tcsetattr(0, TCSANOW, &current);  /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void){ tcsetattr(0, TCSANOW, &old); }

char getl(void){
	char ch;
	initTermios(0);
	ch = getchar();
	resetTermios();
	return ch;
}

