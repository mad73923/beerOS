#include "../memoryManagement.h"
#include "../memoryManagementInternal.h"
#include "testTasks.h"

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
	void* pointer = get(16);
	void* pointer2 = get(8);
	void* pointer3 = get(20);
}

