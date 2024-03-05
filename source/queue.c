#include "queue.h"


#define BETWEEN_FLOORS -1

static int queue[N_FLOORS] = {-1,-1,-1,-1};


void add_order_queue(int floor, order_list order){
    order_list old_order = queue[floor];
    if(order == NO_ORDER){ 
        queue[floor] = NO_ORDER;
    }
    /*else if((old_order==ORDER_UP || old_order ==ORDER_DOWN) && old_order != order) {
        queue[floor]=ORDER_ALL;
    }*/
    if(old_order!=ORDER_ALL) {
        queue[floor] = order;
    }
}

void clear_queue_floor(int floor){
    add_order_queue(floor, NO_ORDER);
}

void clear_all_in_queue(){
    for(int floor = 0; floor<N_FLOORS; floor++){
        add_order_queue(floor, NO_ORDER);
    }
}

void update_queue_from_request(){
    for(int floor = 0; floor<N_FLOORS;floor++){
        for(int b = 0; b<N_BUTTONS;b++){
            if(get_button(floor, b)==1){
                add_order_queue(floor, b);
            }
        }
    }
}

int orders_over_queue(int floor){
    for(int i =floor +1;i<N_FLOORS;i++){
        if(queue[i] !=NO_ORDER){
            return 1;
        }
    }
    return 0;
}
int orders_under_queue(int floor){
    for(int i = floor -1;i>=0;i--){
        if(queue[i]!=NO_ORDER){
            return 1;
        }
    }
    return 0;
}

order_list get_order(int f){
    if (f ==BETWEEN_FLOORS){
        return NO_ORDER;
    }
    else{
        return queue[f];
    }
}

int stop_queue(int floor, MotorDirection d){
    order_list order = queue[floor];
    if(floor ==BETWEEN_FLOORS) return 0;
    else if(order == ORDER_ALL){
        return 1;
    }
    else if(d==DIRN_UP&&order ==ORDER_UP){
        return 1;
    }
    else if(d == DIRN_DOWN && order ==ORDER_DOWN){
        return 1;
    }
    else if(d==ORDER_UP && order == ORDER_DOWN){
        return !orders_over_queue(floor);
    }
    else if(d==DIRN_DOWN&&order==ORDER_UP){
        return !orders_under_queue(floor);
    }
    else{
        return 0;
    }
}

void show_queue(){
    int array[N_FLOORS] = {0,0,0,0};
    for (int i = 0; i < N_FLOORS; ++i) {
        array[i] = get_queue(i);
        printf("queue[%d] = %d\n", i, array[i]);
    }
}

int get_queue(int floor){
    return queue[floor];
}


void test_queue(){
    show_queue();
    show_button_ind();
    show_lights();
}


int queue_any_orders(){
    for(int f = 0; f<N_FLOORS;f++){
        if(queue[f!=NO_ORDER]){
            return 1;
        }
    }return 0;
}

void order_clear_all() {
	for (int i = 0; i < N_FLOORS; i++) {
		queue[i] = -1;
		for (int j = 0; j < N_BUTTONS; j++) {
			remove_button(i,j);
		}
	}

}

void remove_order(int floor){
    for(int i = 0; i < N_BUTTONS; i++){
        remove_button(floor, i); //Fjerner ordre for hver etasje
    }

    //Skyv gjennværende ordre framover i køen

    for(int f = 0; f < N_FLOORS;f++){
        if(queue[f]==floor){
            if(f !=(N_FLOORS-1)){
                for(int i = f; i<(N_FLOORS-1);i++){
                    queue[i] = queue[i+1];
                }
            };
            queue[N_FLOORS-1] = -1;
        }
    }
}

bool no_orders_left(){
    for(int i = 0; i<N_FLOORS;i++){
        if(queue[i]!=BETWEEN_FLOORS || get_button(BUTTON_HALL_UP,i) != 0
            || get_button(BUTTON_HALL_DOWN, i) != 0
            || get_button(BUTTON_CAB,i)!= 0){
                return 0;
            }
    }
    return 1;
};

MotorDirection get_direction_from_order(int floor){

    //ser hvor første elementet i køen er og returnerer retning

    if(queue[0]<floor && queue[0]!= NO_ORDER){
        return DIRN_DOWN;
    };
    if(queue[0]>floor && queue[0]!=NO_ORDER){
        return DIRN_UP;
    };
    if (queue[0] == floor && queue[0] != NO_ORDER){
        return DIRN_STOP;
    };


    //Her returnerer den retning i forhold til den nåværende etasjen som har flest etterspørsler

    int requestUp = 0;
    int requestDown = 0;
    for(int i = 0; i<floor;i++){
        requestDown += get_button(i,1);
        requestDown +=get_button(i,0);
    }
    for(int f = floor +1; f<N_FLOORS;f++){
        requestUp += get_button(f,1);
        requestUp +=get_button(f,0);
    }

    if(requestUp>=requestDown && requestUp != 0){
        return DIRN_UP;
    };
    if(requestDown >requestUp){
        return DIRN_DOWN;
    };
    return DIRN_STOP;
}

void order_update(ButtonType button, int floor) {
	set_button(button, floor);

	/* 
	 * Add new order to queue 
	 */
	if (button == BUTTON_CAB) {
		for (int i = 0; i < N_FLOORS; i++) {
			if (queue[i] == floor || queue[i] == -1) {
				queue[i] = floor;
				break;
			}
		}
	}
}