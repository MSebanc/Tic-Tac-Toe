#pragma once
#include "Board.h"

/*
Represents the different moves a computer can make
*/
class ComputerMoves {
private:
	bool noMoreMoves(int* b);
	bool findWinner(int* b, int p);
public:
	struct scoreStruct {
		int score;
		int index;
	};

	ComputerMoves();
	int randomMove(Board board);
	struct scoreStruct minimax(int* b, int p);
	
};