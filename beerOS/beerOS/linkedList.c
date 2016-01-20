#include "linkedList.h"

ListItem linkedListMem[256];
uint8_t allocMem(ListItem** listItem);
void freeMem(ListItem* listItem);
uint8_t outOfBound(LinkedList *linkedList, uint8_t index);
uint8_t getInternal_linkedList(LinkedList *linkedList, uint8_t index, void **item);


uint8_t init_linkedList(LinkedList *linkedList){
	ListItem* listItem;
	if(allocMem(&listItem)){
		return 1;
	}
	linkedList->list = listItem;
	listItem->this = listItem;
	linkedList->current = NULL;
	linkedList->currentIndex = 0;
	linkedList->length = 0;
	return 0;
}

uint8_t add_linkedList(LinkedList *linkedList, void *item, uint8_t index){
	ListItem *newListItem;
	
	if(allocMem(&newListItem)){
		return 1;
	}
	
	if(getInternal_linkedList(linkedList, index, NULL)){
		return 1;
	}
	
	newListItem->next = (ListItem*) linkedList->current->next;
	linkedList->current->next = newListItem;		
	newListItem->this= item;	
	linkedList->length++;
	
	return 0;
}

uint8_t getInternal_linkedList(LinkedList *linkedList, uint8_t index, void **item){
	if(index > linkedList->length){
		return 1;
	}
	
	linkedList->current = linkedList->list;
		
	for(linkedList->currentIndex = 0; linkedList->currentIndex < index; linkedList->currentIndex++){
		linkedList->current = linkedList->current->next;
	}
	
	*item = linkedList->current->this;
	
	return 0;
}	



uint8_t append_linkedList(LinkedList *linkedList, void *item){
	if(add_linkedList(linkedList, item, linkedList->length)){
		return 1;
	}
	return 0;
}

uint8_t insertAfter_linkedList(LinkedList *linkedList, void *item);
uint8_t insertBefore_linkedList(LinkedList *linkedList, void *item);

void remove_linkedList(LinkedList *linkedList){
	removeAt_linkedList(linkedList, linkedList->currentIndex);	
}

void removeAt_linkedList(LinkedList *linkedList, uint8_t index){
	getInternal_linkedList(linkedList, index, NULL);
	ListItem *toRemove = linkedList->current->next;
	linkedList->current->next = toRemove->next;
	freeMem(toRemove);
}

//uint8_t next_linkedList(LinkedList *linkedList){
	//uint8_t newIndex = (linkedList->currentIndex + 1) % linkedList->length;
	//get_linkedList(linkedList, newIndex);
	//return newIndex;
//}
//
//void first_linkedList(LinkedList *linkedList){
	//get_linkedList(linkedList, 0);
//}
//
//void last_linkedList(LinkedList *linkedList){
	//get_linkedList(linkedList->length - 1);
//}
//
uint8_t get_linkedList(LinkedList *linkedList, uint8_t index, void **item){
	return getInternal_linkedList(linkedList, index + 1, item);
}

uint8_t length_linkedList(LinkedList *linkedList){
	return linkedList->length;
}

uint8_t outOfBound(LinkedList *linkedList, uint8_t index){
	return index >= linkedList->length;
}

uint8_t allocMem(ListItem** listItem){
	uint8_t i = 0;
	while (linkedListMem[i].this != NULL){
		i++;
		if(i >= 256){
			return 1;
		}
	}
	*listItem = &linkedListMem[i];
	return 0;
}

void freeMem(ListItem* listItem){
	listItem->this = NULL;
}