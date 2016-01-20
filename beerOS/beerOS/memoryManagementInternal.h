#ifndef MEMORYMANAGEMENTINTERNAL_H_
#define MEMORYMANAGEMENTINTERNAL_H_

typedef struct{
	uint16_t prev: 12;
	uint16_t next: 12;
	uint16_t size: 8;
}MemoryHead;

typedef struct{
	uint16_t current;
	uint8_t requestSize;
	uint16_t gapSize;
}MemoryRequest;

typedef struct{
	MemoryHead memoryHead;
}Segment;

typedef uint16_t (*memoryAlgorithm)(uint16_t);

void memoryManagement_wipe();
uint8_t memoryManagement_next(MemoryRequest *memoryRequest);
void memoryManagement_init(memoryAlgorithm m);




#endif /* MEMORYMANAGEMENTINTERNAL_H_ */