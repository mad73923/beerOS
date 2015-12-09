/*
 * exceptions.h
 *
 * Created: 04.12.2015 12:26:46
 *  Author: matweis
 */ 


#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include "beerOSTypes.h"
#include "hardware.h"

void kernelPanic();
void beerOSAssertEqual(int cond1, int cond2);

#endif /* EXCEPTIONS_H_ */