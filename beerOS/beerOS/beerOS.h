/*
 * beerOS.h
 *
 * Created: 04.11.2015 13:39:07
 *  Author: matweis
 */ 


#ifndef BEEROS_H_
#define BEEROS_H_

#include "beerOSTypes.h"
#include "dummyTask.h"
#include "scheduler.h"

void startBeerOS(taskControlBlock* firstTask);

#endif /* BEEROS_H_ */