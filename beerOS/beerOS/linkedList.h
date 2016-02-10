#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "beerOSTypes.h"
#include "memoryManagement.h"
#include "linkedListTypes.h"
#include "sync.h"

typedef struct ListItem{
	struct ListItem *next;
	uint8_t *this;
}ListItem;

uint8_t linkedList_init(LinkedList *linkedList);

uint8_t linkedList_add(LinkedList *linkedList, void *item, uint8_t index);
uint8_t linkedList_append(LinkedList *linkedList, void *item);
//uint8_t insertafter_linkedlist(linkedlist *linkedlist, void *item);
//uint8_t insertbefore_linkedlist(linkedlist *linkedlist, void *item);

void linkedList_remove(LinkedList *linkedList, uint8_t index);
uint8_t linkedList_removeItem(LinkedList *linkedList, void *item);
void linkedList_removeAll(LinkedList *linkedList);

uint8_t linkedList_first(LinkedList *linkedList, void **item);
uint8_t linkedList_last(LinkedList *linkedList, void **item);
uint8_t linkedList_get(LinkedList *linkedList, uint8_t index, void **item);
uint8_t linkedList_iter(LinkedList *linkedList, void **item);

uint8_t linkedList_length(LinkedList *linkedList);
uint8_t linkedList_contains(LinkedList *linkedList, void *item);

#endif /* LINKEDLIST_H_ */