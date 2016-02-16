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

extern void (*scheduler_NextTask)(void);
extern void (*scheduler_enqueueTask)(taskControlBlock *task);
extern void (*scheduler_blockedByRessourceRequest)(LinkedList *ressource);
extern void (*scheduler_ressourceReleased)(LinkedList *ressource);

extern taskControlBlock* currentTask;

void scheduler_initSimpleRR();
void scheduler_initPrioRR();
void scheduler_initPrioInheritance();


#endif /* ALLSCHEDULER_H_ */