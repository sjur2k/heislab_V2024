#include <stdlib.h>
#include <stdio.h>

#include "driver/elevio.h"
#include "Door.h"
#include "finitestate.h"
#include "queue.h"

#define BETWEEN_FLOORS -1


static MotorDirection current = DIRN_STOP;
static MotorDirection last = DIRN_STOP;
static MotorDirection lastBeforeStop = DIRN_STOP;

static state_list next_s = IDLE;
static action_state_list next_a = ENTRY;
static int currentFloor = BETWEEN_FLOORS;
static int previous_floor = BETWEEN_FLOORS;


void update_current_floor(){
    currentFloor = elevio_floorSensor();
}

void direction_elevator(MotorDirection direction){
    elevio_motorDirection(direction);
    if (direction != DIRN_STOP) last = direction;
    current = direction;
}

void transition(action_state_list a, state_list s){
    next_s = s;
    next_a = a;
}

MotorDirection last_target_before_stop(){
    return (lastBeforeStop != DIRN_STOP);
}

void remove_last_befor_stop(){
    lastBeforeStop = DIRN_STOP;
}


void initialize(){
    clear_all_in_queue();
    clear_all_lights();
    update_current_floor();
    if (currentFloor==BETWEEN_FLOORS){ 
        elevio_motorDirection(DIRN_DOWN);
    }
    while(currentFloor == -1){
        printf("Init %d\n", currentFloor);
        update_current_floor();
    }
    direction_elevator(DIRN_STOP);
    elevio_floorIndicator(currentFloor);
    transition(IDLE, ENTRY);

}

state_list next_state(){
    return next_s;
}

void state_drive(){
    switch (next_a)
    {
    case ENTRY:
        if(currentFloor == -1 && current == DIRN_STOP){
            if(!last_target_before_stop()) lastBeforeStop = last;
            if(orders_over_queue(previous_floor)||(last_target_before_stop == DIRN_DOWN && get_order(previous_floor)!=NO_ORDER)){
                direction_elevator(DIRN_UP);
            }
            else{
                direction_elevator(DIRN_DOWN);
            }
        }
        else{
            if(currentFloor ==0){
                direction_elevator(DIRN_DOWN);
            }
            else if(currentFloor = N_FLOORS-1){
                direction_elevator(DIRN_DOWN);
            }
            else if(last == DIRN_UP && !orders_over_queue(currentFloor)){
                direction_elevator(DIRN_DOWN);
            }
            else if(last==DIRN_DOWN && !orders_under_queue(currentFloor)){
                direction_elevator(DIRN_UP);
            }
            else if(last==DIRN_STOP &&orders_over_queue(currentFloor)){
                direction_elevator(DIRN_UP);
            }
            else if(last == DIRN_STOP){
                direction_elevator(DIRN_DOWN);
            }
            else{
                direction_elevator(last);
            }
        }
        transition(GO, INTERNAL);
        
    case INTERNAL:
    update_current_floor();
    if(currentFloor!=-1){
        remove_last_befor_stop();
        if(currentFloor!=previous_floor){
            elevio_floorIndicator(currentFloor);
            previous_floor = currentFloor;
        }
        if(stop_queue(currentFloor, current)){
            transition(STAY, ENTRY);
        }
    }
    break;
    
    default:
    break;
    }
}

void go_up(int floor){
    update_current_floor();
    int start_floor=currentFloor;
    int target = start_floor + floor;
    elevio_motorDirection(DIRN_UP);
    while(currentFloor!=target){
        update_current_floor();
        printf("%D\n", currentFloor);
    }
    elevio_motorDirection(DIRN_STOP);
    
}

void go_down(int floor){
    update_current_floor();
    int start_floor=currentFloor;
    int target = start_floor - floor;
    elevio_motorDirection(DIRN_DOWN);
    while(currentFloor!=target){
        update_current_floor();
        printf("%D\n", currentFloor);
    }
    elevio_motorDirection(DIRN_STOP);
}


