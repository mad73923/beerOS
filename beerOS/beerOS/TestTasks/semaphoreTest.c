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
		semaphore_init(&dummySema, 1);
		semaphore_init(&dummySema2, 0);
		semaphore_init(&dummySema3, 0);
	}	
	asm volatile ("nop");
	while(1){
		if(currentTask->id == 0){
			semaphore_wait(&dummySema);
			task1Cnt++;
			semaphore_release(&dummySema2);
		}else if(currentTask->id == 1){
			semaphore_wait(&dummySema2);
			task2Cnt++;
			semaphore_release(&dummySema3);
		}else if(currentTask->id == 2){
			semaphore_wait(&dummySema3);
			task3Cnt++;
			semaphore_release(&dummySema);
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
	beerOS_reboot();	
}