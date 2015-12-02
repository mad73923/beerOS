/*
 * hardware.h
 *
 * Created: 04.11.2015 13:38:38
 *  Author: matweis
 */ 


#ifndef HARDWARE_H_
#define HARDWARE_H_

#define NULL 0

#ifdef __AVR_ATxmega128A1__

#include <avr/io.h>
#include <avr/interrupt.h>

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