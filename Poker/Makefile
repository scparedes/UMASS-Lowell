#########################################################
## Programmer Santiago Paredes                         ##
##                                                     ##
## Project 1: (Makefile)                               ##
##                                                     ##
## Approximate Completion Time: 10 minutes             ##
#########################################################


CPP		= g++
CPP_FLAGS	= -g -Wall -c

all: poker

Card.o: Card.cc Card.h
	$(CPP) $(CPP_FLAGS) Card.cc

DeckOfCards.o: DeckOfCards.cc DeckOfCards.h Card.h
	$(CPP) $(CPP_FLAGS) DeckOfCards.cc

Hand.o: Hand.cc Card.h Hand.h
	$(CPP) $(CPP_FLAGS) Hand.cc

Player.o: Player.cc Card.h Hand.h Player.h
	$(CPP) $(CPP_FLAGS) Player.cc

poker.o: poker.cc Card.h DeckOfCards.h Player.h
	$(CPP) $(CPP_FLAGS) poker.cc

poker: poker.o Card.o DeckOfCards.o Hand.o Player.o
	$(CPP) -o poker poker.o DeckOfCards.o Card.o Hand.o Player.o

clean:
	-rm *~
	-rm *.o
	-rm *#