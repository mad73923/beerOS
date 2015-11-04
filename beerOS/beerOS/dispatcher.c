/*
 * dispatcher.c
 *
 * Created: 04.11.2015 14:53:06
 *  Author: matweis
 */ 

#include "dispatcher.h"

ISR(DISPISRVEC, ISR_NAKED){
	// rescue registers
	// Alle Register
	// SREG (Statuswort)
	// Stack
	// Modus (Running, Waiting, Killed ....)
	// Prioritaet (je nach Scheduling Verfahren)
	
	// call scheduler
	
	// reassign stackpointer
	 
	// write registers of new thread
	asm volatile ("nop");
	asm volatile ("reti");
}