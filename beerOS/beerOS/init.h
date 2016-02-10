#ifndef INIT_H_
#define INIT_H_

#define TEST

#ifdef TEST
#include "TestTasks/test.c"
#else
#include "beerOS.c"
#endif

#include "MemoryManagement/memoryManagementInternal.h"
#include "MemoryManagement/memoryManagementAlgos.h"
#include "linkedList.h"

#endif /* INIT_H_ */