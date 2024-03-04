#include "timer.h"
#include "stdbool.h"


void set_timer(){
	timer = time(0);
	active = 1;
};

time_t get_timer(){
	return (time(0)-timer);
};

bool active_timer(){
	return active;
};

void reset_timer(){
	active = 0;
};