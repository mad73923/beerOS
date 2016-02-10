#include "memoryManagementInternal.h"
#include "memoryManagementAlgos.h"

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