#pragma once


void clear_floor_light(int floor);

void clear_all_lights();

void update_lights_from_request();
int get_light(int floor, int button);
void show_lights();