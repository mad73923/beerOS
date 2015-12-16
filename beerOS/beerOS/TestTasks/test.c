/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 

#include "test.h"

uint8_t task1Stack[128];
uint8_t task2Stack[128];

//#define SemaTest
#define SignalTest
void startBeerOS(taskControlBlock* firstTask);

int run(void)
{	
	
#ifdef SemaTest
	initTask(1, task1Stack, semaphoreTestTask, 128);
	initTask(1, task2Stack, semaphoreTestTask, 128);
#endif // SemaTest
#ifdef SignalTest
	initTask(1, task1Stack, signalTestTask, 128);
	initTask(1, task2Stack, signalTestTask, 128);
#endif // SignalTest

	initIdleTask();
	initHardware();
	
	startBeerOS(&tcb[0]);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

void startBeerOS(taskControlBlock* firstTask){
	//set stack pointer of starting task next to taskaddress
	SP = firstTask->stackBeginn+firstTask->stackSize-progcntOffset;
	firstTask->state = RUNNING;
	//start task
	asm volatile ("ret");
}