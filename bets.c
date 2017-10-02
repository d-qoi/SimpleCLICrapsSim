/*
 * bets.c
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#include "bets.h"
#include "commonFunctions.h"
#include "players.h"
#include "ArrayList.h"
#include "dice.h"

#include <stdlib.h>
#include <stdio.h>

void placeBets(player* active, ArrayList* betList) {
	printf("\n\n=============== Place Your Bet! ==============\n\n");
	int state = 0;
	int loop = 1;
	int choice;
	bet* newBet;
	newBet = malloc(sizeof(bet));
	newBet->player = active;
	do {
		switch(state) { // left functions in state machine this time. Could be pulled out, I didn't want to.
			case 0: //which type?
				printf("What type of bet would you like to place?\n");
				printf("Line bet:1\tMulti-Roll:2\tSingle-Roll:3\n--> ");
				choice = getChoice();
				if (choice >= 1 && choice <= 3)
					state = choice;
				else
					state = -1;
				break;
			case 1: //Line choice
				printf("What Line Bet would you like to make?\n");
				printf("Come:1\tDon't Come:2\tPass:3\tDon't Pass:4\n--> ");
				choice = getChoice();
				if (choice >= 1 && choice <= 4) {
					newBet->type = choice; // see header for definitions.
					state = 4; //setting amount;
				} else {
					state = 0;
				}
				break;
			case 2: //Multi-roll choice
				printf("What Multi-Roll Bet would you like to make?\n");
				printf("Place:1\tBuy:2\tLay:3\tHard Way:5\tBig6/8: 6\n--> ");
				choice = getChoice();
				if (choice >= 1 && choice <= 3) {
					newBet->type = choice + 4; // see header for definitions, place is 5=4+1;
					state = 8; //by place lay;
				} else if (choice == 5 || choice == 6){
					state = choice; // chose states specifically for this.
				} else {
					state = 0;
				}
				break;
			case 3: //Single-roll bet
				printf("What Single-Roll Bet would you like to make?\n");
				printf("Aces:1\tAce-Deuce:2\tYo:3\tBoxCars:4\tHi-Lo:5\tAny Craps:6\tAny Seven:7\tField:8\n--> ");
				choice = getChoice();
				if (choice >= 1 && choice <= 7) {
					newBet->type = choice + 11; // see header for definitions, place is 12=11+1;
					state = 4; //setting amount;
				} else if (choice == 8){
					state = 7; // Field Choices are state 7.
				} else {
					state = 0;
				}
				break;
			case 4: //Amounts
				printf("How much would you like to bet? (Zero/Blank to cancel)\n--> ");
				newBet->amount = getLongLong();
				if (newBet->amount < 0) {
					printf("Please enter a valid amount, or zero to cancel the bet.");
					break;
				}
				switch(newBet->type) { //determining if free odds can be placed.
				case PASS:
				case COME:
				case DONT_PASS:
				case DONT_COME:
					printf("Would you like to bet free odds? (amount or zero)\n-->");
					newBet->free_odds = getLongLong();
					if (newBet->free_odds < 0) {
						printf("Please enter a valid amount, or zero to cancel the bet.");
						break;
					}
				}
				if (newBet->amount + newBet->free_odds <= active->ballance) {
					AL_add(betList, newBet);
					printf("Your bet has been recorded.");
					printf("%d %d %lld %lld %d %s", newBet->type, newBet->specifics, newBet->amount, newBet->free_odds, newBet->working, newBet->player->name);
					newBet = 0;
					state = -1;
					break;
				} else {
					printf("Please choose an amount that you can actually pay.");
					break;
				}
			case 5: //Hard Way Choice
				printf("Which Hard Way choice would you like to make?\n");
				printf("2, 4, 6, 8, 10, 12 (2 and 12 are also BoxCars and Aces from the previous menu.\n -->");
				choice = getChoice();
				if (choice > 1 && choice%2 == 0 && choice <= 12) {
					newBet->type = HARD_WAY;
					newBet->specifics = choice;
					if (choice == 2)
						newBet->type = ACES;
					else if (choice == 12)
						newBet->type = BOXCARS;
					state = 4;
				} else {
					state = 3;
				}
				break;
			case 6: //Big6/8 Choice
				printf("Which Big Choice would you like to make?\n");
				printf("6 or 8\n->");
				choice = getChoice();
				if (choice == 6) {
					newBet->type = BIG6;
					state = 4;
				}
				else if(choice == 8) {
					newBet->type = BIG8;
					state = 4;
				}
				else
					state = 3;
				break;
			case 7: //Field Choices
				printf("Which Field Choice would you like to make?\n");
				printf("2, 3, 4, 9, 10, 11, 12");
				choice = getChoice();
				switch (choice) { // best way to do this?
					case 2:
					case 3:
					case 4:
					case 9:
					case 10:
					case 11:
					case 12:
						newBet->type = FIELD;
						newBet->specifics = choice;
						state = 4;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case 8: //Buy, Place, Lay choices
				printf("Which number? (Any other to return to betting menu)\n");
				printf("4, 5, 6, 8, 9, 10\n--> ");
				choice = getChoice();
				switch(choice) {
				case 4:
				case 5:
				case 6:
				case 8:
				case 9:
				case 10:
					newBet->specifics = choice;
					state = 4;
					break;
				default:
					state = 3;
				}
				break;

			default:
				if (newBet) {
					free(newBet);
				}
				loop = 0;
		}
		printf("\n\n=============================\n\n");
	} while(loop);
}

void removeBets(player* active, ArrayList* betList) {
	return;
}

void viewBets(player* curPlayer, ArrayList* betList) {
	return;
}

void checkBets(ArrayList* betList, roll* curRoll, int point, int state) {
	bet* cur;
	for (int i = 0; i<AL_size(betList); i++) {
		cur = AL_get(betList, i);
		switch(cur->type) {
		case COME:
		case PASS:
			if ((state == POINT && curRoll->value == point) || (state == COMEOUT && curRoll->natural)) {
				cur->player->ballance += cur->amount;
				if (state == POINT) {
					switch (curRoll->value) {
					case 4:
					case 10:
						cur->player->ballance += 2*cur->free_odds;
						break;
					case 5:
					case 9:
						cur->player->ballance += 3*(cur->free_odds/2);
						break;
					case 6:
					case 8:
						cur->player->ballance += 6*(cur->free_odds/5);
						break;
					}
				}
				if (cur->type == COME) {
					cur->player->ballance += cur->amount + cur->free_odds;
					free(AL_remove(betList, i--));
				}
			} else if ((state == COMEOUT && curRoll->crap) || (state == POINT && curRoll->seven)) {
				cur->player->ballance += cur->free_odds;
				free(AL_remove(betList, i--));
			}
			break;
		case DONT_COME:
		case DONT_PASS:
			if ((state == POINT && curRoll->seven) || (state == COMEOUT && curRoll->crap && curRoll->value != 12)) {
				cur->player->ballance += cur->amount;
				if (state == POINT) {
					switch(point) {
					case 4:
					case 10:
						cur->player->ballance += cur->free_odds/2;
						break;
					case 5:
					case 9:
						cur->player->ballance += 2*(cur->free_odds/3);
						break;
					case 6:
					case 8:
						cur->player->ballance += 5*(cur->free_odds/6);
						break;
					}
				}
				if (cur->type == COME) {
					cur->player->ballance += cur->amount + cur->free_odds;
					free(AL_remove(betList, i--));
				}
			} else if ((state == COMEOUT && curRoll->crap) || (state == POINT && curRoll->seven)) {
				cur->player->ballance += cur->free_odds;
				free(AL_remove(betList, i--));
			}
			break;
		case PLACE:
		case BUY:
		case LAY:
		case HARD_WAY:
		case BIG6:
		case BIG8:
		case ACES:
		case ACEDEUCE:
		case YO:
		case BOXCARS:
		case HILO:
		case ANY_CRAPS:
		case ANY_SEVEN:
		case FIELD:
		default:
			break;
		}
	}
}

void toggleWorking(ArrayList* betList) {
	return;
}

void setWorking(bet* theBet) {
	theBet->working = TRUE;
}
