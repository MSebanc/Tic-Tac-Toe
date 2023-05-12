#include "ComputerGUI.h"
#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include<cstdlib>
#include <SFML/Graphics.hpp>

ComputerGUI::ComputerGUI(Board b, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t, int d) {
	board = b;
	window = w;
	grid = s;
	player = 2;
	difficulty = d;
	path = "oImage.png";
	gridTextures = t;
	srand((unsigned) time(NULL));
}

bool ComputerGUI::makeMove(sf::Vector2i pos) {
	if (!difficulty) makeMoveRandom();
	else makeMoveMinimax();
	return true;
}

void ComputerGUI::makeMoveMinimax() {
	int* b = board.getCondencedBoard();
	scoreStruct bestMove = minimax(b, player);
	free(b);
	printf("%d\n", bestMove.score);
	printf("%d\n\n", bestMove.index);
	placeMove(bestMove.index);
}

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

bool ComputerGUI::noMoreMoves(int *b) {
	for (int i = 1; i < 10; i++) {
		if (!b[i]) return false;
	}
	return true;
}

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

void ComputerGUI::makeMoveRandom() {
	int location = randomMove();
	placeMove(location);
}

int ComputerGUI::randomMove() {
	int location = 0;
	while (location < 1 || location > 9 || !board.isValidMove(location)) {
		location = 1 + (rand() % 9);
	}
	return location;
}

void ComputerGUI::drawWin(sf::Text text) {
	text.setString("Uh Oh, You Lost...");
	window->draw(text);
}