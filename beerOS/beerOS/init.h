/*
 * init.h
 *
 * Created: 09.12.2015 18:18:37
 *  Author: anreinha
 */ 


#ifndef INIT_H_
#define INIT_H_

#define TEST

#ifdef TEST
#include "TestTasks/test.c"
#else
#include "beerOS.c"
#endif

#endif /* INIT_H_ */