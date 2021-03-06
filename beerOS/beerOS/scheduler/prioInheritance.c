/*
 * prioInheritance.c
 *
 * Created: 04.02.2016 00:42:04
 *  Author: matweis
 */ 
#include "../beerOSTypes.h"
#include "allScheduler.h"

volatile Queue prioQueue[maxPrio+1];

void prioInheritance_nextTask(){
	Queue* nextPrioQueue;	
	for(uint16_t i = 0; i <= maxPrio; i++){
		nextPrioQueue = &prioQueue[i];
		if(!queue_isEmpty(nextPrioQueue)){
			queue_pop(nextPrioQueue, &currentTask);
			break;
		}
	}
}

void prioInheritance_enqueueTask(taskControlBlock* task){
	Queue* targetPrioQueue;
	if(task->prio > maxPrio){
		kernelPanic();
	}
	targetPrioQueue = &prioQueue[task->prio];
	queue_push(targetPrioQueue, task);
}

void prioInheritance_blockedByRessourceRequest(LinkedList* resFreedBy){
	uint8_t length = linkedList_length(resFreedBy);
	taskControlBlock* nextTask;
	if(length){
		for(uint16_t i = 0; i < length; i++){
			linkedList_get(resFreedBy, i, &nextTask);
			if(nextTask->state == READY && nextTask->prio > currentTask->prio){
				nextTask->prio = currentTask->prio;
				queue_removeItem(&prioQueue[nextTask->tmpPrio], nextTask);
				queue_push(&prioQueue[nextTask->prio], nextTask);
				break;
			}
		}
	}
}

void prioInheritance_ressourceReleased(LinkedList* resFreedBy){
	if(!linkedList_contains(resFreedBy, currentTask)){
		linkedList_append(resFreedBy, currentTask);
	}
	if(currentTask->tmpPrio != currentTask->prio){
		currentTask->prio = currentTask->tmpPrio;
		task_yield();
	}
}

void scheduler_initPrioInheritance(){
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
	
	scheduler_NextTask = &prioInheritance_nextTask;
	scheduler_enqueueTask = &prioInheritance_enqueueTask;
	scheduler_blockedByRessourceRequest = &prioInheritance_blockedByRessourceRequest;
	scheduler_ressourceReleased = &prioInheritance_ressourceReleased;
}