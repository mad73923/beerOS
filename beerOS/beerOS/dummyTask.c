/*
 * dummyTask.c
 *
 * Created: 11.11.2015 14:29:48
 *  Author: matweis
 */ 

#include "dummyTask.h"

void semaphoreTestTask(){
	while(1){
		asm volatile ("nop");	
	}
}