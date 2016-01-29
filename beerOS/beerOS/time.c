/*
 * time.c
 *
 * Created: 09.12.2015 19:52:59
 *  Author: matweis
 */ 

#include "time.h"

volatile uint32_t systemTime_ms = 0;
volatile linkedSyncObject allSleepingTasks;

void time_init(){
	linkedList_init(&allSleepingTasks.waitingTasks);
}

void sleep_ms(uint32_t ms){
	enterCriticalSection();
	currentTask->state = WAITING;
	currentTask->waitUntil = systemTime_ms + ms;
	
	if(linkedList_length(&allSleepingTasks.waitingTasks) > 0){
		taskControlBlock* nextTask;
		uint8_t index = 0;
		while(linkedList_iter(&allSleepingTasks.waitingTasks, &nextTask)){
			if(nextTask->waitUntil > currentTask->waitUntil){
				linkedList_add(&allSleepingTasks.waitingTasks, currentTask, index);
				allSleepingTasks.waitingTasks.isIterating = 0;
				break;
			}
			index++;
		}
	}	
	linkedList_append(&allSleepingTasks.waitingTasks, currentTask);
	yieldTask();
}

void wakeupPendingTasks(){
	if(linkedList_length(&allSleepingTasks.waitingTasks) > 0){
		taskControlBlock* nextTask;
		uint8_t index = 0;
		while(linkedList_iter(&allSleepingTasks.waitingTasks, &nextTask)){
			if(nextTask->waitUntil <= systemTime_ms){
				nextTask->state = READY;
				nextTask->waitUntil = 0;
				linkedList_remove(&allSleepingTasks.waitingTasks, index);
				//TODO dirty fix
				allSleepingTasks.waitingTasks.currentIndex--;
				index--;
				scheduler_enqueueTask(nextTask);
			}else{
				allSleepingTasks.waitingTasks.isIterating = 0;
				break;				
			}
			index++;
		}
	}
}

uint32_t getTime(){
	return systemTime_ms;
}