#include "driver/elevio.h"


typedef enum orders {
	NO_ORDER = -1,               
	ORDER_UP = BUTTON_HALL_UP,
	ORDER_DOWN = BUTTON_HALL_DOWN,
	ORDER_ALL = BUTTON_CAB     
} order_list;

void add_order_queue(int floor, order_list order);

void clear_queue_floor(int floor);

void clear_all_in_queue();

void update_queue_from_request();

int orders_over_queue(int floor);
int orders_under_queue(int floor);

order_list get_order(int f);

int stop_queue(int floor, MotorDirection d);

void show_queue();
void test_queue();
int get_queue(int floor);

