#include "../memoryManagement.h"
#include "../memoryManagementInternal.h"
#include "testTasks.h"

uint16_t testTask(uint16_t pew){
	
}

void memoryManagementTestTask(){
	memoryManagement_init(testTask);
}

