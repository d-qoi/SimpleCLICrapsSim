/*
 * dice.h
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#ifndef DICE_H_
#define DICE_H_

#define TRUE 1
#define FALSE 0

typedef struct roll_struct {
	int dice_1;
	int dice_2;
	int value;
	char hard;
	char crap;
	char seven;
	char natural;
} roll;

roll *newRoll();
void checkRoll(roll*);

#endif /* DICE_H_ */
