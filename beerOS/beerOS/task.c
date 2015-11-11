/*
 * task.c
 *
 * Created: 11.11.2015 14:04:58
 *  Author: matweis
 */ 

#include "task.h"

void initTask(taskControlBlock* cb, uint8_t prio, uint8_t* stack, void* taskFunction){
	cb->stackP = stack;
	cb->prio = prio;
}