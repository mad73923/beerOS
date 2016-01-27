#ifndef QUEUE_H_
#define QUEUE_H_

#include "beerOSTypes.h"
#include "linkedList.h"

typedef struct{
	LinkedList linkedList;
} Queue;

uint8_t queue_init(Queue *queue);
uint8_t queue_push(Queue *queue, void *item);
uint8_t queue_pop(Queue *queue, void **item);
uint8_t queue_isEmpty(Queue *queue);
uint8_t queue_peek(Queue *queue, void **item);

#endif /* QUEUE_H_ */