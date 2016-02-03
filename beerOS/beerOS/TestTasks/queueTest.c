#include "../queue.h"
#include "testTasks.h"

static int testValues[5] = {1, 2, 3, 4, 5};
static Queue queue;

void initQueueTest(){
	initTask(1, task1Stack, queueTestTask, stacksize);
	initNextTest = &initPrioTest;
}	
	
void queueTestTask(){
	
	int* value;
	
	// test queue_init
	if(queue_init(&queue)){
		kernelPanic();
	}
	
	//test queue_push
	for(int i = 0; i < 5; i++){
		if(queue_push(&queue, &testValues[i])){
			kernelPanic();
		}
	}
	
	//test queue_peek
	if(queue_peek(&queue, &value)){
		kernelPanic();
	}
	
	if(*value != 1){
		kernelPanic();
	}
	
	//test queue_pop
	for(int i = 0; i < 5; i++){
		if(queue_pop(&queue, &value)){
			kernelPanic();
		}
		if(*value != i + 1){
			kernelPanic();
		}
	}
	
	//test queue_isEmpty
	if(!queue_isEmpty(&queue)){
		kernelPanic();
	}
	
	if(queue_push(&queue, &testValues[1])){
		kernelPanic();
	}
	
	if(queue_isEmpty(&queue)){
		kernelPanic();
	}
	
	beerOS_reboot();
}