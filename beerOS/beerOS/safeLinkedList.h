#ifndef SAFELINKEDLIST_H_
#define SAFELINKEDLIST_H_

#include "beerOSTypes.h"
#include "sync.h"

typedef struct {
	LinkedList linkedList;
	semaphore *sema;
}SafeLinkedList;

uint8_t safeLinkedList_init(SafeLinkedList *safeLinkedList, semaphore *sema);

uint8_t safelinkedList_add(SafeLinkedList *safeLinkedList, void *item, uint8_t index);
uint8_t safelinkedList_append(SafeLinkedList *safeLinkedList, void *item);

void safelinkedList_remove(SafeLinkedList *safeLinkedList, uint8_t index);

uint8_t safelinkedList_first(SafeLinkedList *safeLinkedList, void **item);
uint8_t safelinkedList_last(SafeLinkedList *safeLinkedList, void **item);
uint8_t safelinkedList_get(SafeLinkedList *safeLinkedList, uint8_t index, void **item);

uint8_t linkedList_length(SafeLinkedList *safeLinkedList);

#endif /* SAFELINKEDLIST_H_ */