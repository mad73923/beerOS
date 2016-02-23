/*
 * rebootTest.c
 *
 * Created: 29.01.2016 11:39:31
 *  Author: matweis
 */ 
#include "testTasks.h"
#include "../time.h"

void rebootTestTask(){
	time_sleep_ms(1);
	beerOS_reboot();
}