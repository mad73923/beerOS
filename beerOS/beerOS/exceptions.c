/*
 * exceptions.c
 *
 * Created: 04.12.2015 12:26:23
 *  Author: matweis
 */ 

#include "exceptions.h"

void kernelPanic(){
	disableInterrupts();
	while(1){
		asm volatile ("nop");		
	}
}

void beerOSAssertEqual(int cond1, int cond2){
	if(cond1 != cond2){
		kernelPanic();
	}
}