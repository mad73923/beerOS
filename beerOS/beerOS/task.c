#include "task.h"

uint8_t numberOfTasks = 0;
// 32 reg + sreg + eind + 3x progcnt + index 0 + magicNo
const uint8_t numberOfRegister = 32+2+3+1+1;
// 3x progcnt + magicNo + index 0
const uint8_t progcntOffset = 5;
const uint8_t magicStackNumber = 0b10101010;
typedef union {
	uint32_t u24;
	uint8_t u8[4];
} ByteAccessUnion;

void initTaskControlBlock(uint8_t prio, uint8_t* stack, uint16_t stackSize);
void placeMagicNumberOnStack(uint8_t* stack, uint16_t stackSize);
void placeStartAdressOnStack(uint8_t* stack, void* taskFunction, uint16_t stackSize);

void initTask(uint8_t prio, uint8_t* stack, void* taskFunction, uint16_t stackSize){
	initTaskControlBlock(prio, stack, stackSize);
	placeMagicNumberOnStack(stack, stackSize);
	placeStartAdressOnStack(stack, taskFunction, stackSize);	
}

void initTaskControlBlock(uint8_t prio, uint8_t* stack, uint16_t stackSize){
	taskControlBlock *cb = &tcb[numberOfTasks];
	numberOfTasks++;
	cb->prio = prio;
	cb->stackSize = stackSize;
	cb->stackBeginn = stack;
	cb->stackPointer = stack + (stackSize - numberOfRegister);
	cb->state = READY;	
	cb->semaNextWaiting = NULL;
	cb->waitUntil = 0;
}

void placeMagicNumberOnStack(uint8_t* stack, uint16_t stackSize){
	stack[stackSize-1] = magicStackNumber;
}

void placeStartAdressOnStack(uint8_t* stack, void* taskFunction, uint16_t stackSize){
	ByteAccessUnion byteAccessUnion;
	byteAccessUnion.u24 = (uint32_t) taskFunction;
	
	stack[stackSize-2] = byteAccessUnion.u8[0];
	stack[stackSize-3] = byteAccessUnion.u8[1];
	stack[stackSize-4] = byteAccessUnion.u8[2];
}

void wakeupLinkedTasks(likedSyncObject* syncObj){
	while(syncObj->firstWaiting != NULL){
		taskControlBlock* tb = syncObj->firstWaiting;
		tb->state = READY;
		syncObj->firstWaiting = NULL;
		syncObj->firstWaiting = tb->semaNextWaiting;
	}
}

void queueWaitingTask(likedSyncObject* syncObj, taskControlBlock* newTask){
	while(syncObj->firstWaiting != NULL)
		syncObj = syncObj->firstWaiting;
	syncObj->firstWaiting = newTask;
	newTask->state = WAITING;
}