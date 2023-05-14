#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include <SFML/Graphics.hpp>

/*
REQUIRES: should not be used
EFFECT: default constructor, sets player to 0, sets empty path string, and sets window, grid, 
and gridTextures to NULL
MODIFIES: this
*/
PlayerGUI::PlayerGUI() {
    player = 0;
    path = "";
    window = NULL;
    grid = NULL;
    gridTextures = NULL;
}

/*
REQUIRES: use this constructor instead of the default contructor
EFFECTS: constructs the player, frees already existing board and sets board to given board, 
player to given player, sets path to correct image based on given player number, sets 
window to given window, sets grid to given grid, and sets gridTextures to given textures
MODIFIES: this
*/
PlayerGUI::PlayerGUI(Board b, int p, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t) {
    board.freeBoard();
	board = b;
	player = p;
	if (player == 1) path = "xImage.png";
	else path = "oImage.png";
    window = w;
    grid = s;
    gridTextures = t;
}

/*
EFFECT: determines if given position vector is contained in the bounds of each grid location,
if it is, then it calls placeMove with the location value if the move is a valid move
returns true if move is placed, false otherwise
MODIFIES: this
*/
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

/*
REQUIRES: location is a valid move
EFFECT: sets texture of grid location to player's move and places move on the board
MODIFIES: this, Board
*/
void PlayerGUI::placeMove(int location) {
    if (!gridTextures[location].loadFromFile(path)) {
        printf("Error\n");
    }
    board.placeMove(player, location);
    grid[location].setTexture(&gridTextures[location]);
}

/*
EFFECT: sets text string to winning message and displays on the window
MODIFIES: this, sf::RenderWindow
*/
void PlayerGUI::drawWin(sf::Text text) {
    text.setString("Congrats Player " + std::to_string(player) + "!");
    window->draw(text);
}