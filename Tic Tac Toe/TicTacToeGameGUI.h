#pragma once
#include "Board.h"
#include "PlayerGUI.h"
#include "ComputerGUI.h"
#include <SFML/Graphics.hpp>

class TicTacToeGameGUI {
private:
	const float gridSize = 300.f;
	const int windowWidth = 1500;
	const int windowHeight = 1500;
	Board board;
	int playerCount;
	int currentPlayer;
	int round;
	sf::RectangleShape shapes[10];
	sf::Texture textures[10];

	void runGame();
	void initGridShapes();
	void drawGridShapes(sf::RenderWindow &window);
	void processMouseInput(sf::RenderWindow &window, sf::Vector2i pos);

public:
	TicTacToeGameGUI();
};
