#include "scheduler.h"

uint8_t task = 0;
taskControlBlock tcb[4];

void scheduleNextTask(){
	do{
		task = (task + 1) % numberOfTasks;
	}while (tcb[task].state == WAITING);
}

void idleTask(){
	while(1){
		yieldTask();
	}
}