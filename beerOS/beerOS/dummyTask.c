/*
 * dummyTask.c
 *
 * Created: 11.11.2015 14:29:48
 *  Author: matweis
 */ 

#include "dummyTask.h"

volatile semaphore dummySema;
volatile semaphore dummySema2;

volatile int task1Cnt = 0;
volatile int task2Cnt = 0;

void dummyTaskSemaTest(){	
	if(task == 0){
		initSemaphore(&dummySema, 1);
		initSemaphore(&dummySema2, 0);
	}	
	asm volatile ("nop");
	while(1){
		if(task == 0){
			waitSemaphore(&dummySema);
			task1Cnt++;
			releaseSemaphore(&dummySema2);
		}else{
			waitSemaphore(&dummySema2);
			task2Cnt++;
			releaseSemaphore(&dummySema);
		}
		asm volatile ("nop");
		if(task1Cnt - task2Cnt > 1 || task1Cnt - task2Cnt < -1){
			kernelPanic();
		}
	}	
}


volatile signal signal1;


void dummyTaskSignalTest(){
	if(task == 0){
		initSignal(&signal1);
	}
	while(1){
		if(task == 0){
			yieldTask();
			yieldTask();
			sendSignal(&signal1);
			task1Cnt++;
		}else{
			waitSignal(&signal1);
			task2Cnt++;
		}
		asm volatile ("nop");
		if(task1Cnt - task2Cnt > 1 || task1Cnt - task2Cnt < -1){
			kernelPanic();
		}
	}
}