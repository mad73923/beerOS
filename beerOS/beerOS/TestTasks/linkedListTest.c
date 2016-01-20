/*
 * linkedListTest.c
 *
 * Created: 09.12.2015 19:36:53
 *  Author: anreinha
 */ 

#include "../linkedList.h"
#include "testTasks.h"


static int testValues[5] = {1, 2, 3, 4, 5};
static LinkedList linkedList;

void linkedListTestTask(){
	if(init_linkedList(&linkedList)){
		kernelPanic();
	}	
	
	int *value;
	for(int i = 0; i < 5; i++){
		if(append_linkedList(&linkedList, &testValues[i])){
			kernelPanic();		
		}	
	}
	
	for(uint8_t j = 0; j < 5; j++){
		if(get_linkedList(&linkedList, j, &value)){
				kernelPanic();			
		} else {
			if(*value != j + 1){
				kernelPanic();
			}
		}	
	}
	
	
}