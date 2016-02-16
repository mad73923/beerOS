/*
 * LinkedListTypes.h
 *
 * Created: 10.02.2016 16:43:01
 *  Author: anreinha
 */ 


#ifndef LINKEDLISTTYPES_H_
#define LINKEDLISTTYPES_H_


typedef struct {
	struct ListItem *list;
	struct ListItem *current;
	uint8_t length;
	uint8_t currentIndex;
	uint8_t isIterating;
}LinkedList;




#endif /* LINKEDLISTTYPES_H_ */