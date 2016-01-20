/*
 * task.h
 *
 * Created: 11.11.2015 14:05:48
 *  Author: matweis
 */ 


#ifndef TASK_H_
#define TASK_H_

#include "beerOSTypes.h"
#include "scheduler.h"

extern taskControlBlock tcb[4];

void initTask(uint8_t prio, uint8_t* stack, void* taskFunction, uint16_t stackSize);

void wakeupLinkedTasks(linkedSyncObject* syncObj);
void queueWaitingTask(linkedSyncObject* syncObj, taskControlBlock* newTask);

#endif /* TASK_H_ */