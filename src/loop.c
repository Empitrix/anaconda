#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "control.h"


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


// void delay_ms(int number_of_seconds){
// 	// Converting time into milli_seconds
// 	int milli_seconds = 1000 * number_of_seconds;
// 	// Storing start time
// 	clock_t start_time = clock();
// 	// looping till required time is not achieved
// 	while (clock() < start_time + milli_seconds);
// }
// 
// void alarm_ms(int ms){
// 	delay_ms(ms);
// 	raise(SIGALRM);
// }


volatile int status = 0;
static void (*p_event)(int);

static int __key;
static int __state;

void loop_event_call(int sig) {
	if(status == 0)
		alarm(1);
		// alarm_ms(500);
	if(__state)
		p_event(__key);
	else
		p_event(0);
	__state = 0;
}

void loop_event(void (*event)(int)) {
	p_event = event;
	alarm(1);
	// alarm_ms(500);
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

