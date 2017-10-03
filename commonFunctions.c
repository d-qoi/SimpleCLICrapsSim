/*
 * commonFunctions.c
 *
 *  Created on: July 24th, 2017
 *      Author: hirschag
 */

#include "commonFunctions.h"


#include <stdio.h>

int getChoice() {
	char buffer[5];
	int chosen = 0;
	fgets(buffer, sizeof(buffer), stdin);
	sscanf(buffer, "%d", &chosen);
	printf("\n\n *** \n\n");
	return chosen;
}

long long getLongLong() {
	char buffer[20];
	long long chosen = 0;
	fgets(buffer, sizeof(buffer), stdin);
	sscanf(buffer, "%lld", &chosen);
	printf("\n\n *** \n\n");
	return chosen;
}
