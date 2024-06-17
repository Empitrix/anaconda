#include <signal.h>
#include <unistd.h>
#include "./control.c"

// this is works for each loop and immediate action for key press
/*
#include <signal.h>
#include <unistd.h>
#include "./control.c"


volatile int status = 0;
static void (*p_event)(int);

void loop_event_call(int sig) {
	if(status == 0)
		alarm(1);
	p_event(0);
}

void loop_event(void (*event)(int)) {
	int k;
	p_event = event;
	alarm(1);
	signal(SIGALRM, loop_event_call);
	while(status == 0){
		if((k = getkey()) == 133){
			status = 1;
		}
		p_event(k);
		sleep(1);
	}
}

*/



volatile int status = 0;
static void (*p_event)(int);

static int __key;
static int __state;

void loop_event_call(int sig) {
	if(status == 0)
		alarm(1);
	if(__state)
		p_event(__key);
	else
		p_event(0);
	__state = 0;
}

void loop_event(void (*event)(int)) {
	p_event = event;
	alarm(1);
	signal(SIGALRM, loop_event_call);
	while(status == 0){
		__key = getkey();  // get key press without echo
		__state = 1;
		if(__key == 133){
			status = 1;
		}
		sleep(1);
	}
}

