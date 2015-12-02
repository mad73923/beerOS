#include "scheduler.h"


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