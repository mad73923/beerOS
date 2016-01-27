#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include "beerOSTypes.h"
#include "linkedList.h"

extern const uint8_t progcntOffset;

extern volatile LinkedList allTasksList;

void scheduleNextTask();
void initIdleTask();
void idleTask();
void startBeerOS(taskControlBlock* firstTask);

#endif /* SCHEDULER_H_ */