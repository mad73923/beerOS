/*
 * sleepTest.c
 *
 * Created: 16.12.2015 18:55:19
 *  Author: matweis
 */ 

#include "testTasks.h"

#include "../time.h";

void sleepTestTask(){
	while(1){
		asm volatile ("nop");		
		sleep_ms(2);	
	}
}