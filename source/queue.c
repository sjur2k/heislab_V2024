#include "queue.h"


#define BETWEEN_FLOORS -1

static int queue[N_FLOORS] = {-1,-1,-1,-1};


void clear_all_in_queue(){
    for(int i = 0; i<N_FLOORS;i++){
        queue[i] = NO_ORDER;
    }
}

order_list get_order(int f){
    if (f ==BETWEEN_FLOORS){
        return NO_ORDER;
    }
    else{
        return queue[f];
    }
}
bool queue_is_empty(){
    for(int i = 0; i<N_FLOORS; i++){
        if(queue[i] != -1){
            return 0;
        }
    }
    return 1;
}

bool stop_queue(int floor, MotorDirection d){
    
    
    for(int i = 0; i<N_FLOORS; i++){
        if(queue[i] == floor){
            return 1; //Hvis en av bestillingene i queue er den samme som etasjen så burde heisen stoppe
        }
    }

    if(d == DIRN_DOWN && get_button(BUTTON_HALL_DOWN,floor)==1){
        return 1;       //Hvis retningen på heisen går ned
    }                   //og retningen i en  etasjen går ned så burde heisen stoppe
    if(d == DIRN_UP && get_button(BUTTON_HALL_UP,floor) == 1){
        return 1;       //hvis retningen på heisen går opp
    }                   //og retningen i en etasje går opp burde heisen stoppe
    if(queue_is_empty() && no_request_in_current_direction(d) && (get_button(BUTTON_HALL_UP,floor)==1
    || get_button(BUTTON_HALL_DOWN,floor)==1)){         //hvis køen er tom og det er ingen bestillinger i en gitt retning
        return 1;                                       //og enten git etasje har en bestilling opp eller ned, burde heisen stoppe
    }

    if(((floor == 0) && (get_button(BUTTON_HALL_UP,0)==1||get_button(BUTTON_HALL_DOWN,0)==1))
    ||((floor==3) && (get_button(BUTTON_HALL_UP,3)==1 || get_button(BUTTON_HALL_DOWN,3)==1))){
        return 1;                           //hvis etasjen står i 0 og estillingen er enten opp eller ned
    }                                       //eller etasjen står i 3. og bestillingen er enten opp eller ned
    return 0;                               //burde den stoppe
    //ellers skal den bare kjøre
}

bool no_request_in_current_direction(MotorDirection direction){
    int button;

    if(direction == DIRN_DOWN){
        button = BUTTON_HALL_DOWN; //hvis retningen er opp er butten lik opp
    }
    if(direction == DIRN_UP){
        button = BUTTON_HALL_UP; //hvis retningen er opp er button lik ned
    }
    for(int i = 0; i<N_FLOORS;i++){
        if(get_button(button,i)==1){ //sjekker om noen av etasjene har bestilling ned eller opp, kommer an på direction
            return 0;               //Hvis det stemmer vil den returnere 0
        }
    }
    return 1;
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
        remove_button(floor,i);
        elevio_buttonLamp(floor, i, 0);      //Fjerner ordre for hver etasje
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
	set_button(button, floor); //setter en inn 1 matrisen

	/* 
	 * Add new order to queue 
	 */
	if (button == BUTTON_CAB) {
		for (int i = 0; i < N_FLOORS; i++) {
			if (queue[i] == floor || queue[i] == -1) { //hvis elementet i køen er lik etasjen eller har ingen bestilling 
				queue[i] = floor;                       // vil elementet bli oppdatert.
				break;
			}
		}
	}
}