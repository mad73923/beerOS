#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include "beerOSTypes.h"
#include "linkedList.h"
#include "queue.h"
#include "scheduler/allScheduler.h"
#include "hardware.h"

extern const uint8_t progcntOffset;

extern volatile LinkedList allTasksList;
extern volatile uint8_t taskStructsAreInit;

extern uint8_t mainCalled;

void (*scheduler_NextTask)(void);
void (*scheduler_enqueueTask)(taskControlBlock* task);
void initIdleTask();
void idleTask();
void beerOS_start(taskControlBlock* firstTask, void (*scheduler_init)(void));
void beerOS_reboot();

#endif /* SCHEDULER_H_ */