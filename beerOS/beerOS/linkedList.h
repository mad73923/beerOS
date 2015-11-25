/*
 * linkedList.h
 *
 * Created: 25.11.2015 17:56:28
 *  Author: anreinha
 */ 


#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct {
	ListItem *list;
	void *current;
	uint8_t size;
	uint8_t length;
	uint8_t currentIndex;
}LinkedList;

typedef struct {
	void *this;
}ListItem;


void init_linkedList(LinkedList *linkedList, ListItem *listItem);

void add_linkedList(LinkedList *linkedList, void *item, uint8_t index);
void append_linkedList(LinkedList *linkedList, void *item);
uint8_t insertAfter_linkedList(LinkedList *linkedList, void *item);
uint8_t insertBefore_linkedList(LinkedList *linkedList, void *item);

void remove_linkedList(LinkedList *linkedList);
void removeAt_linkedList(LinkedList *linkedList, uint8_t index);

uint8_t next_linkedList(LinkedList *linkedList);
void first_linkedList(LinkedList *linkedList);
void last_linkedList(LinkedList *linkedList);
void get_linkedList(LinkedList *linkedList, uint8_t index);

uint8_t length_linkedList(LinkedList *linkedList);

#endif /* LINKEDLIST_H_ */