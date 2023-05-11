#include "ComputerGUI.h"
#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include<cstdlib>
#include <SFML/Graphics.hpp>

ComputerGUI::ComputerGUI(Board b, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t) {
	board = b;
	window = w;
	grid = s;
	player = 2;
	path = "oImage.png";
	gridTextures = t;
	srand((unsigned) time(NULL));
}

bool ComputerGUI::makeMove(sf::Vector2i pos) {
	int location = randomMove();
	placeMove(location);
	return true;
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