/*
 * sync.c
 *
 * Created: 19.11.2015 17:48:56
 *  Author: anreinha
 */ 

#include "sync.h"

void semaphore_init(semaphore* sema, uint16_t cntInit){
	sema->semaCnt = cntInit;
	linkedList_init(&sema->waitingTasks);
	linkedList_init(&sema->freedBy);
}

void semaphore_request(semaphore* sema){
	if(sema->freedBy.list){
		enterCriticalSection();
		while(sema->semaCnt <= 0){
			queueWaitingTask(&sema->waitingTasks, currentTask);
			scheduler_blockedByRessourceRequest(&sema->freedBy);
			leaveCriticalSection();
			task_yield();
			enterCriticalSection();
		}
		sema->semaCnt --;
		leaveCriticalSection();
	}
}
void semaphore_release(semaphore* sema){
	if(sema->freedBy.list){
		enterCriticalSection();
		sema->semaCnt ++;
		wakeupLinkedTasks(&sema->waitingTasks);
		scheduler_ressourceReleased(&sema->freedBy);
		leaveCriticalSection();
	}
}

void signal_init(signal* sig){
	linkedList_init(&sig->waitingTasks);
	linkedList_init(&sig->freedBy);
}

void signal_wait(signal* sig){
	enterCriticalSection();
	queueWaitingTask(&sig->waitingTasks, currentTask);
	scheduler_blockedByRessourceRequest(&sig->freedBy);
	leaveCriticalSection();
	task_yield();
}

void signal_send(signal* sig){
	enterCriticalSection();
	wakeupLinkedTasks(&sig->waitingTasks);
	scheduler_ressourceReleased(&sig->freedBy);
	leaveCriticalSection();
}

void task_yield(){
	disableInterrupts();
	hardwareISR = 0;
	DISPISRVEC();
}