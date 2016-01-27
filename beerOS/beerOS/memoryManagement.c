#include "memoryManagement.h"
#include "memoryManagementInternal.h"

Segment theHeap[numberOfSegments];

uint16_t firstMemHead = 0;

memoryAlgorithm memAlgo;

uint16_t memoryManagement_next(MemoryRequest *memoryRequest){
	MemoryHead memoryHead;
	uint16_t index = memoryRequest->memId;
	uint16_t lastIndex = index;
	
	uint16_t gap = 0;
	while(gap < memoryRequest->requestSize){
		memoryHead = theHeap[index].memoryHead;
		if(memoryHead.next == 0){
			uint8_t overhead = 2;
			if(memoryHead.size == 0){
				overhead = 1;
			}
			gap = numberOfSegments - memoryHead.size - index - overhead;
			lastIndex = index;
			break;
		} else {
			gap = memoryHead.next - memoryHead.size - index - 1;
			if(gap > 0){
				gap--;
			}
			lastIndex = index;
			index = memoryHead.next;						
		}		
	}
	
	if(gap < memoryRequest->requestSize){
		return 0;
	}
	
	
	memoryRequest->memId = index;
	memoryRequest->gapSize = gap;
	return lastIndex + 1;	
}

void memoryManagement_init(memoryAlgorithm m){
	memAlgo = m;
}

void* memoryManagement_alloc(MemoryRequest *memoryRequest){
	uint16_t memIdBefore = memoryRequest->memId - 1;
	MemoryHead *memoryHeadBefore = &theHeap[memIdBefore].memoryHead;
	uint16_t newMemId = memIdBefore;
	if(memoryHeadBefore->size){
		newMemId += memoryHeadBefore->size + 1;
	}	 	
	
	MemoryHead *newMemoryHead = &theHeap[newMemId].memoryHead;
	if(memoryHeadBefore->next){
		MemoryHead *memoryHeadAfter = &theHeap[memoryHeadBefore->next].memoryHead;
		memoryHeadAfter->prev = newMemId;	
	}
	
	newMemoryHead->prev = memIdBefore;
	newMemoryHead->size = memoryRequest->requestSize;
	memoryHeadBefore->next = newMemId;
	
	void* pointer = &theHeap[newMemId + 1];
	return pointer;
	
}

void memoryManagement_wipe(){
	theHeap[firstMemHead].memoryHead.next = 0;
	theHeap[firstMemHead].memoryHead.prev = numberOfSegments;
	theHeap[firstMemHead].memoryHead.size = 0;
}

void memoryManagement_initMemoryRequest(MemoryRequest *memoryRequest, uint8_t size){
	memoryRequest->requestSize = size;
	memoryRequest->gapSize = 0;
	memoryRequest->memId = 0;
}

void *get(uint16_t size){
	if(!memAlgo){
		return NULL;
	}
	
	return memAlgo(size);
}
void free(uint16_t *ptr){
	
}


