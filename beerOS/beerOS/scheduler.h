#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include "beerOSTypes.h"
#include "linkedList.h"
#include "queue.h"

extern const uint8_t progcntOffset;

extern volatile LinkedList allTasksList;
extern volatile LinkedList prioQueueList;
extern volatile Queue prioQueue[maxPrio+1];

void scheduleNextTask();
void initIdleTask();
void idleTask();
void startBeerOS(taskControlBlock* firstTask);

#endif /* SCHEDULER_H_ */