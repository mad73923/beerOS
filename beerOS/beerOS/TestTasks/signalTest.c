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
		initSignal(&signal1);
		initSignal(&signal2);
		initSignal(&signal3);
	}
	while(1){
		if(currentTask->id == 0){
			waitSignal(&signal1);
			task1Cnt++;
			yieldTask();
			yieldTask();
			yieldTask();	
			sendSignal(&signal2);
		}else if(currentTask->id == 1){
			yieldTask();
			yieldTask();
			yieldTask();
			sendSignal(&signal1);
			waitSignal(&signal2);
			task2Cnt++;
			yieldTask();
			yieldTask();
			yieldTask();
			sendSignal(&signal3);	
		}else if(currentTask->id == 2){
			waitSignal(&signal3);
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
	rebootBeerOS();
}