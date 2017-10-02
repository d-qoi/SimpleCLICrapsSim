/*
 * dice.c
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#include "dice.h"

#include <stdlib.h>

roll* newRoll() {
	roll* res = 0;

	res = (roll*)malloc(sizeof(roll));

	res->dice_1 = rand()%6 + 1;
	res->dice_2 = rand()%6 + 1;

	checkRoll(res);

	return res;
}

void checkRoll(roll* roll) {
	int temp = 0;
	temp = roll->dice_1 + roll->dice_2;
	roll->value = temp;
	roll->hard = FALSE;
	roll->crap = FALSE;
	roll->seven = FALSE;
	roll->natural = FALSE;



	switch (temp) {
		case 2:
		case 3:
		case 12:
			roll->crap = TRUE;
			break;
		case 7:
			roll->seven = TRUE; // need to set crap to false, no break
		case 11:
			roll->natural = TRUE;
			break;
	}

	if (roll->dice_1 == roll->dice_2)
		roll->hard = TRUE;
	else
		roll->hard = FALSE;
}
