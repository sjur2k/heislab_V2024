#include <time.h>
#include <stdbool.h>


#ifndef TIMER_H
#define TIMER_H


static time_t timer;
static bool active;


void set_timer();

time_t get_timer();

void reset_timer();

bool active_timer();

#endif