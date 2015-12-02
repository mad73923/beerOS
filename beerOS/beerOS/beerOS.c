/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 

#include "beerOS.h"

uint8_t task1Stack[128];
uint8_t task2Stack[128];

int main(void)
{
	
	
	initTask(1, task1Stack, dummyTaskSemaTest, 128);
	initTask(2, task2Stack, dummyTaskSemaTest, 128);
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