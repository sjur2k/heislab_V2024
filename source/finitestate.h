#pragma once



typedef enum states {
    EMERGENCY,
    IDLE,
    GO,
    STAY
}state_list;

typedef enum actions{
    EXIT,
    INTERNAL,
    ENTRY
} action_state_list;


void update_current_floor();

void initialize();

void direction_elevator(MotorDirection direction);

void transition(action_state_list a, state_list s);

state_list next_state();

MotorDirection last_target_before_stop();

void state_drive();

void go_up(int floor);
void go_down(int floor);

