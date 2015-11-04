/*
 * hardware.c
 *
 * Created: 04.11.2015 13:42:13
 *  Author: matweis
 */ 

#include "hardware.h"

#ifdef __AVR_ATxmega128A1__

void setSystemClock32MHZ();
void initDispatcherTimer();
void startDispatcherTimer();
void stopDispatcherTimer();

void initHardware(){
	
	setSystemClock32MHZ();
	initDispatcherTimer();
	startDispatcherTimer();
	enableInterrupts();
}

void setSystemClock32MHZ(){
	OSC.CTRL |= OSC_RC32MEN_bm;
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));
	CCP = CCP_IOREG_gc;
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc;
}

void initDispatcherTimer(){
	TCF0.CTRLB = TC_WGMODE_NORMAL_gc;
	// adapt period here
	TCF0.PER = 0xFF;
	TCF0.INTCTRLA = TC_OVFINTLVL_HI_gc;
}

void startDispatcherTimer(){
	// needs adaptions
	//TCF0.CTRLA = TC_CLKSEL_DIV8_gc;
	TCF0.CTRLA = TC_CLKSEL_DIV1_gc;
	
}

void stopDispatcherTimer(){
	TCF0.CTRLA = TC_CLKSEL_OFF_gc;
}

void enableInterrupts(){
	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	sei();
}

void disableInterrupts(){
	cli();
}

#endif // __AVR_ATxmega128A1__