/*
 * dummyTask.c
 *
 * Created: 11.11.2015 14:29:48
 *  Author: matweis
 */ 

#include "dummyTask.h"

volatile semaphore dummySema;

void dummyTask(){
	
	if(task == 0){
		initSemaphore(&dummySema, 1);
	}
	
	while(1){
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		int i=0;
		waitSemaphore(&dummySema, &tcb[task]);		
		while(i<100){
			i++;
			asm volatile ("nop");
		}
		releaseSemaphore(&dummySema);
		
	}
	
}