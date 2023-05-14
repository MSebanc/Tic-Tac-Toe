#include "TicTacToeGame.h"
#include <iostream>
#include <algorithm>
#include <sstream>

/*
EFFECT: Constructor, starts the game by calling runGame();
MODIFIES: this
*/
TicTacToeGame::TicTacToeGame() {
	runGame();
}

/*
EFFECT: display main menu and processes user input
MODIFIES: this
*/
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

/*
EFFECT: prints main menu to console
MODIFIES: none
*/
void TicTacToeGame::displayMainMenu() {
	printf("\nSelect From:\n");
	printf("\tr -> Rules\n");
	printf("\ts -> Start Game!\n");
	printf("\tq -> Quit\n");
	printf("Enter: ");
}

/*
EFFECT: processes user input for main menu
MODIFIES: this
*/
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

/*
EFFECT: prints rules to console
MODIFIES: none
*/
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


/*
EFFECT: runs the tic tac toe gameplay with fresh board
MODIFIES: this
*/
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

/*
EFFECT: processes user input for number of players
MODIFIES: this
*/
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

/*
EFFECT: creates new players and creates a computer player for player2 if playerCount is 1
MODIFIES: this
*/
void TicTacToeGame::initPlayers() {
	player1 = new Player(board, 1);
	if (playerCount == 1) {
		player2 = new Computer(board);
	}
	else {
		player2 = new Player(board, 2);
	}
}

/*
EFFECT: calls makeMove for players until 5 rounds for a draw or a player wins
MODIFIES: this, Board
*/
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

/*
EFFECT: calls displayWinner for given winner or prints draw message given winner is 0
MODIFIES: none
*/
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