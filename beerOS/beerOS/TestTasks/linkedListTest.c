/*
 * linkedListTest.c
 *
 * Created: 09.12.2015 19:36:53
 *  Author: anreinha
 */ 

#include "../linkedList.h"
#include "testTasks.h"


static int testValues[6] = {1, 2, 3, 4, 5, 6};
static LinkedList linkedList;

void initLinkedListTest(){
	initTask(1, task1Stack, linkedListTestTask, stacksize);
	initNextTest = &initQueueTest;
}
	
void linkedListTestTask(){
	
	int* value;
	
	// test linkedList_get
	if(linkedList_init(&linkedList)){
		kernelPanic();
	}
	
	//test linkedList_iter empty
	while(linkedList_iter(&linkedList, &value)){
		value;
		kernelPanic();
	}
	
	
	// test linkedList_append	
	for(int i = 0; i < 5; i++){
		if(linkedList_append(&linkedList, &testValues[i])){
			kernelPanic();		
		}	
	}	
	
	// test linkedList_get
	for(uint8_t j = 0; j < 5; j++){
		if(linkedList_get(&linkedList, j, &value)){
				kernelPanic();			
		}
		 
		if(*value != j + 1){
			kernelPanic();
		}
			
	}
	
	//test linkedList_iter
	int i = 1;
	while(linkedList_iter(&linkedList, &value)){
		if(*value != i){
			kernelPanic();
		}
		i++;
	}
	
	if(*value != 5){
			kernelPanic();
	}
	
	//test linkedList_add
	if(linkedList_add(&linkedList, &testValues[5], 2)){
		kernelPanic();
	}
	 
	if(linkedList_get(&linkedList, 2, &value)){
		kernelPanic();
	}
	
	if(*value != 6){
		kernelPanic();
	}
	
	//test linkedList_length	
	if(linkedList_length(&linkedList) != 6){
		kernelPanic();
	}
	
		
	//test linkedList_first	
	if(linkedList_first(&linkedList, &value)){
		kernelPanic();
	}
	
	if(*value != 1){
		kernelPanic();
	}
	
	//test linkedList_last	
	if(linkedList_last(&linkedList, &value)){
		kernelPanic();
	}
	
	if(*value != 5){
		kernelPanic();
	}
	
	//test linkedList_remove
	int lenghtBeforeRemove = linkedList_length(&linkedList);
	linkedList_remove(&linkedList, lenghtBeforeRemove - 1);
	
	if(linkedList_get(&linkedList, lenghtBeforeRemove - 1, NULL) == 0){
		kernelPanic();
	}
	
	beerOS_reboot();
}