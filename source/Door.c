
#include "driver/elevio.h"
#include "Door.h"


void open_door(){
    elevio_doorOpenLamp(1);
}

void close_door(){
    elevio_doorOpenLamp(0);
}
