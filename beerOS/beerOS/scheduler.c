#include "scheduler.h"

#define idleTaskStackSize 256
uint8_t idleTaskStack[idleTaskStackSize];
taskControlBlock tcb[maxNumberOfTasks];
taskControlBlock* currentTask;

void schedSimpleRoundRobbin();
void schedPrioRoundRobbin();

void scheduleNextTask(){
	//schedSimpleRoundRobbin();
	schedPrioRoundRobbin();
}

void schedSimpleRoundRobbin(){
	uint8_t task;
	uint8_t numberOfTasks = linkedList_length(&allTasksList);
	do{
		task = (currentTask->id + 1)% numberOfTasks;
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
	Queue* nextPrioQueue;	
	for(uint16_t i = 0; i <= maxPrio; i++){
		linkedList_get(&prioQueueList, i, &nextPrioQueue);
		if(!queue_isEmpty(nextPrioQueue)){
			queue_pop(nextPrioQueue, &currentTask);
			break;
		}
	}
}

void initIdleTask(){
	initTask(maxPrio, idleTaskStack, idleTask, idleTaskStackSize);	
}

void idleTask(){
	while(1){
		yieldTask();
	}
}

void startBeerOS(taskControlBlock* firstTask){
	Queue* targetPrioQueue;
	taskControlBlock* newTask;
	for(uint32_t i = 0; i < linkedList_length(&allTasksList); i++){
		linkedList_get(&allTasksList, i, &newTask);
		if(newTask != firstTask){
			linkedList_get(&prioQueueList, newTask->prio, &targetPrioQueue);
			queue_push(targetPrioQueue, newTask);
		}
	}
	
	//set stack pointer of starting task next to taskaddress
	SP = firstTask->stackBeginn+firstTask->stackSize-progcntOffset;
	firstTask->state = RUNNING;
	currentTask = firstTask;
	//start task
	asm volatile ("ret");
}