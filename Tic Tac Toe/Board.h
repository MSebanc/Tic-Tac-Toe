#pragma once
#include <utility>

/*
Represents the game board in Tic Tac Toe
*/
class Board {
private:
	int** board;
	int playerCount;

	void initBoard();
	int checkWin(int pos1, int pos2, int pos3, int b[9]);
	std::pair<int, int> findIndex(int location);

public:
	Board(int players);
	void placeMove(int player, int location);
	bool isValidMove(int location);
	int findWinner();
	void freeBoard();
	int** getBoard();
};