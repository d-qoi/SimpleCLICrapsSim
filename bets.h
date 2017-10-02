/*
 * bets.h
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#include "players.h"
#include "ArrayList.h"
#include "dice.h"

#ifndef BETS_H_
#define BETS_H_

#define TRUE 1
#define FALSE 0

#define COME 1
#define DONT_COME 2
#define PASS 3
#define DONT_PASS 4
#define PLACE 5
#define BUY 6
#define LAY 7
#define HARD_WAY 9
#define BIG6 10
#define BIG8 11
#define ACES 12
#define ACEDEUCE 13
#define YO 14
#define BOXCARS 15
#define HILO 16
#define ANY_CRAPS 17
#define ANY_SEVEN 18
#define FIELD 19


typedef struct bet_struct {
	int type;
	int specifics; // for field and hard way.
	long long amount;
	long long free_odds;
	int working;
	player* player;

} bet;

void placeBets(player*, ArrayList*);

void removeBets(player*, ArrayList*);

void viewBets(player*, ArrayList*);

void checkBets(ArrayList*, roll*, int, int);

void toggleWorking(ArrayList*);

void setWorking(bet*);

#endif /* BETS_H_ */
