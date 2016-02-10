#include "linkedList.h"

ListItem linkedListMem[256];
uint8_t allocMem(ListItem** listItem);
void freeMem(ListItem* listItem);
uint8_t outOfBound(LinkedList *linkedList, uint8_t index);
uint8_t getInternal(LinkedList *linkedList, uint8_t index, void **item);

uint8_t linkedList_init(LinkedList *linkedList){
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

uint8_t linkedList_add(LinkedList *linkedList, void *item, uint8_t index){		
	ListItem *newListItem;
	
	if(allocMem(&newListItem)){
		return 1;
	}
	
	if(getInternal(linkedList, index, NULL)){
		return 1;
	}
	
	newListItem->next = (ListItem*) linkedList->current->next;
	linkedList->current->next = newListItem;		
	newListItem->this= item;
	
	linkedList->length++;		
	
	return 0;
}

uint8_t getInternal(LinkedList *linkedList, uint8_t index, void **item){
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



uint8_t linkedList_append(LinkedList *linkedList, void *item){
	if(linkedList_add(linkedList, item, linkedList->length)){
		return 1;
	}
	return 0;
}

uint8_t insertAfter_linkedList(LinkedList *linkedList, void *item){
	kernelPanic();
}

uint8_t insertBefore_linkedList(LinkedList *linkedList, void *item){
	kernelPanic();
}

void linkedList_remove(LinkedList *linkedList, uint8_t index){
	if(getInternal(linkedList, index, NULL)){
		return;
	}
	ListItem *toRemove = linkedList->current->next;
	linkedList->current->next = toRemove->next;
	linkedList->length--;
	freeMem(toRemove);
}

uint8_t linkedList_removeItem(LinkedList *linkedList, void *item){
	void *nextItem;
	for(uint8_t i = 0; i < linkedList->length; i++){
		linkedList_get(linkedList, i, &nextItem);
		if(nextItem == item){
			return 0;
		}
	}
	return 1;
}

void linkedList_removeAll(LinkedList *linkedList){
	while(linkedList->length){
		linkedList_remove(linkedList, 0);
	}
}

uint8_t linkedList_first(LinkedList *linkedList, void **item){
	linkedList_get(linkedList, 0, item);
}

uint8_t linkedList_last(LinkedList *linkedList, void **item){
	linkedList_get(linkedList, linkedList->length - 1, item);
}

uint8_t linkedList_get(LinkedList *linkedList, uint8_t index, void **item){
	return getInternal(linkedList, index + 1, item);
}

uint8_t linkedList_length(LinkedList *linkedList){
	return linkedList->length;
}

uint8_t linkedList_contains(LinkedList *linkedList, void *item){
	void *currentItem;
	for(uint8_t i = 0; i < linkedList->length; i++){
		linkedList_get(linkedList, i, &currentItem);
		if(currentItem == item){
			return 1;
		}
	}
	return 0;
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

uint8_t linkedList_iter(LinkedList *linkedList, void **item){
	if(linkedList->length == 0){
		return 0;
	}
	
	if(!linkedList->isIterating){
		linkedList->current = linkedList->list->next;
		linkedList->isIterating = 1;
		linkedList->currentIndex = 0;
	}else if(!linkedList->current->next){
		linkedList->isIterating = 0;
		return 0;		
	} else {
		linkedList->current = linkedList->current->next;
		linkedList->currentIndex++;
	}
	
	*item = linkedList->current->this;
	return 1;
}

linkedList_iterReset(LinkedList *linkedList){
	linkedList->isIterating = 0;
}


void freeMem(ListItem* listItem){
	listItem->this = NULL;
}

