/*
 * task.h
 *
 * Created: 11.11.2015 14:05:48
 *  Author: matweis
 */ 


#ifndef TASK_H_
#define TASK_H_

#include "hardware.h"

typedef enum {READY, RUNNING, WAITING, KILLED} taskstate;

typedef volatile struct taskControlBlock{
	volatile uint8_t prio;
	volatile uint8_t* stack;
	volatile uint8_t* stackBeginn;
	volatile uint32_t stackSize;
	
	volatile taskstate state;
}taskControlBlock;

void initTask(uint8_t prio, uint8_t* stack, void* taskFunction, uint32_t stackSize);
uint8_t maxNumberOfTasks = 4;
taskControlBlock tcb[maxNumberOfTasks];

#endif /* TASK_H_ */