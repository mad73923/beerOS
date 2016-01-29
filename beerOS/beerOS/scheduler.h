#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include "beerOSTypes.h"
#include "linkedList.h"
#include "queue.h"
#include "scheduler/allScheduler.h"

extern const uint8_t progcntOffset;

extern volatile LinkedList allTasksList;
extern volatile LinkedList prioQueueList;
extern volatile Queue prioQueue[maxPrio+1];

void (*scheduler_NextTask)(void);
void (*scheduler_enqueueTask)(taskControlBlock* task);
void initIdleTask();
void idleTask();
void startBeerOS(taskControlBlock* firstTask, void (*scheduler_init)(void));

#endif /* SCHEDULER_H_ */