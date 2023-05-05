#include "Player.h"
#pragma once
class Computer : public Player {
private:

public:
	Computer(Board b);
	virtual void makeMove();
	virtual void displayWinner();
};