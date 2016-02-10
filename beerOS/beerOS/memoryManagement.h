#ifndef MEMORYMANAGEMENT_H_
#define MEMORYMANAGEMENT_H_

#include "beerOSTypes.h"
#include "hardware.h"

void* alloc(uint16_t size);
void free(uint16_t *ptr);
uint8_t memcopy(uint16_t *origin, uint16_t *destination);

#define numberOfSegments 256

#endif /* MEMORYMANAGEMENT_H_ */