#include "linkedList.h"

ListItem linkedListMem[256];
uint8_t allocMem(ListItem** listItem);
void freeMem(ListItem* listItem);
uint8_t outOfBound(LinkedList *linkedList, uint8_t index);

uint8_t allocMem(ListItem** listItem){
	uint8_t i = 0;
	while (linkedListMem[i].this != 0x0){
		i++;
		if(i >= 256){
			return 1;
		}
	}
	*listItem = &linkedListMem[i];
	return 0;
}

void freeMem(ListItem* listItem){
	listItem->this = 0x0;
}

uint8_t init_linkedList(LinkedList *linkedList){
	ListItem* listItem;
	if(allocMem(&listItem)){
		return 1;
	}
	linkedList->list = NULL;
	linkedList->current = NULL;
	linkedList->currentIndex = 0;
	linkedList->length = 0;
	return 0;
}

uint8_t add_linkedList(LinkedList *linkedList, void *item, uint8_t index){
	ListItem *newListItem;
	uint8_t newLength;
	
	if(index != 0 && outOfBound(linkedList, index)){
		return 1;
	}	
	if(allocMem(&newListItem)){
		return 1;
	}
	
	get_linkedList(linkedList, index - 1, 0x0);
	newListItem->this= item;
	newListItem->next = (ListItem*) linkedList->current->next;
	linkedList->current->next = newListItem;
	
	newLength = linkedList->length + 1;
	if(newLength == 1){
		linkedList->current = newListItem;
	}
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
	get_linkedList(linkedList, index - 1, 0x0);
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
	if(linkedList->currentIndex < index){
		linkedList->current = linkedList->list->next;
		linkedList->currentIndex = 0;
	}
	while(linkedList->currentIndex != index){
		if(linkedList->current->next == 0x0){
			return 1;
		}
		linkedList->current = linkedList->current->next;
		linkedList->currentIndex++;
		
	}
	*item = linkedList->current->this;
	return 1;
}

uint8_t length_linkedList(LinkedList *linkedList){
	return linkedList->length;
}

uint8_t outOfBound(LinkedList *linkedList, uint8_t index){
	return index >= linkedList->length;
}