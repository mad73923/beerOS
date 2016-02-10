#ifndef MEMORYMANAGEMENT_H_
#define MEMORYMANAGEMENT_H_

#include "beerOSTypes.h"
#include "sync.h"

void* alloc(uint8_t size);
void free(uint16_t *ptr);

#ifndef numberOfSegments
#define numberOfSegments 256
#endif

#endif /* MEMORYMANAGEMENT_H_ */