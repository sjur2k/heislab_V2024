#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "Door.h"
#include "finitestate.h"
#include "Buttons.h"
#include "queue.h"
#include "lights.h"
#include "timer.h"





int main(){
    elevio_init();
    initialize();
    test_queue();
    

    //go_up(1);
    //go_down(1);

    int cycle_num = 0;
    state_type previous_state = IDLE;


    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    //elevio_motorDirection(DIRN_UP);
    while(1){
        
        int floor = elevio_floorSensor();
        printf("Floor: %d\n", floor);
        /*if(floor!=-1){
            move_elevator(floor);
        }*/
        fetch_button(); //legger til knapper i button_ind matrisen
        update_queue_from_request(); //legger til bestillinger i køen queue ut i fra knappene som er trigget
        //update_lights_from_request();
        
    
        
        //int floor = elevio_floorSensor();
        //printf("%d\n", floor);

      /*  if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }*/
        for(int f = 0; f<N_FLOORS; f++){
            for(ButtonType b = BUTTON_HALL_UP; b<=BUTTON_CAB; b++){
                /*
                 * The first if statement ensures that elements in the
                 * button_channel_matirx not assosciated with a button are not accessed.
                 */
                if(!((f == 0 && b == BUTTON_HALL_DOWN)
                    ||(f == (N_FLOORS -1) && b == BUTTON_HALL_UP))){

                    if(elevio_callButton(f,b)){
                        fsm_ev_button(b,f);
                    }
                }
            }
        }

        //cab();

       /* for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                //printf("%d\n", btnPressed);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }*/

    /*
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        */
       /*switch (get_next_state())
       {
       case IDLE:
        state_idle();
       case GO:
        state_drive();
        break;
       
       
       }*/
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        cycle_num++;
        //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    
    test_queue();

    return 0;
}



