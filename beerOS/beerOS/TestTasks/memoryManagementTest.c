#include "../memoryManagement.h"
#include "../MemoryManagement/memoryManagementInternal.h"
#include "../MemoryManagement/memoryManagementAlgos.h"
#include "testTasks.h"

void initMemoryManagementTest(){
	initTask(1, task1Stack, memoryManagementTestTask, stacksize);
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



