#include "../memoryManagement.h"
#include "../memoryManagementInternal.h"
#include "testTasks.h"

void initMemoryManagementTest(){
	initTask(1, task1Stack, memoryManagementTestTask, stacksize);
}

uint16_t firstFit(uint16_t size){
	MemoryRequest memoryRequest;
	memoryManagement_initMemoryRequest(&memoryRequest, size);
	uint16_t memId = 0;
	while(memId = memoryManagement_next(&memoryRequest)){
		memoryRequest.memId = memId;
		return memoryManagement_alloc(&memoryRequest);
	}
	return NULL;
}

void alloc5_free_alloc5(){
	Segment* seg1 = (Segment*) alloc(5);
	free(seg1);
	Segment* seg2 = (Segment*) alloc(5);
	
	if(seg1 != seg2){
		kernelPanic();
	}
}

void tooSmallGap(){
	Segment* seg1 = (Segment*) alloc(5);
	Segment* seg2 = (Segment*) alloc(5);
	Segment* seg3 = (Segment*) alloc(5);
	free(seg2);
	Segment* seg4 = (Segment*) alloc(6);
	
	if(seg2 == seg4){
		kernelPanic();
	}	
}

void fittingGap(){
	Segment* seg1 = (Segment*) alloc(5);
	Segment* seg2 = (Segment*) alloc(5);
	Segment* seg3 = (Segment*) alloc(5);
	free(seg2);
	Segment* seg4 = (Segment*) alloc(5);
	
	if(seg2 != seg4){
		kernelPanic();
	}	
}

void outOfMemory(){
	Segment* seg1 = (Segment*) alloc(200);
	Segment* seg2 = (Segment*) alloc(200);
	if(seg2 != NULL){
		kernelPanic();
	}
	
}

void memoryManagementTestTask(){
	memoryManagement_init(firstFit);	
	
	alloc5_free_alloc5();	
	memoryManagement_wipe();
	
	tooSmallGap();
	memoryManagement_wipe();
	
	fittingGap();
	memoryManagement_wipe();
	
	outOfMemory();
	memoryManagement_wipe();	
	
	beerOS_reboot();
}



