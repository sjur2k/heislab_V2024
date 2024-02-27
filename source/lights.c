#include "driver/elevio.h"
#include "Buttons.h"
#include "lights.h"

static int lights[N_FLOORS][N_BUTTONS] = {};

void clear_floor_light(int floor){
    for(int button = 0; button<N_BUTTONS;button++){
        if(lights[floor][button]==1){
            lights[floor][button]==0;
            if(!(button == BUTTON_HALL_DOWN && floor == 0 ) && !(floor == N_FLOORS-1 && button == BUTTON_HALL_UP)){
                elevio_buttonLamp(floor, button, 0);
            }
        }
    }
}

void clear_all_lights(){
    for(int floor = 0; floor<N_FLOORS;floor++){
        clear_floor_light(floor);
    }
}

void update_lights_from_request(){
    for(int f = 0;f<N_FLOORS;f++){
        for(int b = 0; b<N_BUTTONS;b++){
            if(get_button(f,b) && lights[f][b]==0){
                lights[f][b]=1;
                elevio_buttonLamp(b, f, 1);
            }
        }
    }
}