/*
 * init.c
 *
 * Created: 09.12.2015 18:17:40
 *  Author: anreinha
 */ 

#include "init.h"

uint8_t mainCalled = 0;

int main(void){
	if(mainCalled){
		kernelPanic();
	}
	mainCalled++;
	return run();
}