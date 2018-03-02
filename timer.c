#include <stdio.h>
#include "timer.h"
#include <time.h>

static double start_time= 0;



void startTimer(void) {

	start_time = time(NULL);
}

int has_Three_Seconds_Passed(void){
	if (((time(NULL)-start_time)>=3)){ //////////////////////-----------------//////////////////
		return 1;	
		}
	else{
		return 0;
	}
}
