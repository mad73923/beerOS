/*
 * hardware.h
 *
 * Created: 04.11.2015 13:38:38
 *  Author: matweis
 */ 


#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "beerOSTypes.h"


#ifdef __AVR_ATxmega128A1__

#define DISPISRVEC TCF0_OVF_vect

static void __attribute__((always_inline)) enableInterrupts(){
	sei();
}

static void __attribute__((always_inline)) disableInterrupts(){
	cli();
}

#endif // __AVR_ATxmega128A1__

void initHardware();



#endif /* HARDWARE_H_ */