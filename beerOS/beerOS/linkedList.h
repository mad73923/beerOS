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

uint8_t add_linkedList(LinkedList *linkedList, void *item, uint8_t index);
uint8_t append_linkedList(LinkedList *linkedList, void *item);
//uint8_t insertAfter_linkedList(LinkedList *linkedList, void *item);
//uint8_t insertBefore_linkedList(LinkedList *linkedList, void *item);

void remove_linkedList(LinkedList *linkedList);
void removeAt_linkedList(LinkedList *linkedList, uint8_t index);

//uint8_t next_linkedList(LinkedList *linkedList);
//void first_linkedList(LinkedList *linkedList);
//void last_linkedList(LinkedList *linkedList);
uint8_t get_linkedList(LinkedList *linkedList, uint8_t index, void **item);

uint8_t length_linkedList(LinkedList *linkedList);

#endif /* LINKEDLIST_H_ */