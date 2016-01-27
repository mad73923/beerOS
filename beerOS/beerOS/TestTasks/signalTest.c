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

void signalTestTask(){
	if(task == 0){
		initSignal(&signal1);
		initSignal(&signal2);
		initSignal(&signal3);
	}
	while(1){
		if(task == 0){
			waitSignal(&signal1);
			task1Cnt++;	
			yieldTask();
			yieldTask();
			yieldTask();	
			sendSignal(&signal2);
		}else if(task == 1){
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
		}else if(task == 2){
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
	}
}