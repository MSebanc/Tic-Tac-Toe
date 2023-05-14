#include "Computer.h"
#include "Player.h"
#include<cstdlib>
#include <iostream>

/*
EFFECT: constructs the computer by freeing existing board and setting board to given board and 
player to 2.
MODIFIES: this
*/
Computer::Computer(Board b) {
	board.freeBoard();
	board = b;
	player = 2;
}

/*
EFFECT: calls randomMove and calls placeMove with returned location
MODIFIES: this
*/
void Computer::makeMove() {
	int location = moves.randomMove(board);
	board.placeMove(player, location);
}

/*
EFFECT: prints losing message to console
MODIFIES: none
*/
void Computer::displayWinner() {
	displayBoard();
	printf("Uh oh, the computer won!!!\n");
}
