/*
 * dummyTask.c
 *
 * Created: 11.11.2015 14:29:48
 *  Author: matweis
 */ 

#include "dummyTask.h"

volatile semaphore dummySema;
volatile semaphore dummySema2;

void dummyTask(){
	
	if(task == 0){
		initSemaphore(&dummySema, 1);
		initSemaphore(&dummySema2, 0);
	}
	
	while(1){
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		int i=0;
		while(i<100){
			if(task == 0){
				waitSemaphore(&dummySema);
			}else{
				waitSemaphore(&dummySema2);
			}

			i++;
			asm volatile ("nop");

			if(task == 0){
				releaseSemaphore(&dummySema2);
			}else{
				releaseSemaphore(&dummySema);
			}
		}
	}
	
}