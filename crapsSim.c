/*
 ============================================================================
 Name        : crapsSim.c
 Author      : Alexander Hirschfeld
 Version     :
 Copyright   : Free to use and distribute?
 Description : Craps game sim maybe?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "dice.h"
#include "ArrayList.h"
#include "table.h"

#ifdef DEBUG
int diceTest() {
	roll* temp = (roll*)malloc(sizeof(roll));
	for (int i = 1; i<7; i++) {
		for (int j = 1; j<7; j++) {
			temp->dice_1 = i;
			temp->dice_2 = j;
			checkRoll(temp);
			if (((i+j == 2) || (i+j == 3) || (i+j == 12)) && temp->crap != TRUE) {
					printf("%d, %d gives not craps\n", i, j);
					return 0;
			} else if ((i+j>3 && i+j<12) && temp->crap) {
				printf("%d, %d gives craps\n", i, j);
				return 0;
			}
			if ((i == j) && (temp->hard != TRUE)) {
				printf("%d, %d does not give hard\n", i, j);
				return 0;
			} else if ( i != j && temp->hard) {
				printf("%d, %d gives hard\n", i, j);
				return 0;
			}
			if (i + j == 7 && temp->seven != TRUE) {
				printf("%d, %d does not give seven\n", i, j);
				return 0;
			} else if (i + j != 7 && temp->seven) {
				printf("%d, %d gives seven\n", i, j);
				return 0;
			}
			if ( (i + j == 7 || i + j == 11) && temp->natural == FALSE) {
				printf("%d, %d doesn't give natural\n", i, j);
				return 0;
			} else if (i + j != 7 && i + j != 11 && temp->natural) {
				printf("%d, %d gives natural\n", i, j);
				return 0;
			}
		}
	}
	return 1;
}

void printArrayList(ArrayList* list) {
	printf("Size: %d\n", list->size);
	for (int i = 0; i<list->size; i++) {
		printf("%d, ", (int)list->elements[i]);
	}
	printf("\n");
}

int arrayListTest() {
	ArrayList* list = AL_new();
	AL_add(list, 5);
	if (!(list->size == 1 && list->elements[0] == 5)) {
		printf("Error with inserting 5\n");
		return 0;
	}
	AL_add(list, 6);
	if (!(list->size == 2 && list->elements[1] == 6)) {
		printf("Error with inserting 6\n");
		return 0;
	}
	int temp = (int)AL_remove(list, 0);
	if (!(list->size == 1 && list->elements[0] == 6 && temp == 5)) {
		printf("Error with removing 5, pulled %d\n", temp);
		return 0;
	}
	AL_put(list, 5, 0);
	AL_put(list, 4, 0);
	AL_put(list, 3, 0);
	AL_put(list, 2, 0);
	AL_put(list, 1, 0);
	if (!(list->size == 6 && list->elements[0] == 1 && list->elements[5] == 6)) {
		printf("Error with put\n");
		return 0;
	}
	if (AL_contains(list, 4) < 0) {
		printf("Error with contains\n");
		return 0;
	}
	list->initMaxSize = 2;
	AL_clear(list);
	if (list->size != 0 || list->maxSize != list->initMaxSize) {
		printf("Error with clear:: size: %d, maxSize: %d\n", list->size, list->maxSize);
		return 0;
	}
	AL_add(list, 1);
	AL_add(list, 2);
	if (list->size != 2) {
		printf("Error with add, resizing too early\n");
		return 0;
	}
	AL_add(list, 3);
	if (!(list->size == 3 && list->maxSize == 4)) {
		printf("Error with AL_resize_up:: size: %d, maxSize: %d\n", list->size, list->maxSize);
		return 0;
	}
	AL_free(list);
	return 1;
}
#endif

int main(void) {
#ifdef DEBUG
	if (diceTest() && arrayListTest())
		puts("Tests Done!");
	else
		return EXIT_FAILURE;
#endif


	desetup(runGame(setup()));
	return EXIT_SUCCESS;
}
