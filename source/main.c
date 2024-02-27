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





int main(){
    //elevio_init();
    initialize();
    //test_queue();

    //go_up(1);
    //go_down(1);


    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    //show_queue();
    show_button_ind();
    elevio_motorDirection(DIRN_UP);

    while(1){
        if (elevio_stopButton()){
            transition(EMERGENCY, ENTRY);
        }
        
         //legger til knapper i button_ind matrisen
        //update_queue_from_request(); //legger til bestillinger i køen queue ut i fra knappene som er trigget
        //update_lights_from_request();
        
        /*switch (next_state())
        {
        case GO:
            state_drive();
            break;
        }*/
        
        int floor = elevio_floorSensor();
        printf("%d\n", floor);
        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }
        printf("%d\n", floor);

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }

        printf("%d\n", floor);
       fetch_button();

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                //printf("%d\n", btnPressed);
                //show_button_ind();
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

    /*
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        */
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}



