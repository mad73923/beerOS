/*
 * sync.c
 *
 * Created: 19.11.2015 17:48:56
 *  Author: anreinha
 */ 

#include "sync.h"

uint8_t enterCriticalSection(){
	uint8_t oldState = GLBINTFLG;
	disableInterrupts();
	return oldState;
}

void leaveCriticalSection(uint8_t oldState){
	if(oldState){
		enableInterrupts();
	}else{
		disableInterrupts();
	}
}

void semaphore_init(semaphore* sema, uint16_t cntInit){
	sema->semaCnt = cntInit;
	linkedList_init(&sema->waitingTasks);
	linkedList_init(&sema->freedBy);
}

void semaphore_request(semaphore* sema){
	uint8_t state = enterCriticalSection();
	while(sema->semaCnt <= 0){
		queueWaitingTask(&sema->waitingTasks, currentTask);
		scheduler_blockedByRessourceRequest(&sema->freedBy);
		leaveCriticalSection(state);
		task_yield();
		state = enterCriticalSection();
	}
	sema->semaCnt --;
	leaveCriticalSection(state);
}
void semaphore_release(semaphore* sema){
	uint8_t state = enterCriticalSection();
	sema->semaCnt ++;
	wakeupLinkedTasks(&sema->waitingTasks);
	scheduler_ressourceReleased(&sema->freedBy);
	leaveCriticalSection(state);
}

void signal_init(signal* sig){
	linkedList_init(&sig->waitingTasks);
	linkedList_init(&sig->freedBy);
}

void signal_wait(signal* sig){
	uint8_t state = enterCriticalSection();
	queueWaitingTask(&sig->waitingTasks, currentTask);
	scheduler_blockedByRessourceRequest(&sig->freedBy);
	leaveCriticalSection(state);
	task_yield();
}

void signal_send(signal* sig){
	uint8_t state = enterCriticalSection();
	wakeupLinkedTasks(&sig->waitingTasks);
	scheduler_ressourceReleased(&sig->freedBy);
	leaveCriticalSection(state);
}

void task_yield(){
	disableInterrupts();
	hardwareISR = 0;
	DISPISRVEC();
}