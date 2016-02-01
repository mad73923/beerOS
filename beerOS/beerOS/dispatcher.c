/*
 * dispatcher.c
 *
 * Created: 04.11.2015 14:53:06
 *  Author: matweis
 */ 

#include "dispatcher.h"

volatile uint8_t hardwareISR = 1;



ISR(DISPISRVEC, ISR_NAKED){
	
	// rescue registers	
	asm volatile(	"PUSH R0\n\t"
					"PUSH R1\n\t"
					"PUSH R2\n\t"
					"PUSH R3\n\t"
					"PUSH R4\n\t"
					"PUSH R5\n\t"
					"PUSH R6\n\t"
					"PUSH R7\n\t"
					"PUSH R8\n\t"
					"PUSH R9\n\t"
					"PUSH R10\n\t"
					"PUSH R11\n\t"
					"PUSH R12\n\t"
					"PUSH R13\n\t"
					"PUSH R14\n\t"
					"PUSH R15\n\t"
					"PUSH R16\n\t"
					"PUSH R17\n\t"
					"PUSH R18\n\t"
					"PUSH R19\n\t"
					"PUSH R20\n\t"
					"PUSH R21\n\t"
					"PUSH R22\n\t"
					"PUSH R23\n\t"
					"PUSH R24\n\t"
					"PUSH R25\n\t"
					"PUSH R26\n\t"
					"PUSH R27\n\t"
					"PUSH R28\n\t"
					"PUSH R29\n\t"
					"PUSH R30\n\t"
					"PUSH R31\n\t"
					"IN R0, __SREG__\n\t"
					"PUSH R0\n\t"
					"IN R0, 0x003C ;EIND\n\t"
					"PUSH R0\n\t"
					"CLR R1"
				);
	
	//rescue stack pointer
	currentTask->stackPointer = SP;
	// set task state
	// if state = waiting, dont change!	
	if(currentTask->state == RUNNING){
		currentTask->state = READY;
		scheduler_enqueueTask(currentTask);
	}
	
	if(hardwareISR == 1){
		systemTime_ms ++;
		wakeupPendingTasks();
	}
	hardwareISR = 1;
	
	if(currentTask->stackBeginn[0] != magicStackNumber){
		kernelPanic();
	}
	
	// call scheduler
	scheduler_NextTask();
	
	if(currentTask->stackBeginn[currentTask->stackSize-1] != magicStackNumber){
		kernelPanic();
	}
	
	// reassign stackpointer
	SP = currentTask->stackPointer;
	// set task state
	currentTask->state = RUNNING;
	
	asm volatile ("nop");
	
	// write registers of new thread
	asm volatile(	"POP R0\n\t"
					"OUT 0x003C, R0 ;EIND\n\t"
					"POP R0\n\t"
					"OUT __SREG__, R0\n\t"
					"POP R31\n\t"
					"POP R30\n\t"
					"POP R29\n\t"
					"POP R28\n\t"
					"POP R27\n\t"
					"POP R26\n\t"
					"POP R25\n\t"
					"POP R24\n\t"
					"POP R23\n\t"
					"POP R22\n\t"
					"POP R21\n\t"
					"POP R20\n\t"
					"POP R19\n\t"
					"POP R18\n\t"
					"POP R17\n\t"
					"POP R16\n\t"
					"POP R15\n\t"
					"POP R14\n\t"
					"POP R13\n\t"
					"POP R12\n\t"
					"POP R11\n\t"
					"POP R10\n\t"
					"POP R9\n\t"
					"POP R8\n\t"
					"POP R7\n\t"
					"POP R6\n\t"
					"POP R5\n\t"
					"POP R4\n\t"
					"POP R3\n\t"
					"POP R2\n\t"
					"POP R1\n\t"
					"POP R0\n\t"					
				);
	
	enableInterrupts();
	asm volatile ("nop");
	asm volatile ("reti");
}