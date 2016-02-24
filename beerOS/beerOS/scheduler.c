#include "scheduler.h"

#define idleTaskStackSize 512
uint8_t idleTaskStack[idleTaskStackSize];
taskControlBlock tcb[maxNumberOfTasks];
taskControlBlock* currentTask;

void (*scheduler_NextTask)(void);
void (*scheduler_enqueueTask)(taskControlBlock* task);
void (*scheduler_blockedByRessourceRequest)(LinkedList* ressource);
void (*scheduler_ressourceReleased)(LinkedList* ressource);

static uint8_t* mainSP;


void initIdleTask(){
	initTask(maxPrio, idleTaskStack, idleTask, idleTaskStackSize);	
}

void idleTask(){
	while(1){
		task_yield();
	}
}

void beerOS_start(taskControlBlock* firstTask, void (*scheduler_init)(void)){
	currentTask = firstTask;
	
	scheduler_init();
	time_init();
	
	firstTask->state = RUNNING;
	mainSP = SP;
	//set stack pointer of starting task next to taskaddress
	SP = firstTask->stackBeginn+firstTask->stackSize-progcntOffset;
	//start task	
	asm volatile ("ret");
}

void beerOS_reboot(){
	disableInterrupts();
	stopDispatcherTimer();
	//clear main stack
	while(mainSP <= RAMEND){
		*mainSP = 0;
		mainSP++;
	}
	mainCalled--;
	SP = 0;
	asm volatile(	"CLR R0\n\t"
					"CLR R1\n\t"
					"CLR R2\n\t"
					"CLR R3\n\t"
					"CLR R4\n\t"
					"CLR R5\n\t"
					"CLR R6\n\t"
					"CLR R7\n\t"
					"CLR R8\n\t"
					"CLR R9\n\t"
					"CLR R10\n\t"
					"CLR R11\n\t"
					"CLR R12\n\t"
					"CLR R13\n\t"
					"CLR R14\n\t"
					"CLR R15\n\t"
					"CLR R16\n\t"
					"CLR R17\n\t"
					"CLR R18\n\t"
					"CLR R19\n\t"
					"CLR R20\n\t"
					"CLR R21\n\t"
					"CLR R22\n\t"
					"CLR R23\n\t"
					"CLR R24\n\t"
					"CLR R25\n\t"
					"CLR R26\n\t"
					"CLR R27\n\t"
					"CLR R28\n\t"
					"CLR R29\n\t"
					"CLR R30\n\t"
					"CLR R31\n\t"
					"BCLR 0\n\t"
					"BCLR 1\n\t"
					"BCLR 2\n\t"
					"BCLR 3\n\t"
					"BCLR 4\n\t"
					"BCLR 5\n\t"
					"BCLR 6\n\t"
					"BCLR 7\n\t"
				);
	asm volatile ("jmp 0");
}