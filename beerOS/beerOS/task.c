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

void initTask(taskControlBlock* cb, uint8_t prio, uint8_t* stack, void* taskFunction){
	pew ptr;
	ptr.u24 = (uint32_t) taskFunction;
	cb->prio = prio;
	cb->stack = stack + 26;
	stack[63] = ptr.u8[0]; 
	stack[62] = ptr.u8[1];
	stack[61] = ptr.u8[2];
	// place taskFunction on stack
	
}