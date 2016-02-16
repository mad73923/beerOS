#include "../memoryManagement.h"
#include "memoryManagementInternal.h"

Segment theHeap[numberOfSegments];

uint16_t firstMemHead = 0;

memoryAlgorithm memAlgo;
MemoryHead* memoryHeadFromPointer(uint16_t *ptr);

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


void *alloc(uint16_t size){
	if(!memAlgo){
		return NULL;
	}	
	
	if(size > 256*sizeof(Segment) || size == 0){
		return NULL;
	}
	
	uint8_t state = enterCriticalSection();
	uint16_t segments = size/sizeof(Segment);
	if(size%sizeof(Segment)){
		segments++;
	}
	void* pointer = memAlgo(segments);
	leaveCriticalSection(state);
	return pointer;
}

void free(uint16_t *ptr){
	uint8_t state = enterCriticalSection();
	MemoryHead* memoryHead = memoryHeadFromPointer(ptr);
	
	if(memoryHead->size > 0){
		uint16_t prev = memoryHead->prev;
		uint16_t next = memoryHead->next;
		memoryHead->size = 0;
		
		memoryHead = &theHeap[prev].memoryHead;
		memoryHead->next = next;
		
		memoryHead = &theHeap[next].memoryHead;
		memoryHead->prev = prev;
	}
	leaveCriticalSection(state);
}

uint8_t memcopy(uint16_t *origin, uint16_t *destination){
	uint8_t state = enterCriticalSection();
	MemoryHead* originHead = memoryHeadFromPointer(origin);
	MemoryHead* destinationHead = memoryHeadFromPointer(destination);
	
	if(originHead->size > destinationHead->size){
		return 1;
	}
	
	Segment *originSegment = (Segment*) origin;
	Segment *destinationSegment = (Segment*) destination;
	uint8_t current = 0;
	while(current < originHead->size){		
		*destination = *origin;
		originSegment++;
		destinationSegment++;
		current++;
	}	
	leaveCriticalSection(state);
	return 0;
}

MemoryHead* memoryHeadFromPointer(uint16_t *ptr){
		Segment *segment = (Segment*) ptr;
		segment--;
		return &segment->memoryHead;
}

