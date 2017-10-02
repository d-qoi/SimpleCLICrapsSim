/*
 * ArrayList.c
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */
#include <stdlib.h>
#include <stdio.h>
#include "ArrayList.h"

ArrayList* AL_new_size(int size) {
	ArrayList* list;
	list = (ArrayList*) malloc(sizeof(ArrayList));
	if(!list)
		return 0;
	list->elements = malloc(size*sizeof(void*));
	if (!list->elements) {
		free(list);
		return 0;
	}
	list->size = 0;
	list->initMaxSize = size;
	list->maxSize = size;
	return list;
}

int AL_size(ArrayList* list) {
	return list->size;
}

int AL_add(ArrayList* list, void* e) {
	if (list->size == list->maxSize) {
		if (!AL_resize_up(list))
			return 0;
	}
	list->elements[list->size] = e;
	list->size += 1;
	return list->size-1;
}

int AL_put(ArrayList* list, void* e, int pos) {
	void* temp;
	if (pos > list->size || pos < 0)
		return 0;
	if (list->size == list->maxSize)
		if (!AL_resize_up(list))
			return 0;

	list->size += 1;
	// get the first element at pos, loop till pos it at new size, update temp, increase pos first;
	for(temp = list->elements[pos]; pos < list->size; temp = list->elements[++pos]) {
		list->elements[pos] = e;
		e = temp;
	}
	return list->size;
}

void* AL_get(ArrayList* list, int pos) {
	if (pos > list->size-1 || pos < 0)
		return 0;
	return list->elements[pos];
}

void* AL_remove(ArrayList* list, int pos) {
	void* res;
	if (pos > list->size-1 || pos < 0)
		return 0;

	res = list->elements[pos];
	while(pos < list->size) {
		list->elements[pos] = list->elements[pos+1];
		pos+=1;
	}
	list->size -= 1;
	return res;
}

int AL_contains(ArrayList* list, void* e) {
	for (int i = 0; i<list->size; i++)
		if (list->elements[i] == e)
			return i;
	return -1;
}

int AL_contains_comp(ArrayList* list, void* e, int (*comp)(void*, void*)) {
	for (int i = 0; i<list->size; i++)
		if ((*comp)(e, list->elements[i]) == 0)
			return i;
	return -1;
}

void* AL_resize_up(ArrayList* list) {
	int newSize = list->maxSize*2;
	void* newElements = realloc(list->elements, newSize*sizeof(void*));
	if (newElements) {
		list->elements = newElements;
		list->maxSize = newSize;
		return list->elements;
	}
	return newElements;
}

void AL_clear(ArrayList* list) {
	list->maxSize = list->initMaxSize;
	list->size = 0;
	free(list->elements);
	list->elements = malloc(list->maxSize*sizeof(void*));
}

void AL_clear_free(ArrayList* list) {
	for (int i = 0; i<list->size; i++) {
		free(list->elements[i]);
	}
	free(list->elements);
	list->maxSize = list->initMaxSize;
	list->size = 0;
	list->elements = malloc(list->maxSize * sizeof(void*));
}

void AL_free(ArrayList* list) {
	free(list->elements);
	free(list);
}

void AL_free_free(ArrayList* list) {
	for (int i = 0; i<list->size; i++) {
		free(list->elements[i]);
	}
	free(list->elements);
	free(list);
}
