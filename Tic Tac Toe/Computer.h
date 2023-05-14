#pragma once
#include "Player.h"

/*
Represents a computer player in Tic Tac Toe
*/
class Computer : public Player {
private:
	int randomMove();
public:
	Computer(Board b);
	void makeMove();
	void displayWinner();
};