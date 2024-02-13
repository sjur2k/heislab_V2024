#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    int floor = elevio_floorSensor();
    if (floor != 0){
        while (1){
            int floor = elevio_floorSensor();
            printf("%d\n",floor);
            elevio_motorDirection(DIRN_DOWN);
            if (floor==0){
                elevio_motorDirection(DIRN_STOP);
                printf("%d\n",floor);
                break;
            }
        }
    }
    
    while(1){
        int floor = elevio_floorSensor();
        printf("%d\n",floor);
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


        for(int f = 0; f < N_FLOORS; f++){ // kjører veldig seint her, klarer ikke registrere etg før den har kjørt forbi:(
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

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
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
