/*
 * time.c
 *
 * Created: 09.12.2015 19:52:59
 *  Author: matweis
 */ 

#include "time.h"

volatile uint32_t systemTime_ms = 0;
volatile LinkedList allSleepingTasks;

void time_init(){
	linkedList_init(&allSleepingTasks);
}

void time_sleep_ms(uint32_t ms){
	enterCriticalSection();
	currentTask->state = WAITING;
	currentTask->waitUntil = systemTime_ms + ms;
	uint8_t taskAdded = 0;
	uint8_t length = linkedList_length(&allSleepingTasks);
	if(length){
		taskControlBlock* nextTask;
		uint8_t index = 0;
		for(int i = 0; i < length; i++){
			linkedList_get(&allSleepingTasks, index, &nextTask);
			if(nextTask->waitUntil > currentTask->waitUntil){
				linkedList_add(&allSleepingTasks, currentTask, index);
				taskAdded = 1;
				break;
			}
			index++;
		}
		if(!taskAdded){
			linkedList_append(&allSleepingTasks, (void*) currentTask);
		}
	}else{
		linkedList_append(&allSleepingTasks, currentTask);
	}
	task_yield();
}

void time_wakeupPendingTasks(){
	uint8_t length = linkedList_length(&allSleepingTasks);
	if(length){
		taskControlBlock* nextTask;
		for(int i = 0; i<length; i++){
			linkedList_get(&allSleepingTasks, i, &nextTask);
			if(nextTask->waitUntil <= systemTime_ms){
				nextTask->state = READY;
				nextTask->waitUntil = 0;
				scheduler_enqueueTask(nextTask);
				linkedList_remove(&allSleepingTasks, i);
				length--;
				i--;
			}else{
				break;
			}				
		}
	}
}

uint32_t time_getSystemTime(){
	return systemTime_ms;
}