/*
 * time.c
 *
 * Created: 09.12.2015 19:52:59
 *  Author: matweis
 */ 

#include "time.h"

volatile uint32_t systemTime_ms = 0;
volatile linkedSyncObject firstSleeping;

volatile taskControlBlock* tmpSleeping;
volatile taskControlBlock* next;

void sleep_ms(uint32_t ms){
	enterCriticalSection();
	currentTask->state = WAITING;
	currentTask->waitUntil = systemTime_ms + ms;
	
	if(firstSleeping.firstWaiting != NULL){
		linkedSyncObject* temp = &firstSleeping;
		while(temp->firstWaiting != NULL){
			if(temp->firstWaiting->waitUntil < systemTime_ms + ms){
				temp = temp->firstWaiting;
			}else{
				currentTask->semaNextWaiting = temp->firstWaiting;
				break;
			}
		}
		temp->firstWaiting = currentTask;
	}else{
		firstSleeping.firstWaiting = currentTask;
	}
	yieldTask();
}

void wakeupPendingTasks(){
	tmpSleeping = firstSleeping.firstWaiting;
	Queue* targetPrioQueue;	
	while(tmpSleeping != NULL){
		if(tmpSleeping->waitUntil <= systemTime_ms){
			tmpSleeping->state = READY;
			tmpSleeping->waitUntil = 0;
				
			if(tmpSleeping->prio > maxPrio){
				kernelPanic();
			}
			linkedList_get(&prioQueueList, tmpSleeping->prio, &targetPrioQueue);
			queue_push(targetPrioQueue, tmpSleeping);
				
			next = tmpSleeping->semaNextWaiting;
			tmpSleeping->semaNextWaiting = NULL;
			tmpSleeping = next;
			firstSleeping.firstWaiting = next;
		}else{				
			break;
		}
}

uint32_t getTime(){
	return systemTime_ms;
}