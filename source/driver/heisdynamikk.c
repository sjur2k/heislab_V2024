#include "elevio.h"
#include "heisdynamikk.h"
#include "stdio.h"
#include "stdlib.h"


void moveup(int originalfloorup, int n_floorsup){
    int destinationup = n_floorsup + originalfloorup;
    int currentfloorup = elevio_floorSensor();

    printf("%d\nDestinationUP: ",destinationup);
    printf("%d\nOriginalfloorUP: ",originalfloorup);
    printf("%d\nN_floorsUP: ",n_floorsup);

    if (1<=destinationup && destinationup<=3){
        
        
        while(currentfloorup <= destinationup){
            elevio_motorDirection(DIRN_UP);
            printf("%d\nCurrentfloorUP_before: ",currentfloorup);
            currentfloorup = elevio_floorSensor();
            printf("%d\nCurrentfloorUP_after: ",currentfloorup);
        }
        
        elevio_motorDirection(DIRN_STOP);
        return;
    }else{
        fprintf(stderr,"Floor request out of bounds!");
        exit(1);
    }
};

void movedown(int originalfloordown, int n_floorsdown){
    int destinationdown = originalfloordown - n_floorsdown;
    int currentfloordown = originalfloordown;
    printf("%d\nDestinationDOWN: ",destinationdown);
    printf("%d\nOriginalfloorDOWN: ",originalfloordown);
    printf("%d\nN_floorsDOWN: ",n_floorsdown);
    if(0<=destinationdown && destinationdown<=2){
     
        
        while (currentfloordown > destinationdown){
            if (currentfloordown==-1){
                continue;
            }
            elevio_motorDirection(DIRN_DOWN);
            currentfloordown = elevio_floorSensor();
            printf("%d\nCurrentfloorDOWN: ",currentfloordown);
        }
        
        elevio_motorDirection(DIRN_STOP);
        return;
    }else{
        fprintf(stderr, "Floor request out of bounds!");
        exit(1);
    };
};