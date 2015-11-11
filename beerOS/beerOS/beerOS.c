/*
 * beerOS.c
 *
 * Created: 04.11.2015 13:29:16
 *  Author: matweis
 */ 

#include "beerOS.h"

taskControlBlock task1;
uint8_t task1Stack[512];

taskControlBlock task2;
uint8_t task2Stack[512];

int main(void)
{
	
	initHardware();
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}