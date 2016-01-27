#include "scheduler.h"

uint8_t task = 0;
uint8_t idleTaskStack[128];
taskControlBlock tcb[maxNumberOfTasks];
taskControlBlock* currentTask;

void schedSimpleRoundRobbin();

void scheduleNextTask(){
	schedSimpleRoundRobbin();
}

void schedSimpleRoundRobbin(){
	do{
		task = (task + 1) % linkedList_length(&allTasksList);
		linkedList_get(&allTasksList, task, &currentTask);
	}while (currentTask->state == WAITING);
}

void initIdleTask(){
	initTask(1, idleTaskStack, idleTask, 128);	
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