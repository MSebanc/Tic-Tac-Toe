#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include <SFML/Graphics.hpp>

PlayerGUI::PlayerGUI() {
    window = NULL;
    grid = NULL;
    gridTextures = NULL;
}

PlayerGUI::PlayerGUI(Board b, int p, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t) {
	board = b;
	player = p;
	if (player == 1) path = "xImage.png";
	else path = "oImage.png";
    window = w;
    grid = s;
    gridTextures = t;
}

bool PlayerGUI::makeMove(sf::Vector2i pos) {
    for (int i = 1; i < 10; i++) {
        if (grid[i].getGlobalBounds().contains(window->mapPixelToCoords(pos))) {
            if (board.isValidMove(i)) {
                placeMove(i);
                return true;
            }
            break;
        }
    }
    return false;
}

void PlayerGUI::placeMove(int location) {
    if (!gridTextures[location].loadFromFile(path)) {
        printf("Error\n");
    }
    board.placeMove(player, location);
    grid[location].setTexture(&gridTextures[location]);
}

void PlayerGUI::drawWin(sf::Text text) {
    text.setString("Congrats Player " + std::to_string(player) + "!");
    window->draw(text);
}