/*
 * memoryManagement.h
 *
 * Created: 01.12.2015 12:26:21
 *  Author: anreinha
 */ 


#ifndef MEMORYMANAGEMENT_H_
#define MEMORYMANAGEMENT_H_

typedef struct{
	uint32_t data;	
}Segment;

static const uint32_t MEMORY_SIZE = 2**20;
uint32_t numberOfSegments = MEMORY_SIZE/sizeof(Segment);

Segment stash[numberOfSegments];

int get(uint8_t **ptr, uint16_t size);
void free(uint8_t *ptr);


#endif /* MEMORYMANAGEMENT_H_ */