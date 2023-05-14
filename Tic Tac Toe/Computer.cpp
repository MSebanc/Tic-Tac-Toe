#include "Computer.h"
#include "Player.h"
#include<cstdlib>
#include <iostream>

/*
EFFECT: constructs the computer by freeing existing board and setting board to given board and 
player to 2. Also sets the random seed to current time to maintain randomness in every playthrough
MODIFIES: this
*/
Computer::Computer(Board b) {
	board.freeBoard();
	board = b;
	player = 2;
	srand((unsigned)time(NULL));
}

/*
EFFECT: calls randomMove and calls placeMove with returned location
MODIFIES: this
*/
void Computer::makeMove() {
	int location = randomMove();
	board.placeMove(player, location);
}

/*
EFFECT: finds a random number from 1 to 9 until the move is valid, then returns the move location
MODIFIES: none
*/
int Computer::randomMove() {
	int location = 0;
	while (location < 1 || location > 9 || !board.isValidMove(location)) {
		location = 1 + (rand() % 9);
	}
	return location;
}

/*
EFFECT: prints losing message to console
MODIFIES: none
*/
void Computer::displayWinner() {
	displayBoard();
	printf("Uh oh, the computer won!!!\n");
}
