#include "memoryManagement.h"
#include "memoryManagementInternal.h"

Segment theHeap[numberOfSegments];

uint16_t firstMemHead = 0;

memoryAlgorithm memAlgo;

uint8_t memoryManagement_next(MemoryRequest *memoryRequest){
	MemoryHead memoryHead;
	uint16_t index = memoryRequest->current;
	
	uint16_t gap = 0;
	while(gap < memoryRequest->requestSize){
		memoryHead = theHeap[index].memoryHead; 
		if(memoryHead.next == 0){
			gap = numberOfSegments - memoryHead.size - index - 2;
			break;
		} else {
			gap = memoryHead.next - memoryHead.size - index - 2;
			index = memoryHead.next;
		}	
	}
	
	if(gap < memoryRequest->requestSize){
		return 0;
	}
	
	memoryRequest->current = index;
	memoryRequest->gapSize = gap;
	return 1;	
}

void memoryManagement_init(memoryAlgorithm m){
	memAlgo = m;
	memAlgo(1);
}

void memoryManagement_wipe(){
	theHeap[firstMemHead].memoryHead.next = 0;
	theHeap[firstMemHead].memoryHead.prev = numberOfSegments;
	theHeap[firstMemHead].memoryHead.size = 0;
}

uint16_t *get(uint16_t size){
	
	
	return 0;
}
void free(uint16_t *ptr){
	
}


