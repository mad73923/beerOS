/*
 * dispatcher.h
 *
 * Created: 04.11.2015 14:53:50
 *  Author: matweis
 */ 


#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "beerOSTypes.h"
#include "scheduler.h"
#include "hardware.h"
#include "task.h"
#include "time.h"

extern volatile uint32_t systemTime_ms;
extern volatile linkedSyncObject allSleepingTasks;
extern taskControlBlock* currentTask;
extern const uint8_t magicStackNumber;


#endif /* DISPATCHER_H_ */