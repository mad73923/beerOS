/*
 * sync.c
 *
 * Created: 19.11.2015 17:48:56
 *  Author: anreinha
 */ 

#include "sync.h"

void enterCriticalSection(){
	disableInterrupts();
}

void leaveCriticalSection(){
	enableInterrupts();
}


void initSemaphore(semaphore* sema, uint16_t cntInit){
	sema->semaCnt = cntInit;	
}
void waitSemaphore(semaphore* sema, taskControlBlock* task){
	enterCriticalSection();
	while(sema->semaCnt = 0){
		task->state = WAITING;
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
	leaveCriticalSection();
	wakeupLinkedTasks(sema->firstWaiting);
}

void yieldTask(){
	disableInterrupts();
	DISPISRVEC();
}