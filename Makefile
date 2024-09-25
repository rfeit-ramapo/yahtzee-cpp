# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
yahtzee: yahtzee.o Strategy.o
    $(CC) $(CFLAGS) -o yahtzee yahtzee.o Strategy.o
 
# The main.o target can be written more simply
 
yahtzee.o: yahtzee.cpp Tournament.h StrategyEngine.h
    $(CC) $(CFLAGS) -c yahtzee.cpp
 
Strategy.o: Strategy.h Dice.h Scorecard.h
	$(CC) $(CFLAGS) -c Strategy.cpp