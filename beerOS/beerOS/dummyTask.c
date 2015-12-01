/*
 * dummyTask.c
 *
 * Created: 11.11.2015 14:29:48
 *  Author: matweis
 */ 

#include "dummyTask.h"

volatile semaphore dummySema;
volatile semaphore dummySema2;

volatile signal signal1;

void dummyTaskSemaTest(){
	
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

void dummyTaskSignalTest(){
	if(task == 0){
		initSignal(&signal1);
	}

	while(1){
		int i = 0;
		if(task == 0){
			while(i<100){
				i++;
			}
			sendSignal(&signal1);
		}else{
			waitSignal(&signal1);
			i++;
		}
	}
}