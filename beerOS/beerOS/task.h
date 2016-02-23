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
#include "linkedList.h"
#include "queue.h"
#include "sync.h"

extern taskControlBlock tcb[maxNumberOfTasks];

void initTask(uint8_t prio, uint8_t* stack, void* taskFunction, uint16_t stackSize);

void wakeupLinkedTasks(LinkedList* syncObj);
void queueWaitingTask(LinkedList* syncObj, taskControlBlock* newTask);

#endif /* TASK_H_ */