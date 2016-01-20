#include "scheduler.h"

uint8_t task = 0;
uint8_t idleTaskStack[128];
taskControlBlock tcb[4];

void schedSimpleRoundRobbin();

void scheduleNextTask(){
	schedSimpleRoundRobbin();
}

void schedSimpleRoundRobbin(){
	do{
		task = (task + 1) % numberOfTasks;
	}while (tcb[task].state == WAITING);
}

void initIdleTask(){
	initTask(1, idleTaskStack, idleTask, 128);	
}

void idleTask(){
	while(1){
		yieldTask();
	}
}