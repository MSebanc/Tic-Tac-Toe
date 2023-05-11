#pragma once
#include "Player.h"
class Computer : public Player {
private:
	int randomMove();
public:
	Computer(Board b);
	void makeMove();
	void displayWinner();
};