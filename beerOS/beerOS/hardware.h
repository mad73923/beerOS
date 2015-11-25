/*
 * hardware.h
 *
 * Created: 04.11.2015 13:38:38
 *  Author: matweis
 */ 


#ifndef HARDWARE_H_
#define HARDWARE_H_

#ifdef __AVR_ATxmega128A1__

#include <avr/io.h>
#include <avr/interrupt.h>

#define DISPISRVEC TCF0_OVF_vect
#define NULL 0

#endif // __AVR_ATxmega128A1__

void initHardware();
void enableInterrupts();
void disableInterrupts();

#endif /* HARDWARE_H_ */