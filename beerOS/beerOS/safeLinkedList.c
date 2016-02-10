#include "safeLinkedList.h"

void lockList(SafeLinkedList *safeLinkedList);
void releaseList(SafeLinkedList *safeLinkedList);

uint8_t safeLinkedList_init(SafeLinkedList *safeLinkedList, semaphore *sema){
	if(linkedList_init(&safeLinkedList->linkedList)){
		return 1;
	}
	safeLinkedList->sema = sema;
}

uint8_t safeLinkedList_add(SafeLinkedList *safeLinkedList, void *item, uint8_t index){
	lockList(safeLinkedList);
	uint8_t result = linkedList_add(&safeLinkedList->linkedList, item, index);
	releaseList(safeLinkedList);
	return result;
}
uint8_t safeLinkedList_append(SafeLinkedList *safeLinkedList, void *item){
	lockList(safeLinkedList);
	uint8_t result = linkedList_append(&safeLinkedList->linkedList, item);
	releaseList(safeLinkedList);
	return result;
}

void safeLinkedList_remove(SafeLinkedList *safeLinkedList, uint8_t index){
	lockList(safeLinkedList);
	linkedList_remove(&safeLinkedList->linkedList, index);
	releaseList(safeLinkedList);
}

uint8_t safeLinkedList_first(SafeLinkedList *safeLinkedList, void **item){
	lockList(safeLinkedList);
	uint8_t result = linkedList_first(&safeLinkedList->linkedList, item);
	releaseList(safeLinkedList);
	return result;
}
uint8_t safeLinkedList_last(SafeLinkedList *safeLinkedList, void **item){
	lockList(safeLinkedList);
	uint8_t result = linkedList_last(&safeLinkedList->linkedList, item);
	releaseList(safeLinkedList);
	return result;
}
uint8_t safeLinkedList_get(SafeLinkedList *safeLinkedList, uint8_t index, void **item){
	lockList(safeLinkedList);
	uint8_t result = linkedList_get(&safeLinkedList->linkedList, index, item);
	releaseList(safeLinkedList);
	return result;
}

uint8_t safeLinkedList_length(SafeLinkedList *safeLinkedList){
	lockList(safeLinkedList);
	uint8_t result = linkedList_length(&safeLinkedList->linkedList);
	releaseList(safeLinkedList);
	return result;
}

void lockList(SafeLinkedList *safeLinkedList){
	if(safeLinkedList->sema){
		semaphore_request(safeLinkedList->sema);
	}
}

void releaseList(SafeLinkedList *safeLinkedList){
	if(safeLinkedList->sema){
		semaphore_release(safeLinkedList->sema);
	}
}	
