/*
 * prioRR.c
 *
 * Created: 29.01.2016 14:36:38
 *  Author: matweis
 */ 
#include "../beerOSTypes.h"
#include "allScheduler.h"

volatile LinkedList prioQueueList;
volatile Queue prioQueue[maxPrio+1];

void prioRR_nextTask(){
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

void prioRR_enqueueTask(taskControlBlock* task){
	Queue* targetPrioQueue;
	if(task->prio > maxPrio){
		kernelPanic();
	}
	linkedList_get(&prioQueueList, task->prio, &targetPrioQueue);
	queue_push(targetPrioQueue, task);
}

void scheduler_initPrioRR(){
	linkedList_init(&prioQueueList);
	for (uint16_t i = 0; i <= maxPrio; i++){
		queue_init(&prioQueue[i]);
		linkedList_append(&prioQueueList, &prioQueue[i]);
	}
	Queue* targetPrioQueue;
	taskControlBlock* newTask;
	for(uint32_t i = 0; i < linkedList_length(&allTasksList); i++){
		linkedList_get(&allTasksList, i, &newTask);
		if(newTask != currentTask){
			linkedList_get(&prioQueueList, newTask->prio, &targetPrioQueue);
			queue_push(targetPrioQueue, newTask);
		}
	}
	
	scheduler_NextTask = &prioRR_nextTask;
	scheduler_enqueueTask = &prioRR_enqueueTask;
}