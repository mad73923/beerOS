/*
 * sync.c
 *
 * Created: 19.11.2015 17:48:56
 *  Author: anreinha
 */ 

#include "sync.h"


void initSemaphore(semaphore* sema, uint16_t cntInit){
	sema->semaCnt = cntInit;
	sema->firstWaiting = NULL;
}

void waitSemaphore(semaphore* sema){
	enterCriticalSection();
	if(sema->semaCnt == 0){
		queueWaitingTask(sema->firstWaiting, &tcb[task]);
		while(sema->semaCnt == 0){
			leaveCriticalSection();
			yieldTask();
			enterCriticalSection();
		}
	}
	sema->semaCnt --;
	leaveCriticalSection();
}
void releaseSemaphore(semaphore* sema){
	enterCriticalSection();
	sema->semaCnt ++;
	wakeupLinkedTasks(sema->firstWaiting);	
	leaveCriticalSection();
}

void initSignal(signal* sig){
	sig->firstWaiting = NULL;
}

void waitSignal(signal* sig){
	enterCriticalSection();
	queueWaitingTask(sig->firstWaiting, &tcb[task]);
	leaveCriticalSection();
	yieldTask();
}

void sendSignal(signal* sig){
	enterCriticalSection();
	wakeupLinkedTasks(sig->firstWaiting);
	leaveCriticalSection();
}

void yieldTask(){
	disableInterrupts();
	DISPISRVEC();
}