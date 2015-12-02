#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include "beerOS.h"

extern uint8_t numberOfTasks;

void scheduleNextTask();

void idleTask();

#endif /* SCHEDULER_H_ */