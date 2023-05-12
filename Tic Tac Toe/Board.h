#pragma once
#include <utility>

/*
Represents the game board in Tic Tac Toe
*/
class Board {
private:
	int** board;

	void initBoard();
	int checkWin(int pos1, int pos2, int pos3, int b[10]);
	std::pair<int, int> findIndex(int location);

public:
	Board();
	void placeMove(int player, int location);
	bool isValidMove(int location);
	int findWinner();
	void freeBoard();
	int** getBoard();
	int* getCondencedBoard();
};