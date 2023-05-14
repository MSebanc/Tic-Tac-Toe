#include "Player.h"
#include "Board.h"
#include <iostream>
#include <sstream>


/*
REQUIRES: should not be used
EFFECT: default constructor, sets player to 0
MODIFIES: this
*/
Player::Player() {
	player = 0;
}

/*
REQUIRES: use this constructor instead of the default contructor
EFFECTS: constructs the player, frees already existing board and 
sets board to given board and player to given player
MODIFIES: this
*/
Player::Player(Board b, int p) {
	board.freeBoard();
	board = b;
	player = p;
}

/*
EFFECT: calls inputMove and places given move onto the board
MODIFIES: Board
*/
void Player::makeMove() {
	int location = inputMove();
	board.placeMove(player, location);
}

/*
EFFECT: processes user input for next move until the move is valid and returns location
MODIFIES: none
*/
int Player::inputMove() {
	int location = 0;
	std::string input;
	while (location < 1 || location > 9 || !board.isValidMove(location)) {
		printf("Player %d, here is the current board: \n", player);
		displayBoard();
		printf("Make your move based on the following location numbers: \n");
		displayGrid();
		printf("Enter Your Move Location: ");
		
		std::cin >> input;
		std::stringstream strm(input);
		strm >> location;

		printf("\n");
		if (location < 1 || location > 9 || !board.isValidMove(location)) printf("Invalid Location...\n");
	}
	return location;
}

/*
EFFECT: prints current board to console
MODIFIES: none
*/
void Player::displayBoard() {
	int** b = board.getBoard();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (b[i][j]) {
			case 1:
				printf("x");
				break;
			case 2:
				printf("o");
				break;
			default:
				printf(" ");
			}
			if (j < 2) printf("|");
		}
		printf("\n");
	}
}


/*
EFFECT: prints move index numbers to console
MODIFIES: none
*/
void Player::displayGrid() {
	int** b = board.getBoard();
	for(int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d", 3 * (j + 1) - i);
			if (j < 2) printf("|");
		}
		printf("\n");
	}
}

/*
EFFECT: prints winner message to console
MODIFIES: this
*/
void Player::displayWinner(){
	displayBoard();
	printf("Congratulations Player %d, you win!!!\n", player);
}

