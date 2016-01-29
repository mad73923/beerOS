/*
 * time.h
 *
 * Created: 09.12.2015 19:52:48
 *  Author: matweis
 */ 


#ifndef TIME_H_
#define TIME_H_

#include "beerOSTypes.h"
#include "sync.h"

void time_init();
void sleep_ms(uint32_t ms);
void wakeupPendingTasks();
uint32_t getTime();

#endif /* TIME_H_ */