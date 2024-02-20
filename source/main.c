#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/heisdynamikk.h"



int main(){
    elevio_init();

    printf("Press the stop button on the elevator panel to exit\n");

    int floor = elevio_floorSensor();
    if (floor != 0){
        while (1){
            int floor = elevio_floorSensor();
            elevio_motorDirection(DIRN_DOWN);
            if (floor==0){
                elevio_motorDirection(DIRN_STOP);
                break;
            }
        }
    }
    bool cond=true;
    while(1){
        int floor = elevio_floorSensor();
        //printf("%d\n",floor);
        // if (floor==1){
        //     elevio_motorDirection(DIRN_STOP);
        // }

        // if(floor>=2){
            
        // }

        // if(floor == 0){
        //     elevio_motorDirection(DIRN_UP);
        // }

        // if(floor == N_FLOORS-1){
        //     elevio_motorDirection(DIRN_DOWN);
        // }
        if(cond==true){
            moveup(floor, 2);
            //floor=elevio_floorSensor();
            // movedown(floor, 1);
            // floor=elevio_floorSensor();
            moveup(floor, 1);
            cond=false;
        }

        // for(int f = 0; f < N_FLOORS; f++){ // kjører veldig seint her, klarer ikke registrere etg før den har kjørt forbi:(
        //     for(int b = 0; b < N_BUTTONS; b++){
        //         int btnPressed = elevio_callButton(f, b);
        //         elevio_buttonLamp(f, b, btnPressed);
        //     }
        // }
        
        // if(elevio_obstruction()){
        //     elevio_stopLamp(1);
        // } else {
        //     elevio_stopLamp(0);
        // }
        
        if(elevio_stopButton()){
            while (floor!=0){
                floor=elevio_floorSensor();
                elevio_motorDirection(DIRN_DOWN);
                if (floor==0){
                    elevio_motorDirection(DIRN_STOP);
                    break;
                }
            }
            break;
        }
        
    }

    return 0;
}
