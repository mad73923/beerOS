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
	LinkedList freedBy;
	int16_t semaCnt;
}semaphore;

typedef volatile struct{
	LinkedList waitingTasks;
	LinkedList freedBy;
}signal;

extern volatile uint8_t hardwareISR;
extern taskControlBlock* currentTask;

uint8_t enterCriticalSection();
void leaveCriticalSection(uint8_t oldState);

void semaphore_init(semaphore* sema, uint16_t cntInit);
void semaphore_request(semaphore* sema);
void semaphore_release(semaphore* sema);

void signal_init(signal* sig);
void signal_wait(signal* sig);
void signal_send(signal* sig);

void task_yield();

#endif /* SYNC_H_ */