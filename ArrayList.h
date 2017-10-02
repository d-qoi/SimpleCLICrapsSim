/*
 * ArrayList.h
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#define ARRAY_LIST_MAX_DEFAULT 20

typedef struct ArrayListStruct {
	void** elements;
	int size;
	int maxSize;
	int initMaxSize;
} ArrayList;

#define AL_new() AL_new_size(ARRAY_LIST_MAX_DEFAULT)
ArrayList* AL_new_size(int);


int AL_size(ArrayList*);

int AL_add(ArrayList*, void*); //adds to end
int AL_put(ArrayList*, void*, int); //inserts at position.

void* AL_get(ArrayList*, int); //gets returns element at index

void* AL_remove(ArrayList*, int);

int AL_contains(ArrayList*, void*); //returns index of object in array with same pointer as one passed.
int AL_contains_comp(ArrayList*, void*, int (*comp)(void*, void*));
// AL_contains_comp takes a comparator.
// comp(contains, element in AL)
// assumes 0 is equal, 1 is greater than -1 is less than. only uses 0 for equal.
// will return first encounter.
/* as an example, wrapping memcmp for two structs
 *
 * int comp(struct* this, struct* that) {
 * 	 return memcpr(this, that, sizeof(struct)
 * }
 */
void* AL_resize_up(ArrayList*); //doubles the size of the list.

void AL_clear(ArrayList*); //clears list
void AL_clear_free(ArrayList*); //clears list and frees all elements in list.
void AL_free(ArrayList*); //actual cleanup, use this rather than free.
void AL_free_free(ArrayList*); //free list first, rather than just freeing the struct.

#endif /* ARRAYLIST_H_ */
