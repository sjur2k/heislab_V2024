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



//halla man, hva skjera!

int main(){
    elevio_init();
    initialize();
    test_queue();
    



    int cycle_num = 0;
    state_type previous_state = IDLE;


    while(1){
        
        int floor = elevio_floorSensor();
        if(floor!=-1){
            move_elevator(floor);
        }
        fetch_button(); //legger til knapper i button_ind matrisen
        update_queue_from_request(); //legger til bestillinger i køen queue ut i fra knappene som er trigget
        //update_lights_from_request();
        
    
   
    
        for(int f = 0; f<N_FLOORS; f++){
            for(ButtonType b = BUTTON_HALL_UP; b<=BUTTON_CAB; b++){
                if(!((f == 0 && b == BUTTON_HALL_DOWN)
                    ||(f == (N_FLOORS -1) && b == BUTTON_HALL_UP))){

                    if(elevio_callButton(f,b)){
                        fsm_ev_button(b,f);
                    }
                }
            }
        }

        //cab();

        
       
       
        
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



