#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include "beerOSTypes.h"

extern uint8_t numberOfTasks;
extern const uint8_t progcntOffset;


void scheduleNextTask();
void initIdleTask();
void idleTask();
void startBeerOS(taskControlBlock* firstTask);

#endif /* SCHEDULER_H_ */