/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 

#include "beerOS.h"

uint8_t task1Stack[128];
uint8_t task2Stack[128];
taskControlBlock tcb[4];

int main(void)
{
	
	
	initTask(&tcb[0], 1, task1Stack, dummyTask, 128);
	initTask(&tcb[1], 2, task2Stack, dummyTask, 128);
	initHardware();
	
	startBeerOS(&tcb[0]);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

void startBeerOS(taskControlBlock* firstTask){
	//set stack pointer of starting task next to taskaddress
	SP = firstTask->stackBeginn+firstTask->stackSize-4;
	firstTask->state = RUNNING;
	//start task
	asm volatile ("ret");
}