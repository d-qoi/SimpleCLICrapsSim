CC=gcc
CFLAGS=-Wall

all: crapsSim

rm:
	rm *.o crapSims *.h.ghc

crapsSim: crapsSim.c ArrayList.o dice.o table.o commonFunctions.o bets.o
	$(CC) $(CFLAGS) -o $@ $?

ArrayList.o: ArrayList.c ArrayList.h
	$(CC) $(CFLAGS) -c $<
	
dice.o: dice.c dice.h
	$(CC) $(CFLAGS) -c $<
	
table.o: table.c ArrayList.h bets.h commonFunctions.h table.h players.h dice.h
	$(CC) $(CFLAGS) -c $<

commonFunctions.o: commonFunctions.c commonFunctions.h
	$(CC) $(CFLAGS) -c $<
	
bets.o: bets.c ArrayList.h bets.h commonFunctions.h players.h dice.h
	$(CC) $(CFLAGS) -c $<
	
.PHONY: all rm
