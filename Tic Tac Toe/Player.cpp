#include "Player.h"
#include "Board.h"
#include <iostream>
#include <sstream>

Player::Player() {
	player = 0;
}

Player::Player(Board b, int p) {
	board.freeBoard();
	board = b;
	player = p;
}

void Player::makeMove() {
	int location = inputMove();
	board.placeMove(player, location);
}

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

void Player::displayWinner(){
	displayBoard();
	printf("Congratulations Player %d, you win!!!\n", player);
}

