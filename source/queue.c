#include "queue.h"
#include <stdio.h>
#include "Buttons.h"

#define BETWEEN_FLOORS = -1

static int queue[N_FLOORS] = {0,0,0,0};


void add_order_queue(int floor, order_list order){
    order_list old_order = queue[floor];
    if(order = NO_ORDER) queue[floor] = NO_ORDER;
    else if((old_order==ORDER_UP || old_order ==ORDER_DOWN) && old_order != order) queue[floor]=ORDER_ALL;
    else if(old_order!=ORDER_ALL) queue[floor] = order;
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
            if(get_button(floor, b)){
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
    if (f ==-1){
        return NO_ORDER;
    }
    else{
        return queue[f];
    }
}

int stop_queue(int floor, MotorDirection d){
    order_list order = queue[floor];
    if(floor ==-1) return 0;
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
    for (int i = 0; i < N_FLOORS; ++i) {
        printf("queue[%d] = %d\n", i, queue[i]);
    }
}

int get_queue(int floor){
    return queue[floor];
}


void test_queue(){
    show_queue();
    show_button_ind();
    while(1){
        fetch_button();
        update_queue_from_request();
        for(int f = 0; f<N_FLOORS;f++){
            if(get_queue!=-1){
                show_queue();
                break;
            }
            for(int b = 0; b<N_BUTTONS; b++){
                if(get_button(f,b)!=0){
                    show_button_ind();
                    break;
                }

            }
        }
    }
    
}