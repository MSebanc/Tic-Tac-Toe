#include "TicTacToeGame.h"
#include <iostream>
#include <algorithm>

TicTacToeGame::TicTacToeGame() {
	runGame();
}

void TicTacToeGame::runGame() {
	bool keepGoing = true;
	printf("Hello and Welcome to Tic Tac Toe!\n");
	while (keepGoing) {
		displayMainMenu();
		std::string command;
		std::cin >> command;
		transform(command.begin(), command.end(), command.begin(), ::tolower);
		if (!command.compare("q")) {
			keepGoing = false;
		}
		else {
			processMainMenu(command);
		}
	}
}

void TicTacToeGame::displayMainMenu() {
	printf("\nSelect From:\n");
	printf("\tr -> Rules\n");
	printf("\ts -> Start Game!\n");
	printf("\tq -> Quit\n");
	printf("Enter: ");
}

void TicTacToeGame::processMainMenu(std::string command) {
	if (!command.compare("r")) {
		displayRules();
	}
	else if (!command.compare("s")) {
		startPlaying();
	}
	else {
		printf("\nSelection is not valid...\n");
	}
}

void TicTacToeGame::displayRules() {
	printf("\nThe object of Tic Tac Toe is to get three in a row. ");
	printf("You play on a three by three game board.\n");
	printf("The first player is known as X and the second is O. ");
	printf("Players alternate placing Xs and Os on the game board\n");
	printf("until either oppent has three in a row or all nine squares ");
	printf("are filled. X always goes first, and in the event that no\n");
	printf("one has three in a row, the stalemate is called a cat game.\n");

	printf("Enter C To Continue: ");
	std::string enter;
	std::cin >> enter;
}

void TicTacToeGame::startPlaying() {
	printf("\nStarting Playing\n");
}
