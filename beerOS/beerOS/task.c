#include "task.h"

volatile uint8_t taskStructsAreInit = 0;
volatile LinkedList allTasksList;


// 32 reg + sreg + eind + 3x progcnt + index 0 + magicNo
const uint8_t numberOfRegister = 32+2+3+1+1;
// 3x progcnt + magicNo + index 0
const uint8_t progcntOffset = 5;
const uint8_t magicStackNumber = 0b10101010;
typedef union {
	uint32_t u24;
	uint8_t u8[4];
} ByteAccessUnion;

void initTaskStructs();
void initTaskControlBlock(uint8_t prio, uint8_t* stack, uint16_t stackSize);
void placeMagicNumberOnStack(uint8_t* stack, uint16_t stackSize);
void placeStartAdressOnStack(uint8_t* stack, void* taskFunction, uint16_t stackSize);

void initTask(uint8_t prio, uint8_t* stack, void* taskFunction, uint16_t stackSize){
	if(!taskStructsAreInit){
		initTaskStructs();
		taskStructsAreInit = 1;
	}
	initTaskControlBlock(prio, stack, stackSize);
	placeMagicNumberOnStack(stack, stackSize);
	placeStartAdressOnStack(stack, taskFunction, stackSize);	
}

void initTaskStructs(){
	linkedList_init(&allTasksList);
}

void initTaskControlBlock(uint8_t prio, uint8_t* stack, uint16_t stackSize){
	if(linkedList_length(&allTasksList) >= maxNumberOfTasks){
		kernelPanic();
	}
	if(prio > maxPrio){
		kernelPanic();
	}
	taskControlBlock *cb = &tcb[linkedList_length(&allTasksList)];
	linkedList_append(&allTasksList, cb);

	cb->prio = prio;
	cb->id = linkedList_length(&allTasksList)-1;
	cb->stackSize = stackSize;
	cb->stackBeginn = stack;
	cb->stackPointer = stack + (stackSize - numberOfRegister);
	cb->state = READY;	
	cb->waitUntil = 0;
}

void placeMagicNumberOnStack(uint8_t* stack, uint16_t stackSize){
	stack[0] = magicStackNumber;
	stack[stackSize-1] = magicStackNumber;
}

void placeStartAdressOnStack(uint8_t* stack, void* taskFunction, uint16_t stackSize){
	ByteAccessUnion byteAccessUnion;
	byteAccessUnion.u24 = (uint32_t) taskFunction;
	
	stack[stackSize-2] = byteAccessUnion.u8[0];
	stack[stackSize-3] = byteAccessUnion.u8[1];
	stack[stackSize-4] = byteAccessUnion.u8[2];
}

void wakeupLinkedTasks(linkedSyncObject* syncObj){
	taskControlBlock* task;
	uint8_t length = linkedList_length(&syncObj->waitingTasks);
	if(length > 0){
		while(linkedList_iter(&syncObj->waitingTasks, &task)){
			task->state = READY;
			scheduler_enqueueTask(task);
		}
		for(int i = 0; i < length; i++){
			linkedList_remove(&syncObj->waitingTasks, 0);
		}
	}
}

void queueWaitingTask(linkedSyncObject* syncObj, taskControlBlock* newTask){
	linkedList_append(&syncObj->waitingTasks, newTask);
	newTask->state = WAITING;
}