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

extern uint8_t task;
extern taskControlBlock tcb[4];

void sleep_ms(uint32_t ms);

#endif /* TIME_H_ */