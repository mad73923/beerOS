#ifndef MEMORYMANAGEMENT_H_
#define MEMORYMANAGEMENT_H_

#include "beerOSTypes.h"

uint16_t *get(uint16_t size);
void free(uint16_t *ptr);

#define numberOfSegments 32


#endif /* MEMORYMANAGEMENT_H_ */