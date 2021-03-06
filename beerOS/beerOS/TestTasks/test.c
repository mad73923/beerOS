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
void (*scheduler_init)(void) = &scheduler_initPrioRR;

// Automated test order
// 1. SemaTest
// 2. SignalTest
// 3. sleepTest
// 4. LinkedListTest
// 5. QueueTest
// 6. PrioTest
// 7. PIPTest
// 8. MemoryManagementTest

// Simulated time: 26.233,94 us

//#define RebootTest

int run(void)
{	
//	initNextTest = &initLinkedListTest;	
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
	beerOS_start(startTask, scheduler_init);

    while(1)
    {
		kernelPanic();
    }
}