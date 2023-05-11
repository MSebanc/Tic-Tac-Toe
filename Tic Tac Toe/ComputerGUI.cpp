#include "ComputerGUI.h"
#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include <SFML/Graphics.hpp>

ComputerGUI::ComputerGUI(Board b, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t) {
	board = b;
	window = w;
	grid = s;
	player = 2;
	path = "oImage.png";
	gridTextures = t;
}