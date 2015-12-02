#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define DISPISRVEC TCF0_OVF_vect

void scheduleNextTask();

#endif /* SCHEDULER_H_ */