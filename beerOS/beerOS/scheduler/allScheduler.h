/*
 * allScheduler.h
 *
 * Created: 29.01.2016 14:15:04
 *  Author: matweis
 */ 


#ifndef ALLSCHEDULER_H_
#define ALLSCHEDULER_H_

#include "../beerOSTypes.h"
#include "../scheduler.h"

extern taskControlBlock* currentTask;


void scheduler_initSimpleRR();


#endif /* ALLSCHEDULER_H_ */