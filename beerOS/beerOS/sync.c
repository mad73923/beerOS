/*
 * sync.c
 *
 * Created: 19.11.2015 17:48:56
 *  Author: anreinha
 */ 

#include "sync.h"

void enterCriticalSection(){
	disableInterrupts();
}

void leaveCriticalSection(){
	enableInterrupts();
}


void leaveCriticalSection();