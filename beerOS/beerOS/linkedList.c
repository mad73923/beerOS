/*
 * linkedList.c
 *
 * Created: 25.11.2015 17:57:12
 *  Author: anreinha
 */ 



void init_linkedList(LinkedList *linkedList, ListItem *listItem){	
	linkedList->list = listItem;
	linkedList->current = NULL;
	linkedList->currentIndex = 0;
	linkedList->length = 0;
	linkedList->size = sizeof(linkedList)/sizeof(linkedList[0]);
}

uint8_t add_linkedList(LinkedList *linkedList, void *item, uint8_t index){
	return 1;
}



void append_linkedList(LinkedList *linkedList, void *item){
	
	if(isFull(linkedList))
		return 1;
	
	
	linkedList->list[linkedList->currentIndex].this= item;
	linkedList->length = linkedList->length + 1;	
}

bool isFull(LinkedList *linkedList){
	return length == size;
}

uint8_t insertAfter_linkedList(LinkedList *linkedList, void *item);
uint8_t insertBefore_linkedList(LinkedList *linkedList, void *item);

void remove_linkedList(LinkedList *linkedList){
	removeAt_linkedList(linkedList, linkedList->currentIndex);	
}

void removeAt_linkedList(LinkedList *linkedList, uint8_t index){
	uint8_t start = index;
	uint8_t end = linkedList->length - 1;
	ListItem list = linkedList->list;
	
	for(uint8_t i = start; i < end; i++){
		list[i] = list[i + 1];
	}
	
	linkedList->length = end;
}

uint8_t next_linkedList(LinkedList *linkedList){
	uint8_t newIndex = (linkedList->currentIndex + 1) % linkedList->length;
	get_linkedList(linkedList, newIndex);
	return newIndex;
}

void first_linkedList(LinkedList *linkedList){
	get_linkedList(linkedList, 0);
}

void last_linkedList(LinkedList *linkedList){
	get_linkedList(linkedList->length - 1);
}
bool get_linkedList(LinkedList *linkedList, uint8_t index){
	if(linkedList->)
	linkedList->
}

uint8_t length_linkedList(LinkedList *linkedList);