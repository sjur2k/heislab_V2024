#include <stdlib.h>
#include <stdio.h>

#include "driver/elevio.h"
#include "Door.h"
#include "finitestate.h"
#include "queue.h"
#include "Buttons.h"
#include "timer.h"
#include "lights.h"

#define BETWEEN_FLOORS -1


static int currentFloor = BETWEEN_FLOORS;
static int previous_floor = BETWEEN_FLOORS;

void update_current_floor()
{
    currentFloor = elevio_floorSensor();
}


void initialize()
{
    
    clear_all_in_queue();
    clear_all_lights();
    update_current_floor();
    printf("currentfloor %d\n", currentFloor);
    if(currentFloor == -1){
        printf("currentfloor = -1\n");
        elevio_motorDirection(DIRN_DOWN);
    }
    while(currentFloor == -1){
        printf("Initializing%d\n", currentFloor);
        update_current_floor();
    }
    elevio_motorDirection(DIRN_STOP);
    current_state = IDLE;
}

state_type get_state()
{
    return current_state;
}


void move_elevator(int floor){
    printf("Move_elevator is going.");
    elevio_floorIndicator(floor);
    currentFloor = floor;
    printf("Current floor: %d \n", currentFloor);
    realFloor = currentFloor + motor_direction/2.0;

    switch (current_state)
    {
    case IDLE:
        printf("IDLE");
        break;
    case GO:
        printf("GO");
        if(stop_queue(floor, motor_direction)){
            current_state = STAY;
        }
        break;
    case STAY:
        printf("STAY");
        motor_direction = DIRN_STOP;
        elevio_motorDirection(DIRN_STOP);

        if(!active_timer()){
            set_timer();
        }
        open_door();
        remove_order(floor);
        clear_floor_light(currentFloor);

        if(get_timer() > WAIT_TIME){
            reset_timer();
            close_door();

            if(no_orders_left()){
                current_state = IDLE;
            }
            else{
                motor_direction = get_direction_from_order(currentFloor);
                elevio_motorDirection(motor_direction);
                current_state = GO;
            }
        }
        break;

    case EMERGENCY:
        printf("EMERGENCY");
        open_door();
        while(elevio_stopButton()){};
        elevio_stopLamp(OFF);
        close_door();
        current_state = STAY;
        break;

    }
}


































void go_up()
{
    update_current_floor();
    int start_floor = currentFloor;
    elevio_motorDirection(DIRN_UP);
    while (currentFloor == BETWEEN_FLOORS || currentFloor == start_floor)
    {
        update_current_floor();
    }
    elevio_motorDirection(DIRN_STOP);
}

void go_down()
{
    update_current_floor();
    int start_floor = currentFloor;
    elevio_motorDirection(DIRN_DOWN);
    while (currentFloor == BETWEEN_FLOORS || currentFloor == start_floor)
    {
        update_current_floor();
    }
    elevio_motorDirection(DIRN_STOP);
}

void cab()
{
    int list[N_FLOORS] = {-1, -1, -1, -1};
    for (int i = 0; i < N_FLOORS; i++)
    {
        list[i] = get_queue(i);
        if (list[i] != NO_ORDER)
        {
            update_current_floor();
            int dir = i - currentFloor;
            test_queue();
            printf("Dir: %d \n", dir);
            if (dir < 0)
            {
                for (int j = 0; j < abs(dir); j++)
                {
                    go_down();
                }
            }
            if (dir > 0)
            {
                for (int k = 0; k < dir; k++)
                {
                    go_up();
                }
            }
            remove_button(i, list[i]);
            clear_queue_floor(i);
            test_queue();
        }
    }
}
