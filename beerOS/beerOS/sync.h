/*
 * sync.h
 *
 * Created: 19.11.2015 17:49:46
 *  Author: anreinha
 */ 


#ifndef SYNC_H_
#define SYNC_H_

#include "beerOSTypes.h"
#include "scheduler.h"
#include "hardware.h"

typedef volatile struct{
	LinkedList waitingTasks;
	volatile int16_t semaCnt;
}semaphore;

typedef volatile struct{
	LinkedList waitingTasks;
}signal;

extern volatile uint8_t hardwareISR;
extern taskControlBlock* currentTask;

static void __attribute__((always_inline)) enterCriticalSection(){
	disableInterrupts();
}

static void __attribute__((always_inline)) leaveCriticalSection(){
	enableInterrupts();
}

void semaphore_init(semaphore* sema, uint16_t cntInit);
void semaphore_wait(semaphore* sema);
void semaphore_release(semaphore* sema);

void signal_init(signal* sig);
void signal_wait(signal* sig);
void signal_send(signal* sig);

void task_yield();

#endif /* SYNC_H_ */