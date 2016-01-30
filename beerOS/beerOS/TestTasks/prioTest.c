/*
 * prioTest.c
 *
 * Created: 27.01.2016 19:54:49
 *  Author: matweis
 */ 
#include "testTasks.h"
#include "../sync.h"

static volatile int task1Cnt = 0;
static volatile int task2Cnt = 0;
static volatile int task3Cnt = 0;

volatile semaphore dummySema;
volatile signal dummySignal;

void initPrioTest(){
	initTask(0, task1Stack, prioTestTask, stacksize);
	initTask(1, task2Stack, prioTestTask, stacksize);
	initTask(2, task3Stack, prioTestTask, stacksize);
}

void prioTestTask(){
	if(currentTask->id == 0){
		initSemaphore(&dummySema, 0);
		initSignal(&dummySignal);
	}
	
	while(1){
		if(currentTask->id == 0){
			yieldTask();
			yieldTask();
			yieldTask();
			waitSemaphore(&dummySema);
			task1Cnt++;
		}else if(currentTask->id == 1){
			releaseSemaphore(&dummySema);
			task2Cnt++;
			waitSignal(&dummySignal);			
		}else if(currentTask->id == 2){
			sendSignal(&dummySignal);
			task3Cnt++;
			yieldTask();
		}		
		asm volatile ("nop");
		if(task1Cnt - task2Cnt > 1 || task1Cnt - task2Cnt < -1){
			kernelPanic();
		}
		if(task2Cnt - task3Cnt > 1 || task2Cnt - task3Cnt < -1){
			kernelPanic();
		}
		if(task3Cnt >= 2){
			break;
		}
	}
	rebootBeerOS();
}