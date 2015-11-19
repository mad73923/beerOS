#include "task.h"

uint8_t numberOfTasks = 0;
// 32 reg - sreg - eind - 3x progcnt - index 0
const uint8_t numberOfRegister = 32-2-3-1; 

typedef union {
	uint32_t u24;
	uint8_t u8[4];
} ByteAccesUnion;

void initTaskControlBlock(uint8_t prio, uint8_t* stack, uint32_t stackSize);
void placeStartAdressOnStack(uint8_t* stack, void* taskFunction);

void initTask(uint8_t prio, uint8_t* stack, void* taskFunction, uint32_t stackSize){
	initTaskControlBlock(prio, stack, stacksize);
	placeStartAdressOnStack(stack, taskFunction);	
}

void initTaskControlBlock(uint8_t prio, uint8_t* stack, uint32_t stackSize){
	taskControlBlock cb = tcb[numberOfTasks];
	numberOfTasks++;
	
	cb->prio = prio;
	cb->stackSize = stackSize;
	cb->stackBeginn = stack;
	cb->stack = stack + (stackSize - numberOfRegister); 
}

void placeStartAdressOnStack(uint8_t* stack, void* taskFunction){
	ByteAccessUnion byteAccessUnion;
	byteAccessUnion.u24 = (uint32_t) taskFunction;
	
	stack[stackSize-1] = byteAccessUnion.u8[0]; 
	stack[stackSize-2] = byteAccessUnion.u8[1];
	stack[stackSize-3] = byteAccessUnion.u8[2];
}