/*
 * sleepTest.c
 *
 * Created: 16.12.2015 18:55:19
 *  Author: matweis
 */ 

#include "testTasks.h"

#include "../time.h";

extern volatile uint32_t systemTime_ms;

static volatile int task1Cnt = 0;
static volatile int task2Cnt = 0;
static volatile int task3Cnt = 0;

void initSleepTest(){
	initTask(0, task1Stack, sleepTestTask, stacksize);
	initTask(0, task2Stack, sleepTestTask, stacksize);
	initTask(0, task3Stack, sleepTestTask, stacksize);
	initNextTest = &initLinkedListTest;
}

void sleepTestTask(){
	if(currentTask->id == 0){
		// lower timer period to 500us for faster testing
		TCF0.PER = 0x4650;
	}			
	
	while(1){
		if(currentTask->id == 0){
			sleep_ms(2);
			task1Cnt++;
			if(task1Cnt * 2 != systemTime_ms){
				kernelPanic();
			}
		}else if(currentTask->id == 1){
			sleep_ms(3);
			task2Cnt++;
			if(task2Cnt * 3 != systemTime_ms){
				kernelPanic();
			}
		}else{
			sleep_ms(5);
			task3Cnt++;
			if(task3Cnt * 5 != systemTime_ms){
				kernelPanic();
			}
		}
		if(task3Cnt == 2){
			break;
		}
	}
	rebootBeerOS();
}