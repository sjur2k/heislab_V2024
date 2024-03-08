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



<<<<<<< HEAD
=======
//halla man, hva skjera!


//hm
>>>>>>> origin/main
int main(){
    elevio_init();
    initialize();
    test_queue();
    
<<<<<<< HEAD
    
=======


>>>>>>> origin/main

    int cycle_num = 0;
    state_type previous_state = IDLE;
    int floor;

<<<<<<< HEAD
=======

>>>>>>> origin/main
    while(1){
        
        floor = elevio_floorSensor();
        if(floor!=-1){
            initialize_elevator_state(floor);
        }
<<<<<<< HEAD
       


        for(int f = 0; f<N_FLOORS; f++){
            for(ButtonType b = BUTTON_HALL_UP; b<=BUTTON_CAB; b++){
                
                if(!((f == 0 && b == BUTTON_HALL_DOWN)||(f == (N_FLOORS -1) && b == BUTTON_HALL_UP))){
=======
        fetch_button(); //legger til knapper i button_ind matrisen
        update_queue_from_request(); //legger til bestillinger i køen queue ut i fra knappene som er trigget
        //update_lights_from_request();
        
    
   
    
        for(int f = 0; f<N_FLOORS; f++){
            for(ButtonType b = BUTTON_HALL_UP; b<=BUTTON_CAB; b++){
                if(!((f == 0 && b == BUTTON_HALL_DOWN)
                    ||(f == (N_FLOORS -1) && b == BUTTON_HALL_UP))){
>>>>>>> origin/main

                    if(elevio_callButton(f,b)){
                        button_sensor(b,f);
                    }
                }
            }
        }

        //cab();

        
       
       
<<<<<<< HEAD
       }*/

       if(get_state() != previous_state){
        printf("Current state: %d, Cycle number: %d \n", get_state(), cycle_num);
        test_queue();
        printf("Current floor: %d \n", floor);
       }
       previous_state = get_state();
=======
>>>>>>> origin/main
        
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



