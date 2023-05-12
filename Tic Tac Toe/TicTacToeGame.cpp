#include "TicTacToeGame.h"
#include <iostream>
#include <algorithm>
#include <sstream>

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
		printf("\n");
		if (!command.compare("q")) {
			keepGoing = false;
		}
		else {
			processMainMenu(command);
		}
	}
	board.freeBoard();
	printf("Goodbye!\n");
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
		printf("Selection is not valid...\n");
	}
}

void TicTacToeGame::displayRules() {
	printf("\nThe object of Tic Tac Toe is to get three in a row. ");
	printf("You play on a three by three game board.\n");
	printf("The first player is known as X and the second is O. ");
	printf("Players alternate placing Xs and Os on the game board\n");
	printf("until either oppent has three in a row or all nine squares ");
	printf("are filled. X always goes first, and in the event that no\n");
	printf("one has three in a row, the stalemate is a draw.\n");

	printf("Enter C To Continue: ");
	std::string enter;
	std::cin >> enter;
	printf("\n");
}

void TicTacToeGame::startPlaying() {
	board.freeBoard();
	board = Board();
	playerSelection();
	initPlayers();
	rounds();
	displayResults(board.findWinner());
	delete player1;
	delete player2;
}

void TicTacToeGame::playerSelection() {
	int count = 0;
	std::string input;
	while (count != 1 && count != 2) {
		printf("Enter Player Count (1 or 2): ");
		std::cin >> input;
		std::stringstream strm(input);
		strm >> count;
		printf("\n");
		if (count != 1 && count != 2) printf("Invalid Player Count...\n");\
	}
	playerCount = count;
}

void TicTacToeGame::initPlayers() {
	player1 = new Player(board, 1);
	if (playerCount == 1) {
		player2 = new Computer(board);
	}
	else {
		player2 = new Player(board, 2);
	}
}

void TicTacToeGame::rounds() {
	round = 1;
	while (!board.findWinner() && round < 5) {
		player1->makeMove();
		if (board.findWinner()) break;
		player2->makeMove();
		round++;
	}
	if (!board.findWinner() && round == 5) {
		player1->makeMove();
	}
}

void TicTacToeGame::displayResults(int winner) {
	if (!winner) {
		player1->displayBoard();
		printf("It's a draw!!!\n");
	}
	else if (winner == 1) {
		player1->displayWinner();
	}
	else {
		player2->displayWinner();
	}
	printf("\nEnter R to return to Main Menu: ");
	std::string enter;
	std::cin >> enter;
	printf("\n");
}