/*
 * pipTest.c
 *
 * Created: 04.02.2016 02:18:57
 *  Author: matweis
 */ 
#include "testTasks.h"
#include "../sync.h"

volatile semaphore dummySema;
volatile signal dummySignal;

static volatile int task1Cnt = 0;
static volatile int task2Cnt = 0;
static volatile int task3Cnt = 0;

void initPipTest(){
	initTask(0, task1Stack, pipTestTask, stacksize);
	initTask(1, task2Stack, pipTestTask, stacksize);
	initTask(2, task3Stack, pipTestTask, stacksize);
	scheduler_init = &scheduler_initPrioInheritance;
	initNextTest = &initMemoryManagementTest;
}

void pipTestTask(){	
	if(currentTask->id == 0){
		semaphore_init(&dummySema, 0);
		signal_init(&dummySignal);
		signal_wait(&dummySignal);
	}else if(currentTask->id == 1){
		signal_wait(&dummySignal);	
	}else if(currentTask->id == 2){
		linkedList_append(&dummySema.freedBy, currentTask);
		signal_send(&dummySignal);
		task_yield();
	}
	asm volatile ("nop");
	while(1){
		if(currentTask->id == 0){
			semaphore_request(&dummySema);
			task1Cnt++;
			asm volatile ("nop");
		}else if(currentTask->id == 1){
			task2Cnt++;
			asm volatile ("nop");
		}else if(currentTask->id == 2){
			semaphore_release(&dummySema);
			task3Cnt++;
			asm volatile ("nop");		
		}
		if(task1Cnt - task3Cnt > 1 || task1Cnt - task3Cnt < -1){
			kernelPanic();
		}
		if(task2Cnt){
			kernelPanic();
		}
		if(task3Cnt > 3){
			break;
		}
	}
	beerOS_reboot();
}