/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 

#include "test.h"

uint8_t task1Stack[128];
uint8_t task2Stack[128];
uint8_t task3Stack[128];

//#define SemaTest
//#define SignalTest
//#define sleepTest
//#define LinkedListTest
//#define QueueTest

int run(void)
{	
	
#ifdef SemaTest
	initTask(1, task1Stack, semaphoreTestTask, 128);
	initTask(1, task2Stack, semaphoreTestTask, 128);
	initTask(1, task3Stack, semaphoreTestTask, 128);
#endif // SemaTest

#ifdef SignalTest
	initTask(1, task1Stack, signalTestTask, 128);
	initTask(1, task2Stack, signalTestTask, 128);
	initTask(1, task3Stack, signalTestTask, 128);
#endif // SignalTest

#ifdef sleepTest
	initTask(1, task1Stack, sleepTestTask, 128);
	initTask(1, task2Stack, sleepTestTask, 128);
	initTask(1, task3Stack, sleepTestTask, 128);
#endif //sleepTest

#ifdef LinkedListTest
	initTask(1, task1Stack, linkedListTestTask, 128);
#endif // LinkedListTest

#ifdef QueueTest
	initTask(1, task1Stack, queueTestTask, 128);
#endif // QueueTest

	initIdleTask();
	initHardware();
	
	taskControlBlock* startTask;
	linkedList_get(&allTasksList, 0, &startTask);
	startBeerOS(startTask);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}