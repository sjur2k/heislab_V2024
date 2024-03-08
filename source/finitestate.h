#pragma once
#include "stdbool.h"

#define WAIT_TIME 1  //SKAL ENDRES TIL 3 (?) for å bestå fat

#define ON 1
#define OFF 0


typedef enum states{
    IDLE = 0,
    GO = 1,
    STAY = 2,
    EMERGENCY = 3
} state_type;

static state_type current_state;
static int motor_direction;
static double realFloor;


void update_current_floor();

void initialize();

void direction_elevator(MotorDirection direction);



state_type get_state();

MotorDirection last_target_before_stop();

void remove_last_before_stop();

void state_drive();
void state_idle();

void go_up();
void go_down();
void cab();
void initialize_elevator_state(int floor);
void next_state(state_type state);
void button_sensor(ButtonType button, int floor);

