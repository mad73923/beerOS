/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 


#include "beerOS.h"

uint8_t task1Stack[128];
uint8_t task2Stack[128];


int run(void)
{	
	initTask(1, task1Stack, dummyTask, 128);

	initIdleTask();
	initHardware();
	
	taskControlBlock* startTask;
	linkedList_get(&allTasksList, 0, &startTask);
	beerOS_start(startTask, &scheduler_initSimpleRR);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}
