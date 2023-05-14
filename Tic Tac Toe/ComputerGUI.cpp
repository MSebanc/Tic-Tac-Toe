#include "ComputerGUI.h"
#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include<cstdlib>
#include <SFML/Graphics.hpp>

/*
EFFECT: constructs the computer, frees already existing board and sets board to given board,
window to given window, grid to given game grid, gridTextures to given textures, 
difficulty to given difficulty, path to player2 image and sets player to 2. Also sets 
the random seed to current time to maintain randomness in every playthrough
MODIFIES: this
*/
ComputerGUI::ComputerGUI(Board b, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t, int d) {
	board.freeBoard();
	board = b;
	window = w;
	grid = s;
	player = 2;
	difficulty = d;
	path = "oImage.png";
	gridTextures = t;
	srand((unsigned) time(NULL));
}

/*
EFFECT: delays move by 0.5 seconds to feel more natural to players and calls makeMoveRandom
if difficulty is 0, calls makeMoveMinimax otherwise. Returns true
MODIFIES: none
*/
bool ComputerGUI::makeMove(sf::Vector2i pos) {
	delay.restart();
	while (delay.getElapsedTime().asSeconds() < wait);
	if (!difficulty) makeMoveRandom();
	else makeMoveMinimax();
	return true;
}

/* 
EFFECT: runs the minimax algorithm with the condencedBoard and places found best move
MODIFIES: this
*/
void ComputerGUI::makeMoveMinimax() {
	int* b = board.getCondencedBoard();
	scoreStruct bestMove = minimax(b, player);
	delete b;
	placeMove(bestMove.index);
}

/*
REQUIRES: given array is length 10
EFFECT: returns true if any of the possible winning rows, columns and diagonals 
are equal to given player, false otherwise
MODIFIES: none
*/
bool ComputerGUI::findWinner(int *b, int p) {
	if ((b[3] == b[6] && b[3] == b[9] && b[3] == p) ||
		(b[2] == b[5] && b[2] == b[8] && b[2] == p) ||
		(b[1] == b[4] && b[1] == b[7] && b[1] == p) ||
		(b[3] == b[2] && b[3] == b[1] && b[3] == p) ||
		(b[6] == b[5] && b[6] == b[4] && b[6] == p) ||
		(b[9] == b[8] && b[9] == b[7] && b[9] == p) ||
		(b[3] == b[5] && b[3] == b[7] && b[3] == p) ||
		(b[9] == b[5] && b[9] == b[1] && b[9] == p)) {
		return true;
	}
		
	return false;
}

/*
* REQUIRES: given array is length 10
EFFECT: returns true if all locations are occupied, false otherwise
*/
bool ComputerGUI::noMoreMoves(int *b) {
	for (int i = 1; i < 10; i++) {
		if (!b[i]) return false;
	}
	return true;
}
/*
REQUIRES: given array is length 10
EFFECT: runs recursive minimax algorithm. 
See https://en.wikipedia.org/wiki/Minimax for info on the algorithm
MODIFIES: none
*/
ComputerGUI::scoreStruct ComputerGUI::minimax(int *b, int p) {
	if (findWinner(b, 1)) {
		scoreStruct score;
		score.score = -10;
		score.index = 0;
		return score;
	}
	else if (findWinner(b, 2)) {
		scoreStruct score;
		score.score = 10;
		score.index = 0;
		return score;
	}
	else if (noMoreMoves(b)) {
		scoreStruct score;
		score.score = 0;
		score.index = 0;
		return score;
	}

	scoreStruct scores[10];
	for (int i = 0; i < 10; i++) {
		scores[i].score = 0;
		scores[i].index = i;
	}

	for (int i = 1; i < 10; i++) {
		if (!b[i]) {
			b[i] = p;
			if (p == 2) {
				scores[i].score = minimax(b, 1).score;
				scores[i].index = i;
			}
			else {
				scores[i].score = minimax(b, 2).score;
				scores[i].index = i;
			}
			b[i] = 0;
		}
	}
	
	int bestMove;
	if (p == 2) {
		int bestScore = -10000;
		for (int i = 1; i < 10; i++) {
			if (!b[i]) {
				if (scores[i].score > bestScore) {
					bestScore = scores[i].score;
					bestMove = i;
				}
			}
		}
	}
	else {
		int bestScore = 10000;
		for (int i = 1; i < 10; i++) {
			if (!b[i]) {
				if (scores[i].score < bestScore) {
					bestScore = scores[i].score;
					bestMove = i;
				}
			}
		}
	}
	scoreStruct bestStruct;
	bestStruct.score = scores[bestMove].score;
	bestStruct.index = bestMove;
	return bestStruct;
}

/*
EFFECT: calls randomMove and calls placeMove with returned location
MODIFIES: this
*/
void ComputerGUI::makeMoveRandom() {
	int location = randomMove();
	placeMove(location);
}

/*
EFFECT: finds a random number from 1 to 9 until the move is valid, then returns the move location
MODIFIES: none
*/
int ComputerGUI::randomMove() {
	int location = 0;
	while (location < 1 || location > 9 || !board.isValidMove(location)) {
		location = 1 + (rand() % 9);
	}
	return location;
}

/*
EFFECT: sets text string to winning message and displays on the window
MODIFIES: this, sf::RenderWindow
*/
void ComputerGUI::drawWin(sf::Text text) {
	text.setString("Uh Oh, You Lost...");
	window->draw(text);
}