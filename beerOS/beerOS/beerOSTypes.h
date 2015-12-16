/*
 * beerOSTypes.h
 *
 * Created: 03.12.2015 16:45:01
 *  Author: matweis
 */ 


#ifndef BEEROSTYPES_H_
#define BEEROSTYPES_H_

#ifdef __AVR_ATxmega128A1__

#include <avr/io.h>
#include <avr/interrupt.h>

#endif //__AVR_ATxmega128A1__

#define NULL 0

// TASK
typedef enum {READY, RUNNING, WAITING, KILLED} taskstate;

typedef volatile struct strucTCB{
	volatile struct strucTCB* semaNextWaiting;
	volatile uint8_t prio;
	volatile uint8_t* stackPointer;
	volatile uint8_t* stackBeginn;
	volatile uint16_t stackSize;
	volatile uint32_t waitUntil;
	volatile taskstate state;
}taskControlBlock;

//SYNC
typedef volatile struct{
	volatile struct taskControlBlock* firstWaiting;
	volatile int16_t semaCnt;
}semaphore;

typedef volatile struct{
	volatile struct taskControlBlock* firstWaiting;
}signal;

typedef volatile struct{
	volatile struct taskControlBlock* firstWaiting;
}likedSyncObject;



#endif /* BEEROSTYPES_H_ */