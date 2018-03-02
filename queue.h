#include <stdio.h>
#include "elev.h"
#include "timer.h"

#define  N_BUTTONS 3


int queue_matrix[N_FLOORS][N_BUTTONS];

void queue_add_order_to_queue(int floor, elev_button_type_t button_type);
void queue_remove_order_from_queue(int floor, elev_button_type_t button_type);
void queue_reset_queue(void);
int queue_is_not_empty(void);
int queue_current_floor_in_queue(void);///////----//////