#include "elev.h"
#include <stdio.h>
#include "timer.h"
#include "fsm.h"
#include "queue.h"

int current_floor = -1;
int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
	
    printf("Press STOP button to stop elevator and exit program.\n");

	if (!fsm_init()) {
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}
	/////////////////////////////
	
	/////////////////////////////
	int floor_signal;
	while (1) {
		
		if (elev_get_stop_signal())
			fsm_event_stop_button();

		floor_signal = elev_get_floor_sensor_signal();
		
		if (floor_signal != -1); {
			fsm_event_floor_reached(floor_signal);
		}
		
		for (int i = 0; i < N_FLOORS; i++) {
			for (int j = 0; j < N_BUTTONS; j++) {
				if (!(j == BUTTON_CALL_UP && i == N_FLOORS - 1) && !(j == BUTTON_CALL_DOWN && i == 0) && (elev_get_button_signal(i, j))){
					fsm_button_pressed(j, i);
					queue_add_to_queue(i, j);
				}
			}
		}



		/////////////////////Sjekker for events///////////////////////////////
		
		//////hvis queue IKKE er tom
		if (queue_is_not_empty()) {
		
				
		}
		////////hvis heisen når en etasje den skal stoppe i
		if (queue_current_floor_in_queue()) {

		}

		////////hvis queue ER tom
		if (!queue_is_not_empty()) {


		}

		//////hvis heisen står i en etasje og noen vil inn
		if (			) {


		}


		





		
		




	


		

	}












    return 0;
}
