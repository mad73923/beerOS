/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 

#include "test.h"

#define stacksize 128

uint8_t task1Stack[stacksize];
uint8_t task2Stack[stacksize];
uint8_t task3Stack[stacksize];

//#define SemaTest
//#define SignalTest
//#define sleepTest
//#define LinkedListTest
//#define QueueTest
//#define PrioTest

int run(void)
{	
	
#ifdef SemaTest
	initTask(1, task1Stack, semaphoreTestTask, stacksize);
	initTask(1, task2Stack, semaphoreTestTask, stacksize);
	initTask(1, task3Stack, semaphoreTestTask, stacksize);
#endif // SemaTest

#ifdef SignalTest
	initTask(1, task1Stack, signalTestTask, stacksize);
	initTask(1, task2Stack, signalTestTask, stacksize);
	initTask(1, task3Stack, signalTestTask, stacksize);
#endif // SignalTest

#ifdef sleepTest
	initTask(0, task1Stack, sleepTestTask, stacksize);
	initTask(0, task2Stack, sleepTestTask, stacksize);
	initTask(0, task3Stack, sleepTestTask, stacksize);
#endif //sleepTest

#ifdef LinkedListTest
	initTask(1, task1Stack, linkedListTestTask, stacksize);
#endif // LinkedListTest

#ifdef QueueTest
	initTask(1, task1Stack, queueTestTask, stacksize);
#endif // QueueTest

#ifdef PrioTest
	initTask(0, task1Stack, prioTestTask, stacksize);
	initTask(1, task2Stack, prioTestTask, stacksize);
	initTask(2, task3Stack, prioTestTask, stacksize);
#endif // PrioTest

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