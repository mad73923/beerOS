/*
 * time.c
 *
 * Created: 09.12.2015 19:52:59
 *  Author: matweis
 */ 

#include "time.h"

volatile uint32_t systemTime_ms = 0;
volatile likedSyncObject firstSleeping;

void sleep_ms(uint32_t ms){
	enterCriticalSection();
	tcb[task].state = WAITING;
	tcb[task].waitUntil = systemTime_ms + ms;
	uint8_t done = 0;
	while(!done){
		if(firstSleeping.firstWaiting != NULL){
			if(firstSleeping.firstWaiting->waitUntil < systemTime_ms + ms){
				done = 1;
			}
		}else{
			done = 1;
		}
		if(!done){
			firstSleeping.firstWaiting = firstSleeping.firstWaiting->semaNextWaiting;		
		}
	}
	firstSleeping.firstWaiting = &tcb[task];
	yieldTask();
}