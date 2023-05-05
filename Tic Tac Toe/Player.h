#pragma once
#include "Board.h"
class Player {
private:
	Board board;
	int player;
	void displayGrid();
	int inputMove();

public:
	Player(Board b, int p);
	Player();

	void displayBoard();
	void makeMove();
	void displayWinner();
};