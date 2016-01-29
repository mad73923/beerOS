#include "scheduler.h"

#define idleTaskStackSize 256
uint8_t idleTaskStack[idleTaskStackSize];
taskControlBlock tcb[maxNumberOfTasks];
taskControlBlock* currentTask;

void initIdleTask(){
	initTask(maxPrio, idleTaskStack, idleTask, idleTaskStackSize);	
}

void idleTask(){
	while(1){
		yieldTask();
	}
}

void startBeerOS(taskControlBlock* firstTask){
	currentTask = firstTask;
	
	//TODO make this a parameter
	scheduler_initPrioRR();
	
	//set stack pointer of starting task next to taskaddress
	SP = currentTask->stackBeginn+currentTask->stackSize-progcntOffset;
	currentTask->state = RUNNING;
	//start task
	asm volatile ("ret");
}