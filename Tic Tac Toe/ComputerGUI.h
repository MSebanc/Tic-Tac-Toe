#pragma once
#include "PlayerGUI.h"
#include "Board.h"
#include<iostream>
#include <SFML/Graphics.hpp>
class ComputerGUI : public PlayerGUI{
private:
	struct scoreStruct {
		int score;
		int index;
	};

	int difficulty;

	int randomMove();
	void makeMoveMinimax();
	void makeMoveRandom();
	bool findWinner(int *b, int p);
	struct scoreStruct minimax(int *b, int p);
	bool noMoreMoves(int *b);
public:
	ComputerGUI(Board b, sf::RenderWindow* w, sf::RectangleShape* s, sf::Texture* t, int d);

	bool makeMove(sf::Vector2i pos);
	void drawWin(sf::Text text);
};

