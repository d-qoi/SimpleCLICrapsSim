/*
 * table.h
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#include "ArrayList.h"
#include "bets.h"
#include "dice.h"
#include "players.h"

#ifndef TABLE_H_
#define TABLE_H_

#define CHOOSE_PLAYER 0
#define CHOOSE_ACTION 1
#define PLACE_BET 2
#define TAKE_BET 3
#define SHOOT_DICE 4
#define CHECK_BETS 5

typedef struct table_struct {
	ArrayList* players;
	ArrayList* bets;
	player* currentPlayer;
	roll* currentRoll;
	int point;
} table;

table* setup();

void desetup(table*);

table* runGame(table*);

#endif /* TABLE_H_ */
