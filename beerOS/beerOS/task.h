/*
 * task.h
 *
 * Created: 11.11.2015 14:05:48
 *  Author: matweis
 */ 


#ifndef TASK_H_
#define TASK_H_

#include "hardware.h"

typedef volatile struct taskControlBlock{
	volatile uint8_t prio;
	volatile uint8_t* stack;
	volatile uint8_t* stackBeginn;
	volatile uint32_t stackSize;
}taskControlBlock;

void initTask(taskControlBlock* cb, uint8_t prio, uint8_t* stack, void* taskFunction, uint32_t stackSize);

#endif /* TASK_H_ */