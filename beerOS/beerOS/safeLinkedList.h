#ifndef SAFELINKEDLIST_H_
#define SAFELINKEDLIST_H_

#include "beerOSTypes.h"
#include "sync.h"
#include "linkedList.h"

typedef struct {
	LinkedList linkedList;
	semaphore *sema;
}SafeLinkedList;

uint8_t safeLinkedList_init(SafeLinkedList *safeLinkedList, semaphore *sema);

uint8_t safeLinkedList_add(SafeLinkedList *safeLinkedList, void *item, uint8_t index);
uint8_t safeLinkedList_append(SafeLinkedList *safeLinkedList, void *item);

void safeLinkedList_remove(SafeLinkedList *safeLinkedList, uint8_t index);

uint8_t safeLinkedList_first(SafeLinkedList *safeLinkedList, void **item);
uint8_t safeLinkedList_last(SafeLinkedList *safeLinkedList, void **item);
uint8_t safeLinkedList_get(SafeLinkedList *safeLinkedList, uint8_t index, void **item);

uint8_t safeLinkedList_length(SafeLinkedList *safeLinkedList);

#endif /* SAFELINKEDLIST_H_ */