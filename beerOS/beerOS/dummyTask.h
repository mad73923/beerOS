/*
 * dummyTask.h
 *
 * Created: 11.11.2015 14:30:28
 *  Author: matweis
 */ 


#ifndef DUMMYTASK_H_
#define DUMMYTASK_H_

#include "sync.h"

void dummyTask();

extern uint8_t task;
extern taskControlBlock tcb[4];

#endif /* DUMMYTASK_H_ */