#include "Computer.h"
#include "Player.h"
#include <iostream>

Computer::Computer(Board b) {
	board = b;
	player = 2;
}

void Computer::makeMove() {
	int location = randomMove();
	board.placeMove(player, location);
}

int Computer::randomMove() {
	int location = 0;
	while (location < 1 || location > 9 || !board.isValidMove(location)) {
		location = 1 + (rand() % 9);
	}
	return location;
}

void Computer::displayWinner() {
	displayBoard();
	printf("Uh oh, the computer won!!!\n");
}
