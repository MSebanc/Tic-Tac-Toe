#include <utility>
#include "Board.h"

/*
EFFECTS: constructs the Board with given number of players, if player count if > 2 or < 1,
it corrects to nearest player count
MODIFIES: this
*/
Board::Board() {
	initBoard();
}

/*
EFFECT: allocates space in memory for the board and sets all locations to 0
MODIFIES: this
*/
void Board::initBoard() {
	board = new int* [3];
	for (int i = 0; i < 3; i++) {
		board[i] = new int[3];
		for (int j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
}

/*
REQUIRES: pos1, pos2, pos3 all valid index in given array
EFFECT: checks for a win by comparing the value at all 3 positions in given board
MODIFIES: none
*/
int Board::checkWin(int pos1, int pos2, int pos3, int b[10]) {
	if (b[pos1] == b[pos2] && b[pos1] == b[pos3]) return b[pos1];
	return 0;
}


/*
REQUIRES: location from 1 to 9
EFFECTS: returns an std::pair<int,int> representing the two index of the 2d array board given 
location on the board based on the following location values:
3|6|9
2|5|8
1|4|7
MODIFIES: none
*/
std::pair<int, int> Board::findIndex(int location) {
	int index1 = location % 3;
	if (index1 == 1) {
		index1++;
	}
	else if (index1 == 2) {
		index1--;
	}
	int index2 = location / 3;
	if (location % 3 == 0) {
		index2--;
	}
	return std::make_pair(index1, index2);
}


/*
REQUIRES: player equal to 1 or 2 and location from 1 to 9
EFFECT: updates board with player number at the given location on the board based on the following 
location values:
3|6|9
2|5|8
1|4|7
MODIFIES: this
*/
void Board::placeMove(int player, int location) {
	std::pair<int, int> index = findIndex(location);
	board[index.first][index.second] = player;
}

/*
REQUIRES: location from 1 to 9
EFFECT: checks to see if no player has made a move (value is 0) at the given location on the board 
based on the following location values:
3|6|9
2|5|8
1|4|7
MODIFIES: none
*/
bool Board::isValidMove(int location) {
	std::pair<int, int> index = findIndex(location);
	return board[index.first][index.second] == 0;
}

/*
EFFECT: condences the 2d array into one array based on the following indices:
3|6|9
2|5|8
1|4|7
Then calls checkWin with each possible winning combination in tic tac toe (3 in a row) and returns the
winning player or 0 if a draw.
MODIFIES: none
*/
int Board::findWinner() {
	int boardCondenced[10];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			boardCondenced[3 * (j + 1) - i] = board[i][j];
		}
	}
	int winningPlayer = 0;
	winningPlayer = checkWin(3, 6, 9, boardCondenced);
	if (winningPlayer) return winningPlayer;
	winningPlayer = checkWin(2, 5, 8, boardCondenced);
	if (winningPlayer) return winningPlayer;
	winningPlayer = checkWin(1, 4, 7, boardCondenced);
	if (winningPlayer) return winningPlayer;
	winningPlayer = checkWin(3, 2, 1, boardCondenced);
	if (winningPlayer) return winningPlayer;
	winningPlayer = checkWin(6, 5, 4, boardCondenced);
	if (winningPlayer) return winningPlayer;
	winningPlayer = checkWin(9, 8, 7, boardCondenced);
	if (winningPlayer) return winningPlayer;
	winningPlayer = checkWin(3, 5, 7, boardCondenced);
	if (winningPlayer) return winningPlayer;
	winningPlayer = checkWin(9, 5, 1, boardCondenced);
	return winningPlayer;
}

/*
EFFECT: frees up board's location in memory
MODIFIES: this
*/
void Board::freeBoard() {
	for (int i = 0; i < 3; i++) {
		delete board[i];
	}
	delete board;
}
	
// getters

/*
EFFECT: returns 2d board array
MODIFIES: none
*/
int** Board::getBoard() {
	return board;
}

/*
EFFECT: returns 1d board array
MODIFIES: none
*/
int* Board::getCondencedBoard() {
	int* boardCondenced = new int[10];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			boardCondenced[3 * (j + 1) - i] = board[i][j];
		}
	}
	return boardCondenced;
}

