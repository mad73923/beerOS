#include "queue.h"

uint8_t queue_init(Queue *queue){
	return linkedList_init(&queue->linkedList);
}
uint8_t queue_push(Queue *queue, void *item){
	return linkedList_append(&queue->linkedList, item);
}
uint8_t queue_pop(Queue *queue, void **item){
	uint8_t result = linkedList_first(&queue->linkedList, item);
	linkedList_remove(&queue->linkedList, 0);
	return result;
}
uint8_t queue_peek(Queue *queue, void **item){
	return linkedList_first(&queue->linkedList, item);
}
uint8_t queue_isEmpty(Queue *queue){
	return linkedList_length(&queue->linkedList) == 0;
}

void queue_removeAll(Queue *queue){
	linkedList_removeAll(&queue->linkedList);
}

void queue_removeItem(Queue *queue, void *item){
	linkedList_removeItem(&queue->linkedList, item);
}