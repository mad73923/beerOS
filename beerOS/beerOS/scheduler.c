#include "scheduler.h"

uint8_t idleTaskStack[128];
taskControlBlock tcb[maxNumberOfTasks];
taskControlBlock* currentTask;

void schedSimpleRoundRobbin();
void schedPrioRoundRobbin();

void scheduleNextTask(){
	schedSimpleRoundRobbin();
}

void schedSimpleRoundRobbin(){
	uint8_t task;
	do{
		task = (currentTask->id + 1)% linkedList_length(&allTasksList);
		linkedList_get(&allTasksList, task, &currentTask);
	}while (currentTask->state == WAITING);
}

void schedPrioRoundRobbin(){
	if(currentTask->state == READY){
		if(currentTask->prio > maxPrio){
			kernelPanic();
		}
		Queue* targetPrioQueue;
		linkedList_get(&prioQueueList, currentTask->prio, &targetPrioQueue);
		queue_push(targetPrioQueue, currentTask);
	}
	for(uint16_t i = 0; i <= maxPrio; i++){
		Queue* nextPrioQueue;
		linkedList_get(&prioQueueList, i, &nextPrioQueue);
		if(!queue_isEmpty(nextPrioQueue)){
			queue_pop(nextPrioQueue, &currentTask);
			break;
		}
	}
}

void initIdleTask(){
	initTask(maxPrio, idleTaskStack, idleTask, 128);	
}

void idleTask(){
	while(1){
		yieldTask();
	}
}

void startBeerOS(taskControlBlock* firstTask){
	//set stack pointer of starting task next to taskaddress
	SP = firstTask->stackBeginn+firstTask->stackSize-progcntOffset;
	firstTask->state = RUNNING;
	currentTask = firstTask;
	//start task
	asm volatile ("ret");
}