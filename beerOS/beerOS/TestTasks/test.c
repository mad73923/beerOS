/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 

#include "test.h"

uint8_t task1Stack[stacksize];
uint8_t task2Stack[stacksize];
uint8_t task3Stack[stacksize];

void (*initNextTest)(void) __attribute__ ((section (".noinit"))) = &initSemaphoreTest;

//#define SemaTest
//#define SignalTest
//#define sleepTest
//#define LinkedListTest
//#define QueueTest
//#define PrioTest
//#define RebootTest

int run(void)
{	
	initNextTest();
/*
#ifdef RebootTest
	initTask(1, task1Stack, rebootTestTask, stacksize);
#endif
*/
	initIdleTask();
	initHardware();
	
	taskControlBlock* startTask;
	linkedList_get(&allTasksList, 0, &startTask);
	startBeerOS(startTask, &scheduler_initPrioRR);
	
    while(1)
    {
		kernelPanic();
        //TODO:: Please write your application code 
    }
}