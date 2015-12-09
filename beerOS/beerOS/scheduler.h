#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include "beerOSTypes.h"

extern uint8_t numberOfTasks;
extern uint8_t task;
extern taskControlBlock tcb[4];

void scheduleNextTask();
void initIdleTask();
void idleTask();

#endif /* SCHEDULER_H_ */