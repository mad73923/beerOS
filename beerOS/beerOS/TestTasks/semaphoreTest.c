/*
 * SemaphoreTest.c
 *
 * Created: 09.12.2015 18:52:22
 *  Author: anreinha
 */ 

#include "testTasks.h"
#include "../sync.h"

volatile semaphore dummySema;
volatile semaphore dummySema2;
volatile semaphore dummySema3;

static volatile int task1Cnt = 0;
static volatile int task2Cnt = 0;
static volatile int task3Cnt = 0;

void initSemaphoreTest(){
	initTask(1, task1Stack, semaphoreTestTask, stacksize);
	initTask(1, task2Stack, semaphoreTestTask, stacksize);
	initTask(1, task3Stack, semaphoreTestTask, stacksize);
	initNextTest = &initSignalTest;
}

void semaphoreTestTask(){	
	if(currentTask->id == 0){
		initSemaphore(&dummySema, 1);
		initSemaphore(&dummySema2, 0);
		initSemaphore(&dummySema3, 0);
	}	
	asm volatile ("nop");
	while(1){
		if(currentTask->id == 0){
			waitSemaphore(&dummySema);
			task1Cnt++;
			releaseSemaphore(&dummySema2);
		}else if(currentTask->id == 1){
			waitSemaphore(&dummySema2);
			task2Cnt++;
			releaseSemaphore(&dummySema3);
		}else if(currentTask->id == 2){
			waitSemaphore(&dummySema3);
			task3Cnt++;
			releaseSemaphore(&dummySema);
		}
		asm volatile ("nop");
		if(task1Cnt - task2Cnt > 1 || task1Cnt - task2Cnt < -1){
			kernelPanic();
		}
		if(task2Cnt - task3Cnt > 1 || task2Cnt - task3Cnt < -1){
			kernelPanic();
		}
		if(task3Cnt > 3){
			break;
		}
	}
	rebootBeerOS();	
}