#pragma once
#include "Board.h"
#include<iostream>
#include <SFML/Graphics.hpp>

/*
Represents a player in Tic Tac Toe
*/
class PlayerGUI {
protected:
	Board board;
	int player;
	std::string path;
	sf::RenderWindow* window;
	sf::RectangleShape *grid;
	sf::Texture* gridTextures;

	void placeMove(int location);
private:

public:
	PlayerGUI();
	PlayerGUI(Board b, int p, sf::RenderWindow *w, sf::RectangleShape *s, sf::Texture *t);

	virtual bool makeMove(sf::Vector2i pos);
	virtual void drawWin(sf::Text text);
};