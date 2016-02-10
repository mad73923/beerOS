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

volatile signal dummySignal;

void initPrioTest(){
	initTask(0, task1Stack, prioTestTask, stacksize);
	initTask(1, task2Stack, prioTestTask, stacksize);
	initTask(2, task3Stack, prioTestTask, stacksize);
	initNextTest = &initPipTest;	
}

void prioTestTask(){
	if(currentTask->id == 0){
		signal_init(&dummySignal);
	}
	
	while(1){
		if(currentTask->id == 0){
			task_yield();
			task_yield();
			task_yield();
			signal_wait(&dummySignal);
			currentTask->prio = (currentTask->prio+1)%2;
			task1Cnt++;
		}else if(currentTask->id == 1){
			task_yield();			
			task2Cnt++;
			signal_wait(&dummySignal);
			currentTask->prio = (currentTask->prio+1)%2;
		}else if(currentTask->id == 2){
			signal_send(&dummySignal);
			task3Cnt++;
			task_yield();
		}		
		asm volatile ("nop");
		if(task1Cnt - task2Cnt > 1 || task1Cnt - task2Cnt < -1){
			kernelPanic();
		}
		if(task2Cnt - task3Cnt > 1 || task2Cnt - task3Cnt < -1){
			kernelPanic();
		}
		if(task3Cnt > 4){
			break;
		}
	}
	beerOS_reboot();
}