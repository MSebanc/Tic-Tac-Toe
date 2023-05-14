#pragma once
#include "Board.h"

/*
Represents a player in Tic Tac Toe
*/
class Player {
protected: 
	Board board;
	int player;
private:
	void displayGrid();
	int inputMove();

public:
	Player(Board b, int p);
	Player();

	void displayBoard();
	virtual void makeMove();
	virtual void displayWinner();
};