#include <elev.h>
#include <stdio.h>
#include <timer.h>
#include <queue.h>

typedef enum {
	STATE_IDLE,
	STATE_RUNNING,
	STATE_DOOR_OPEN,
	STATE_STOP,
	STATE_NONE
}state;



void fsm_event_floor_reached(int floor);
void fsm_event_stop_button(void);
