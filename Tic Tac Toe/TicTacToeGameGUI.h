#pragma once
#include "Board.h"
#include "PlayerGUI.h"
#include "ComputerGUI.h"
#include <SFML/Graphics.hpp>

class TicTacToeGameGUI {
private:
	enum page { mainMenu = 0, playerSelection = 1, playingGame = 2, winningScreen = 3 };

	const float gridSize = 300.f;
	const int windowWidth = 1500;
	const int windowHeight = 1500;
	const float offset = 100.f;
	Board board;
	int playerCount;
	int currentPlayer;
	int moves;
	enum page p;
	PlayerGUI *player1;
	PlayerGUI *player2;
	int round;
	sf::RectangleShape grid[10];
	sf::Texture gridTextures[10];
	sf::Text winMessage;
	sf::Font font;

	void runGame();
	void initGridShapes();
	void initMainMenu();
	void initWinningScreen(sf::RenderWindow& window);
	void initPlayerSelection();
	void drawGridShapes(sf::RenderWindow &window);
	void drawMainMenu(sf::RenderWindow& window);
	void drawWin(sf::RenderWindow& window, int winner);
	void drawPlayerSelection(sf::RenderWindow& window);
	void playerMove(sf::RenderWindow& window, sf::Vector2i pos);
	void checkForMove(sf::RenderWindow& window, sf::Event event);
	void displayDraw(sf::RenderWindow& window);


public:
	TicTacToeGameGUI();
};
