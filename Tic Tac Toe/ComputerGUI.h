#pragma once
#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include <SFML/Graphics.hpp>
class ComputerGUI : public PlayerGUI{
private:
	int randomMove();
public:
	ComputerGUI(Board b, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t);

	bool makeMove(sf::Vector2i pos);
	void drawWin(sf::Text text);
};

