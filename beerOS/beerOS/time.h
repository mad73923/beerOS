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
void time_sleep_ms(uint32_t ms);
void time_wakeupPendingTasks();
uint32_t time_getSystemTime();

#endif /* TIME_H_ */