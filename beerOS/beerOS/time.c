/*
 * time.c
 *
 * Created: 09.12.2015 19:52:59
 *  Author: matweis
 */ 

#include "time.h"

volatile uint32_t systemTime_ms = 0;
volatile linkedSyncObject firstSleeping;

void sleep_ms(uint32_t ms){
	enterCriticalSection();
	tcb[task].state = WAITING;
	tcb[task].waitUntil = systemTime_ms + ms;
	
	if(firstSleeping.firstWaiting != NULL){
		linkedSyncObject* temp = &firstSleeping;
		while(temp->firstWaiting != NULL){
			if(temp->firstWaiting->waitUntil < systemTime_ms + ms){
				temp = temp->firstWaiting;
			}else{
				tcb[task].semaNextWaiting = temp->firstWaiting;
				break;
			}
		}
		temp->firstWaiting = &tcb[task];
	}else{
		firstSleeping.firstWaiting = &tcb[task];
	}
	yieldTask();
}