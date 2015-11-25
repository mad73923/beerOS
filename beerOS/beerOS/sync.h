/*
 * sync.h
 *
 * Created: 19.11.2015 17:49:46
 *  Author: anreinha
 */ 


#ifndef SYNC_H_
#define SYNC_H_

#include "hardware.h"
#include "task.h"
#include "beerOS.h"

extern taskControlBlock tcb[4]; 

typedef volatile struct semaphore{
	volatile uint16_t semaCnt;
	volatile taskControlBlock* firstWaiting;
}semaphore;


void enterCriticalSection();
void leaveCriticalSection();

void initSemaphore(semaphore* sema, uint16_t cntInit);
void waitSemaphore(semaphore* sema);
void releaseSemaphore(semaphore* sema);

void yieldTask();

#endif /* SYNC_H_ */