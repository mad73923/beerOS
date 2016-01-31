/*
 * sync.c
 *
 * Created: 19.11.2015 17:48:56
 *  Author: anreinha
 */ 

#include "sync.h"


void initSemaphore(semaphore* sema, uint16_t cntInit){
	sema->semaCnt = cntInit;
	linkedList_init(&sema->waitingTasks);
}

void waitSemaphore(semaphore* sema){
	enterCriticalSection();
	while(sema->semaCnt <= 0){
		queueWaitingTask(&sema->waitingTasks, currentTask);			
		leaveCriticalSection();
		yieldTask();
		enterCriticalSection();
	}
	sema->semaCnt --;
	leaveCriticalSection();
}
void releaseSemaphore(semaphore* sema){
	enterCriticalSection();
	sema->semaCnt ++;
	wakeupLinkedTasks(&sema->waitingTasks);
	leaveCriticalSection();
}

void initSignal(signal* sig){
	linkedList_init(&sig->waitingTasks);
}

void waitSignal(signal* sig){
	enterCriticalSection();
	queueWaitingTask(&sig->waitingTasks, currentTask);
	leaveCriticalSection();
	yieldTask();
}

void sendSignal(signal* sig){
	enterCriticalSection();
	wakeupLinkedTasks(&sig->waitingTasks);
	leaveCriticalSection();
}

void yieldTask(){
	disableInterrupts();
	hardwareISR = 0;
	DISPISRVEC();
}