#include "../memoryManagement.h"
#include "../memoryManagementInternal.h"
#include "testTasks.h"

void initMemoryManagementTest(){
	initTask(1, task1Stack, memoryManagementTestTask, stacksize);
}

uint16_t testTask(uint16_t size){
	MemoryRequest memoryRequest;
	memoryManagement_initMemoryRequest(&memoryRequest, size);
	uint16_t memId = 0;
	while(memId = memoryManagement_next(&memoryRequest)){
		memoryRequest.memId = memId;
		return memoryManagement_alloc(&memoryRequest);
	}
	return NULL;
}

void memoryManagementTestTask(){
	memoryManagement_init(testTask);
	Segment* seg = (Segment*) get(5);
	Segment* mh = seg - 1;
	Segment* seg2 = (Segment*) get(5);
	Segment* mh2 = seg2 - 1;
	Segment* seg3 = (Segment*) get(5);
	Segment* mh3 = seg3 - 1;
	free(seg2);
	Segment* seg4 = (Segment*) get(6);
	Segment* mh4 = seg4 - 1;
	Segment* seg5 = (Segment*) get(5);
	Segment* mh5 = seg5 - 1;
	beerOS_reboot();
}

