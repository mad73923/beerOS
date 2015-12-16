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
	tcb[task].waitUntil = systemTime_ms + ms;
	while((firstSleeping.firstWaiting != NULL)){
		firstSleeping = firstSleeping.firstWaiting;
	}
	yieldTask();
}