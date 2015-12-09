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
	
	if(append_linkedList(&linkedList, &testValues[0])){
		kernelPanic();		
	}
	int *value;
	get_linkedList(&linkedList, 0, &value);
	if(*value != 1){
		kernelPanic();
	}
	
}