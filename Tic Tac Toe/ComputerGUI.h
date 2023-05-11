#pragma once
#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include <SFML/Graphics.hpp>
class ComputerGUI : public PlayerGUI {
private:
	int randomMove();
public:
	ComputerGUI(Board b, sf::RenderWindow *w, sf::RectangleShape *s, sf::Texture *t);
	void makeMove();
	void displayWinner();
};

