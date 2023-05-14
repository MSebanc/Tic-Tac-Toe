#pragma once
#include "Player.h"
#include "ComputerMoves.h"

/*
Represents a computer player in Tic Tac Toe
*/
class Computer : public Player {
private:
	ComputerMoves moves;
public:
	Computer(Board b);
	void makeMove();
	void displayWinner();
};