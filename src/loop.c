#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "control.h"
#include "utils.h"
#include "rules.h"


void alarm_ms(int ms){
	struct itimerval it_val;  // for setting itimer
	it_val.it_value.tv_sec = ms/1000;
	it_val.it_value.tv_usec = (ms*1000) % 1000000;   
	it_val.it_interval = it_val.it_value;
	setitimer(ITIMER_REAL, &it_val, NULL);
}


volatile int status = 0;
static void (*p_event)(int);

static int __key;
static int __state;

void loop_event_call(int sig) {
	if(status == 0)
		// alarm(1);
		alarm_ms(game_speed);
	if(__state)
		p_event(__key);
	else
		p_event(0);
	__state = 0;
}

void loop_event(void (*event)(int)) {
	p_event = event;
	alarm_ms(game_speed);
	signal(SIGALRM, loop_event_call);
	while(status == 0){
		__key = getkey();  // get key press without echo
		__state = 1;
		if(__key == 133){
			status = 1;
		}
		delay_ms(game_speed);
	}
}

