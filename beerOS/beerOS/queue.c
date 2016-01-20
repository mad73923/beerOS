#include "queue.h"

uint8_t queue_init(Queue *queue){
	return linkedList_init(&queue->linkedList);
}
uint8_t queue_push(Queue *queue, void *item){
	return linkedList_append(&queue->linkedList, item);
}
uint8_t queue_pop(Queue *queue, void **item){
	
}
uint8_t queue_peek(Queue *queue, void **item);
uint8_t queue_isEmpty(Queue *queue);