/*
 * testTasks.h
 *
 * Created: 09.12.2015 18:56:45
 *  Author: anreinha
 */ 


#ifndef TESTTASKS_H_
#define TESTTASKS_H_

#include "../beerOSTypes.h"
#include "../exceptions.h"

void semaphoreTestTask();
void signalTestTask();
void sleepTestTask();
void linkedListTestTask();

extern uint8_t task;

#endif /* TESTTASKS_H_ */