/*
 * linkedList.h
 *
 * Created: 25.11.2015 17:56:28
 *  Author: anreinha
 */ 


#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

void init_linkedList(LinkedList *linkedList);
uint8_t next_linkedList(LinkedList *linkedList);
uint8_t insertAfter_linkedList(LinkedList *linkedList, void *item);
uint8_t insertAfter_linkedList(LinkedList *linkedList, void *item);
void remove_linkedList(LinkedList *linkedList, uint8_t index);
void first_linkedList(LinkedList *linkedList);
void last_linkedList(LinkedList *linkedList);
void add_linkedList(LinkedList *linkedList, void *item, uint8_t index);
void append_linkedList(LinkedList *linkedList, void *item);
void length
init(&myList);
add(&myList, &item);
remove(&myList, 4);


#endif /* LINKEDLIST_H_ */