/*
 * pipTest.c
 *
 * Created: 04.02.2016 02:18:57
 *  Author: matweis
 */ 
#include "testTasks.h"
#include "../sync.h"

volatile semaphore dummySema;

static volatile int task1Cnt = 0;
static volatile int task2Cnt = 0;
static volatile int task3Cnt = 0;

void initPipTest(){
	initTask(0, task1Stack, semaphoreTestTask, stacksize);
	initTask(1, task2Stack, semaphoreTestTask, stacksize);
	initTask(2, task3Stack, semaphoreTestTask, stacksize);
}

void pipTestTask(){	
	if(currentTask->id == 0){
		semaphore_init(&dummySema, 1);
	}	
	asm volatile ("nop");
	while(1){
		if(currentTask->id == 0){
			semaphore_request(&dummySema);
			asm volatile ("nop");			
		}else if(currentTask->id == 1){
			asm volatile ("nop");
		}else if(currentTask->id == 2){
			semaphore_release(&dummySema);
		}
		asm volatile ("nop");
	}
	beerOS_reboot();	
}