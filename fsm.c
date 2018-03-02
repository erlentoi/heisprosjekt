#include <elev.h>
#include <stdio.h>
#include <timer.h>
#include <fsm.h>
#include <queue.h>

////Globale variabler, initaliseres
state current_state = STATE_IDLE;
elev_motor_direction_t current_dir = DIRN_STOP;
int previous_floor;



int fsm_init() {
	if (elev_get_floor_sensor_signal() == -1){ ////////-------/////////
		elev_set_motor_direction(DIRN_STOP);
	}
	else {
		current_state = STATE_IDLE;
	}
	return 1;
}

void fsm_event_stop_button() {
	switch (current_state) {
		case(STATE_STOP):
			break;
		case (STATE_DOOR_OPEN):
			current_state = STATE_STOP;
			break;
		case(STATE_IDLE):
			if (elev_get_floor_sensor_signal() != -1) {
				elev_set_door_open_lamp(1);
			}
			current_state = STATE_STOP;
			break;
		case(STATE_RUNNING):
			elev_set_motor_direction(0);
			if (elev_get_floor_sensor_signal() != -1) {
				elev_set_door_open_lamp(1);
			}
			current_state = STATE_STOP;
			break;
	}
	elev_set_stop_lamp(1);
	queue_reset_queue();
	while (elev_get_stop_signal()) {	
	}
	elev_set_stop_lamp(0);
	if (elev_get_floor_sensor_signal() != -1) {
		current_state = STATE_DOOR_OPEN;
		fsm_event_door_open();
	}
	else {
		current_state = STATE_IDLE;
	}
}

void sfm_event_button_pressed(elev_button_type_t type, int floor) {			///////////////---------/////////////////////
	queue_add_order_to_queue(floor, type);
	elev_set_button_lamp(type, floor, 1);							
	if (current_state == STATE_IDLE){

		elev_set_motor_direction()
	
	}
}
	
void fsm_event_floor_reached(int floor) {
	if ((queue_matrix[floor][BUTTON_COMMAND] == 1) || (queue_matrix[floor][BUTTON_CALL_UP] == current_dir) || (queue_matrix[floor][BUTTON_CALL_DOWN] == -current_dir)) {
		current_state = STATE_DOOR_OPEN;
		elev_set_motor_direction(0);
		if (queue_matrix[floor][BUTTON_COMMAND] == 1) {
			queue_remove_order_from_queue(floor, BUTTON_COMMAND);
		}
		if (queue_matrix[floor][BUTTON_CALL_UP] == current_dir) {
			queue_remove_order_from_queue(floor, BUTTON_CALL_UP);
		}
		else if (queue_matrix[floor][BUTTON_CALL_DOWN] == -current_dir) {
			queue_remove_order_from_queue(floor, BUTTON_CALL_DOWN);
		}
	fsm_event_door_open(); //////Døren må vel åpnes her?///////
	}
	if (current_state == STATE_NONE) { ///////////////////////////////----------//////////////////////
		elev_set_motor_direction(DIRN_STOP);
		current_state = STATE_IDLE;

	}
}

void fsm_event_idle() {
	if ((queue_matrix[elev_get_floor_sensor_signal()][BUTTON_COMMAND] == 1) || (queue_matrix[elev_get_floor_sensor_signal()][BUTTON_CALL_DOWN] == 1) || (queue_matrix[elev_get_floor_sensor_signal()][BUTTON_CALL_UP] == 1)) { /////////----//////
		current_state = STATE_DOOR_OPEN;
		fsm_event_door_open();
	}
	else{
		if (queue_is_not_empty()){
					current_state = STATE_RUNNING;
					fsm_find_initial_direction(); //////setter current_dir
					elev_set_motor_direction(current_dir);
				}
	}
}


void fsm_event_door_open(void) {
	elev_set_door_open_lamp(1);
	elev_set_button_lamp(BUTTON_CALL_DOWN, elev_get_floor_sensor_signal(), 0);
	elev_set_button_lamp(BUTTON_CALL_UP, elev_get_floor_sensor_signal(), 0);
	elev_set_button_lamp(BUTTON_COMMAND, elev_get_floor_sensor_signal(), 0);
	timer_door_timer();
	elev_set_door_open_lamp(0);
}




void fsm_find_direction(void) {



}

void fsm_find_initial_direction(void) {
	int order_bellow = 0;
	int order_above = 0;

	if(   ) {

	}



	/////sjekker om det er bestillinger UNDER nåværende etasje
	for (int i = 0; i < elev_get_floor_sensor_signal(); i++)
		if ((queue_matrix[i][BUTTON_COMMAND] == 1) || (queue_matrix[i][BUTTON_CALL_UP] == 1) || (queue_matrix[i][BUTTON_CALL_DOWN] == 1)) {
			order_bellow = 1;
			break;
		}
	/////sjekker om det er bestillinger OVER nåværende etasje

	for (int i = elev_get_floor_sensor_signal() + 1 ; i <= N_FLOORS; i++)
		if ((queue_matrix[i][BUTTON_COMMAND] == 1) || (queue_matrix[i][BUTTON_CALL_UP] == 1) || (queue_matrix[i][BUTTON_CALL_DOWN] == 1)) {
			order_above = 1;
			break;
		}
	if ((order_above == 1) && (order_bellow == 0))
		current_dir = DIRN_UP;
	else if ((order_above == 0) && (order_bellow == 1))
		current_dir = DIRN_DOWN;
	else if ((order_above == 1) && (order_bellow == 1) && (N_FLOORS - elev_get_floor_sensor_signal() + 1) <= 0.5*N_FLOORS)
		current_dir = DIRN_DOWN;
	else if (elev_get_floor_sensor_signal() == 3) {
		current_dir = DIRN_DOWN;////////////////--------------///////////
	}
	else if (elev_get_floor_sensor_signal() == 0) {
		current_dir = DIRN_UP; ////////////////--------------///////////
	}
	else
		current_dir = DIRN_UP;
}

//////////Hvordan gå fra STATE_IDLE til STATE_RUNNING? Ny "else if" i find_initial_direction??? ///////////////////




//void fsm_run(void) {
//	switch (current_state) {
//	case(STATE_RUNNING):
//		fsm_event_floor_reached(); ///////////--------/////////////
//		break;
//
//	case(STATE_DOOR_OPEN):
//		if (queue_is_not_empty){
//			current_state = STATE_RUNNING;
//
//		}
//		
//		break;
//
//	case(STATE_IDLE):
//		fsm_event_idle(); ///////////--------/////////////7
//		break;
//
//	case(STATE_STOP):
//
//
//
//	}
//
//}







											//
											//void fsm_event_order_in_queue(elev_button_type_t button, int floor) {
											//	switch (current_state) {
											//	case(STATE_IDLE):
											//		if (elev_get_floor_sensor_signal() == floor) {
											//			current_state = STATE_DOOR_OPEN;
											//		}
											//		else {
											//			elev_set_motor_direction(fsm_get_direction());//////TODO
											//			current_state = STATE_RUNNING;
											//		}
											//		break;
											//	case(STATE_DOOR_OPEN):
											//
											//		break;
											//	case(STATE_RUNNING):
											//
											//		break;
											//	}
											//}