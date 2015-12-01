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

typedef volatile struct{
	volatile uint16_t semaCnt;
	volatile taskControlBlock* firstWaiting;
}semaphore;

typedef volatile struct{
	volatile taskControlBlock* firstWaiting;
}signal;


static void __attribute__((always_inline)) enterCriticalSection(){
	disableInterrupts();
}

static void __attribute__((always_inline)) leaveCriticalSection(){
	enableInterrupts();
}

void initSemaphore(semaphore* sema, uint16_t cntInit);
void waitSemaphore(semaphore* sema);
void releaseSemaphore(semaphore* sema);

void waitSignal(signal* sig);

void sendSignal(signal* sig);

void yieldTask();

#endif /* SYNC_H_ */