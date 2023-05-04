#include "Player.h"
#include "Computer.h"

class Board {
private:
	int **board;
	int playerCount;
	Player player1;
	Player player2;

	/*
	EFFECT: Initializes both players or creates a computer player if there is only 1 player. 
	MODIFIES: this
	*/
	void initPlayers() {
		player1 = Player();
		if (playerCount == 1) {
			player2 = Computer();
		}
		else {
			player2 = Player();
		}
	}

	/*
	EFFECT: allocates space in memory for the board
	MODIFIES: this
	*/
	void initBoard() {
		board = new int* [3];
		for (int i = 0; i < 3; i++) {
			board[i] = new int[3];
		}
	}

	/*
	REQUIRES: pos1, pos2, pos3 all valid index in given array
	EFFECT: checks for a win by comparing the value at all 3 positions in given board
	MODIFIES: none
	*/
	int checkWin(int pos1, int pos2, int pos3, int b[9]) {
		if (b[pos1] == b[pos2] && b[pos1] == b[pos3])
			return b[pos1];
		return 0;
	}

public:
	/*
	EFFECTS: constructs the Board with given number of players, if player count if > 2 or < 1,
		it corrects to nearest player count
	MODIFIES: this
	*/
	Board(int players) {
		playerCount = players;
		if (playerCount > 2) playerCount = 2;
		if (playerCount < 1) playerCount = 1;
		initPlayers();
		initBoard();
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
	void placeMove(int player, int location) {
		board[location % 3][location / 3] = player;
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
	bool isValidMove(int location) {
		return board[location % 3][location / 3] == 0;
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
	int findWinner() {
		int boardCondenced[10];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				boardCondenced[3 * (j + 1) - i - 1] = board[i][j];
			}
		}
		int winningPlayer = 0;
		winningPlayer = checkWin(3, 6, 9, boardCondenced);
		if (winningPlayer) return winningPlayer;
		checkWin(2, 5, 8, boardCondenced);
		if (winningPlayer) return winningPlayer;
		checkWin(1, 4, 7, boardCondenced);
		if (winningPlayer) return winningPlayer;
		checkWin(3, 2, 1, boardCondenced);
		if (winningPlayer) return winningPlayer;
		checkWin(6, 5, 4, boardCondenced);
		if (winningPlayer) return winningPlayer;
		checkWin(9, 8, 7, boardCondenced);
		if (winningPlayer) return winningPlayer;
		checkWin(3, 5, 7, boardCondenced);
		if (winningPlayer) return winningPlayer;
		checkWin(9, 5, 1, boardCondenced);
		return winningPlayer;
	}

	/*
	EFFECT: frees up board's location in memory
	MODIFIES: this
	*/
	void freeBoard() {
		for (int i = 0; i < 3; i++) {
			delete board[i];
		}
		delete board;
	}
	
	// getters
	int** getBoard() {
		return board;
	}

	Player getPlayer(int num) {
		if (num == 1) {
			return player1;
		}
		return player2;
	}
};

