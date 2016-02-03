/*
 * SignalTest.c
 *
 * Created: 09.12.2015 18:53:21
 *  Author: anreinha
 */

#include "testTasks.h"
#include "../sync.h"

volatile signal signal1;
volatile signal signal2;
volatile signal signal3;

static volatile int task1Cnt = 0;
static volatile int task2Cnt = 0;
static volatile int task3Cnt = 0;

void initSignalTest(){
	initTask(1, task1Stack, signalTestTask, stacksize);
	initTask(1, task2Stack, signalTestTask, stacksize);
	initTask(1, task3Stack, signalTestTask, stacksize);
	initNextTest = &initSleepTest;
}

void signalTestTask(){
	if(currentTask->id == 0){
		signal_init(&signal1);
		signal_init(&signal2);
		signal_init(&signal3);
	}
	while(1){
		if(currentTask->id == 0){
			signal_wait(&signal1);
			task1Cnt++;
			task_yield();
			task_yield();
			task_yield();	
			signal_send(&signal2);
		}else if(currentTask->id == 1){
			task_yield();
			task_yield();
			task_yield();
			signal_send(&signal1);
			signal_wait(&signal2);
			task2Cnt++;
			task_yield();
			task_yield();
			task_yield();
			signal_send(&signal3);	
		}else if(currentTask->id == 2){
			signal_wait(&signal3);
			task3Cnt++;
		}
		asm volatile ("nop");
		if(task1Cnt - task2Cnt > 1 || task1Cnt - task2Cnt < -1){
			kernelPanic();
		}
		if(task2Cnt - task3Cnt > 1 || task2Cnt - task3Cnt < -1){
			kernelPanic();
		}
		
		if(task3Cnt > 2){
			break;
		}
	}
	beerOS_reboot();
}