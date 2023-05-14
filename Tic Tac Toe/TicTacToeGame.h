#pragma once
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Computer.h"

/*
Represents the console based display of Tic Tac Toe
*/
class TicTacToeGame {
private:
	Board board;
	int playerCount;
	Player *player1;
	Player *player2;
	int round;

	void runGame();
	void displayMainMenu();
	void processMainMenu(std::string command);
	void displayRules();
	void startPlaying();
	void playerSelection();
	void initPlayers();
	void rounds();
	void displayResults(int winner);

public:
	TicTacToeGame();
};