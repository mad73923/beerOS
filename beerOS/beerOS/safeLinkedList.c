#include "safeLinkedList.h"

void lockList(SafeLinkedList *linkedList);
void releaseList(SafeLinkedList *linkedList);

uint8_t safeLinkedList_init(SafeLinkedList *safelinkedList, semaphore *sema){
	if(linkedList_init(&safelinkedList->linkedList)){
		return 1;
	}
	safelinkedList->sema = sema;
}

uint8_t safelinkedList_add(SafeLinkedList *safeLinkedList, void *item, uint8_t index){
	lockList(safeLinkedList);
	uint8_t result = linkedList_add(&safeLinkedList->linkedList, item, index);
	releaseList(safeLinkedList);
	return result;
}
uint8_t safelinkedList_append(SafeLinkedList *safeLinkedList, void *item){
	lockList(safeLinkedList);
	uint8_t result = linkedList_append(&safeLinkedList->linkedList, item);
	releaseList(safeLinkedList);
	return result;
}

void safelinkedList_remove(SafeLinkedList *safeLinkedList, uint8_t index){
	lockList(safeLinkedList);
	linkedList_append(&safeLinkedList->linkedList, item);
	releaseList(safeLinkedList);
}

uint8_t safelinkedList_first(SafeLinkedList *safeLinkedList, void **item){
	lockList(safeLinkedList);
	uint8_t result = linkedList_first(&safeLinkedList->linkedList, item);
	releaseList(safeLinkedList);
	return result;
}
uint8_t safelinkedList_last(SafeLinkedList *safeLinkedList, void **item){
	lockList(safeLinkedList);
	uint8_t result = linkedList_last(&safeLinkedList->linkedList, item);
	releaseList(safeLinkedList);
	return result;
}
uint8_t safelinkedList_get(SafeLinkedList *safeLinkedList, uint8_t index, void **item){
	lockList(safeLinkedList);
	uint8_t result = linkedList_get(&safeLinkedList->linkedList, index, item);
	releaseList(safeLinkedList);
	return result;
}

uint8_t linkedList_length(SafeLinkedList *safeLinkedList){
	lockList(safeLinkedList);
	uint8_t result = linkedList_last(&safeLinkedList->linkedList);
	releaseList(safeLinkedList);
	return result;
}

void lockList(LinkedList *linkedList){
	if(linkedList->sema){
		waitSemaphore(linkedList->sema);
	}
}

void releaseList(LinkedList *linkedList){
	if(linkedList->sema){
		releaseSemaphore(linkedList->sema);
	}
}
