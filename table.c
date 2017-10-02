/*
 * table.c
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#include "ArrayList.h"
#include "bets.h"
#include "commonFunctions.h"
#include "table.h"
#include "players.h"
#include "dice.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


table* setup() {
	table* Table;
	Table = (table*)malloc(sizeof(table));
	Table->bets = AL_new();
	Table->players = AL_new();
	Table->currentRoll = 0;

	player* tempPlayer;

	char* buffer;
	long long starting = 0;

	printf("Welcome!\n");
	do {
		printf("How many credits does each player start with? :: ");
		buffer = (char*)malloc(26*sizeof(char));
		fgets(buffer, 25, stdin);
		sscanf(buffer, "%lld", &starting);
	} while (starting < 1);


	printf("\nPlease enter the names for the players you want.\n");
	printf("Send an empty name to start the game.\n");

	int cont = 1;
	while(cont) {
		printf("--> ");
		buffer = malloc(256*sizeof(char));
		fgets(buffer, 256, stdin);
		if(buffer[0] == '\n') {
			cont = 0;
			continue;
		}
		tempPlayer = malloc(sizeof(player)); //should probably check this for failure.
		AL_add(Table->players, tempPlayer);
		tempPlayer->name = malloc(256*sizeof(char));
		tempPlayer->ballance = starting;
		sscanf(buffer, "%s", tempPlayer->name);
	}
	Table->currentPlayer = AL_get(Table->players, 0);
	Table->currentPlayer->state = COMEOUT;
	return Table;
}

void desetup(table* Table) {
	AL_free_free(Table->players);
	AL_free_free(Table->bets);
}

player* mainOptionMenu(table* Table) {
	printf("\n\n======================  Main Menu  ====================\n\n");

	if (Table->currentRoll)
		printf("Last Roll:: %d + %d, Point :: %d\n\n",
				Table->currentRoll->dice_1,
				Table->currentRoll->dice_2,
				Table->point);
	player* activePlayer;
	for (int i = 0; i<AL_size(Table->players); i++) {
		activePlayer = (player*)(AL_get(Table->players, i));
		printf("%s:%d\t", activePlayer->name, i+1);
	}
	printf("\n%s is the current shooter.\n", Table->currentPlayer->name);
	printf("Choose a player to take an action, send just 'x' to return to this menu.\n--> ");

	int chosen = getChoice();
	if (chosen <= AL_size(Table->players) && chosen > 0) { // <= size because everything is +1
		return AL_get(Table->players, chosen-1);
	}
	return 0;
}

int chooseAction(table* Table, player* active) {
	printf("\n\n============ Choose an Action ===============\n\n");
	char current = 0;
	if (active == Table->currentPlayer)
		current = 1;
	printf("Place bet:1\t Take down bet:2\t");
	if (current)
		printf("Shoot:3\n");
	printf("Any other character to return to main menu.\n-->");
	int choice = getChoice();
	if (choice == 1)
		return PLACE_BET;
	if (choice == 2)
		return TAKE_BET;
	if (choice == 3 && current)
		return SHOOT_DICE;

	return CHOOSE_PLAYER;
}


void updateCurrentPlayer(table* Table) {
	player* cur = Table->currentPlayer;
	player* next;
	roll* curRoll = Table->currentRoll;
	int playIndex = AL_contains(Table->players, cur);
	if (playIndex+1 >= AL_size(Table->players)) {
		next = AL_get(Table->players, 0);
	} else {
		next = AL_get(Table->players, playIndex+1);
	}

	switch(cur->state) {
	case COMEOUT:
		if (curRoll->crap) {
			printf("Crapped out!\nNext Shooter:: %s\n", next->name);
			Table->currentPlayer = next;
			cur->state = WAIT;
			next->state = COMEOUT;
		} else if (curRoll->natural){
			printf("Natural!\nNext Shooter:: %s\n", next->name);
			Table->currentPlayer = next;
			cur->state = WAIT;
			next->state = COMEOUT;
		} else {
			printf("New Point! %d\n", curRoll->value);
			cur->state = POINT;
			Table->point = curRoll->value;
		}
		break;
	case POINT:
		if (curRoll->seven) {
			printf("SEVEN! Better Luck Next Round! New Shooter:: %s\n", next->name);
			Table->currentPlayer = next;
			cur->state = WAIT;
			next->state = COMEOUT;
		} else if (curRoll->value == Table->point){
			printf("Congratulations! You've hit point! New Shooter:: %s\n", next->name);
			Table->currentPlayer = next;
			cur->state = WAIT;
			next->state = COMEOUT;
		} else {
			printf("Rolled %d, Keep Shooting for %d!", curRoll->value, Table->point);
		}
		break;
	case WAIT:
		printf("This should not have occured\n");
		break;
	}
}

table* runGame(table* Table) {

	int running = 1;
	player* activePlayer;
	roll* nextRoll;

	int state = CHOOSE_PLAYER;

	while(running) {
		switch (state) {
			case CHOOSE_PLAYER:
				activePlayer = mainOptionMenu(Table);
				if (activePlayer)
					state = CHOOSE_ACTION;
				else
					state = -1;
				break;

			case CHOOSE_ACTION:
				state = chooseAction(Table, activePlayer);
				break;

			case PLACE_BET:
				placeBets(activePlayer, Table->bets);
				state = 0;
				break;

			case TAKE_BET:
				removeBets(activePlayer, Table->bets);
				state = 0;
				break;

			case CHECK_BETS:
				viewBets(activePlayer, Table->bets);
				state = 0;
				break;

			case SHOOT_DICE:
				nextRoll = newRoll();
				Table->currentRoll = nextRoll;
				printf("Rolling!\n");
				printf("Rolled :: %d + %d\n", nextRoll->dice_1, nextRoll->dice_2);
				checkBets(Table->bets, Table->currentRoll, Table->point, Table->currentPlayer->state);
				updateCurrentPlayer(Table);
				state = 0;
				break;

			default:
				printf("Something went wrong\nIn state %d", state);
				running = 0;
				break;
		}
	}

	return Table;
}
