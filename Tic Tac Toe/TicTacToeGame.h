#pragma once
#include <iostream>

class TicTacToeGame {
private:
	void runGame();
	void displayMainMenu();
	void processMainMenu(std::string command);
	void displayRules();
	void startPlaying();

public:
	TicTacToeGame();
};