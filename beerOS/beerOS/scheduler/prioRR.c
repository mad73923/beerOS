/*
 * prioRR.c
 *
 * Created: 29.01.2016 14:36:38
 *  Author: matweis
 */ 
#include "../beerOSTypes.h"
#include "allScheduler.h"

volatile Queue prioQueue[maxPrio+1];

void prioRR_nextTask(){
	Queue* nextPrioQueue;
	for(uint16_t i = 0; i <= maxPrio; i++){
		nextPrioQueue = &prioQueue[i];
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
	targetPrioQueue = &prioQueue[task->prio];
	queue_push(targetPrioQueue, task);
}

void prioRR_blockedByRessourceRequest(LinkedList* resFreedBy){

}

void prioRR_ressourceReleased(LinkedList* resFreedBy){

}

void scheduler_initPrioRR(){
	for (uint16_t i = 0; i <= maxPrio; i++){
		queue_init(&prioQueue[i]);
	}
	Queue* targetPrioQueue;
	taskControlBlock* newTask;
	for(uint32_t i = 0; i < linkedList_length(&allTasksList); i++){
		linkedList_get(&allTasksList, i, &newTask);
		if(newTask != currentTask){
			targetPrioQueue = &prioQueue[newTask->prio];
			queue_push(targetPrioQueue, newTask);
		}
	}
	
	scheduler_NextTask = &prioRR_nextTask;
	scheduler_enqueueTask = &prioRR_enqueueTask;
	scheduler_ressourceReleased = &prioRR_ressourceReleased;
	scheduler_blockedByRessourceRequest = &prioRR_blockedByRessourceRequest;
}