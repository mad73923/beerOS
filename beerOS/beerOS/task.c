/*
 * task.c
 *
 * Created: 11.11.2015 14:04:58
 *  Author: matweis
 */ 

#include "task.h"

typedef union {
	uint32_t u24;
	uint8_t u8[4];
} pew;

void initTask(taskControlBlock* cb, uint8_t prio, uint8_t* stack, void* taskFunction, uint32_t stackSize){
	pew ptr;
	ptr.u24 = (uint32_t) taskFunction;
	cb->prio = prio;
	cb->stackSize = stackSize;
	cb->stackBeginn = stack;
	cb->stack = stack + (stackSize-32-2-3-1); // stacksize-32 reg - sreg - eind - 3x progcnt - index 0
	// place taskFunction on stack	
	stack[stackSize-1] = ptr.u8[0]; 
	stack[stackSize-2] = ptr.u8[1];
	stack[stackSize-3] = ptr.u8[2];
	
	cb->state = READY;
}