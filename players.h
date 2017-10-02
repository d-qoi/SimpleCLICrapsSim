/*
 * players.h
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#ifndef PLAYERS_H_
#define PLAYERS_H_

#define WAIT 0
#define COMEOUT 1
#define POINT 2

typedef struct player_struct {
	char* name;
	char state;
	long long ballance;
} player;

#endif /* PLAYERS_H_ */
