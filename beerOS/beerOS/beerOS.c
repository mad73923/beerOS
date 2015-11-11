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
	
	
	initTask(&tcb[0], 1, task1Stack, dummyTask);
	initTask(&tcb[1], 2, task2Stack, dummyTask);
	initHardware();	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}