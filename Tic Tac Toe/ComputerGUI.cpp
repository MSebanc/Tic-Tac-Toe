#include "ComputerGUI.h"
#include "PlayerGUI.h"
#include "Board.h"
#include "ComputerMoves.h"
#include<iostream>
#include<cstdlib>
#include <SFML/Graphics.hpp>

/*
EFFECT: constructs the computer, frees already existing board and sets board to given board,
window to given window, grid to given game grid, gridTextures to given textures, 
difficulty to given difficulty, path to player2 image, sets player to 2;
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
	ComputerMoves::scoreStruct bestMove = moves.minimax(b, player);
	delete b;
	placeMove(bestMove.index);
}

/*
EFFECT: calls randomMove and calls placeMove with returned location
MODIFIES: this
*/
void ComputerGUI::makeMoveRandom() {
	int location = moves.randomMove(board);
	placeMove(location);
}

/*
EFFECT: sets text string to winning message and displays on the window
MODIFIES: this, sf::RenderWindow
*/
void ComputerGUI::drawWin(sf::Text text) {
	text.setString("Uh Oh, You Lost...");
	window->draw(text);
}