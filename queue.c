#include <stdio.h>
#include "queue.h"
#include "elev.h"


int queue_matrix[N_FLOORS][N_BUTTONS] =
{
{ 0,0,0 },
{ 0,0,0 },
{ 0,0,0 },
{ 0,0,0 }
};


int queue_current_floor_in_queue() { ///////----//////
	if (((queue_matrix[elev_get_floor_sensor_signal()][BUTTON_COMMAND] == 1)) || (queue_matrix[elev_get_floor_sensor_signal()][BUTTON_CALL_UP] == current_dir) || (queue_matrix[elev_get_floor_sensor_signal()][BUTTON_CALL_DOWN] == -current_dir))){
	return 1;
   }
	else {
		return 0;
	}


}

void queue_add_order_to_queue(int floor, elev_button_type_t button_type) {
	queue_matrix[floor][button_type] = 1;
	elev_set_button_lamp(button_type, floor, 1);
}

void queue_remove_order_from_queue(int floor, elev_button_type_t button_type) {
	queue_matrix[floor][button_type] = 0;
	elev_set_button_lamp(button_type, floor, 0);
}

void queue_reset_queue(void) {
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			if (!(j == BUTTON_CALL_UP && i == N_FLOORS - 1)&& !(j == BUTTON_CALL_DOWN && i == 0))
				queue_remove_order_from_queue(i, j);
		}
	}
}

int queue_is_not_empty(void) {
	int flag = 0;
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++)
			if (queue_matrix[i][j] == 1) {
				flag = 1;
				return(flag);
			}
	}
}


