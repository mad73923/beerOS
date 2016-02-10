#include "init.h"

uint8_t mainCalled __attribute__ ((section (".noinit"))) = 0;

int main(void){
	if(mainCalled){
		kernelPanic();
	}
	mainCalled++;
	memoryManagement_initModule(firstFit);
	linkedList_initModule();
	return run();
}