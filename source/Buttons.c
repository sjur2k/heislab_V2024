#include "driver/elevio.h"
static int button_ind[N_FLOORS][N_BUTTONS] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};


void fetch_button(){
    for (int floor = 0; floor< N_FLOORS; floor++){
        for(int button = 0; button<N_BUTTONS;button++){
                if(elevio_callButton(floor, button)==1){
                    button_ind[floor][button] = 1;
                }
            }
        }
    }



int get_button(ButtonType b, int floor){
    return button_ind[b][floor];
}

void remove_all_buttons(){
    for(int floor = 0; floor<N_FLOORS; floor++){
        for(int button = 0; button<N_BUTTONS; button++){
            if(button_ind[floor][button] != 0){
                button_ind[floor][button] = 0;
            }
        }
    }
}

void remove_button(int floor, int button){
    button_ind[floor][button] = 0;
}


void show_button_ind(){
    int matrise[N_FLOORS][N_BUTTONS] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    for (int i = 0; i < N_FLOORS; i++) {
        printf("Etasje %d: ", i);
        for (int j = 0; j < N_BUTTONS; j++) {
            matrise[i][j] = get_button(i,j); 
            printf("%d ", matrise[i][j]);
        }
        printf("\n");
    }
}

void set_button(ButtonType button, int floor){
    button_ind[floor][button];
}




