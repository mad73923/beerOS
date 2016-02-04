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

#define stacksize 128

extern void (*initNextTest)(void);
extern uint8_t task1Stack[stacksize];
extern uint8_t task2Stack[stacksize];
extern uint8_t task3Stack[stacksize];

void initSemaphoreTest();
void semaphoreTestTask();
void initSignalTest();
void signalTestTask();
void initSleepTest();
void sleepTestTask();
void initLinkedListTest();
void linkedListTestTask();
void initQueueTest();
void queueTestTask();
void initPrioTest();
void prioTestTask();
void rebootTestTask();
void initPipTest();
void pipTestTask();

#endif /* TESTTASKS_H_ */