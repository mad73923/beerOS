/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 

#include "beerOS.h"

uint8_t task1Stack[64];
uint8_t task2Stack[64];
taskControlBlock tcb[4];

int main(void)
{
	
	
	initTask(&tcb[0], 1, task1Stack, dummyTask, 64);
	initTask(&tcb[1], 2, task2Stack, dummyTask, 64);
	initHardware();
	SP = &tcb[0].stackBeginn[tcb[0].stackSize-4];

	asm volatile ("ret");
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}