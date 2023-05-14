#pragma once
#include "PlayerGUI.h"
#include "Board.h"
#include "ComputerMoves.h"
#include<iostream>
#include <SFML/Graphics.hpp>

/*
Represents a computer player in Tic Tac Toe
*/
class ComputerGUI : public PlayerGUI{
private:
	const float wait = 0.5f;

	ComputerMoves moves;

	int difficulty;
	sf::Clock delay;
public:
	ComputerGUI(Board b, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t, int d);
	void makeMoveMinimax();
	void makeMoveRandom();
	bool makeMove(sf::Vector2i pos);
	void drawWin(sf::Text text);
};

