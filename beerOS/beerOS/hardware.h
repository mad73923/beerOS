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

static inline void enableInterrupts(){
	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	sei();
}

static inline void disableInterrupts(){
	cli();
}

#endif // __AVR_ATxmega128A1__

void initHardware();



#endif /* HARDWARE_H_ */