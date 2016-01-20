#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "beerOSTypes.h"

typedef struct ListItem{
	struct ListItem *next;
	uint8_t *this;
}ListItem;

typedef struct {
	ListItem *list;
	ListItem *current;
	uint8_t length;
	uint8_t currentIndex;
}LinkedList;

uint8_t init_linkedList(LinkedList *linkedList);

uint8_t linkedList_add(LinkedList *linkedList, void *item, uint8_t index);
uint8_t linkedList_append(LinkedList *linkedList, void *item);
//uint8_t insertafter_linkedlist(linkedlist *linkedlist, void *item);
//uint8_t insertbefore_linkedlist(linkedlist *linkedlist, void *item);

void linkedList_remove(LinkedList *linkedList, uint8_t index);

uint8_t linkedList_first(LinkedList *linkedList, void **item);
uint8_t linkedList_last(LinkedList *linkedList, void **item);
uint8_t linkedList_get(LinkedList *linkedList, uint8_t index, void **item);

uint8_t linkedList_length(LinkedList *linkedList);

#endif /* LINKEDLIST_H_ */