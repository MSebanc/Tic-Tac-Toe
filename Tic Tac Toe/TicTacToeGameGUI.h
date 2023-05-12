#pragma once
#include "Board.h"
#include "PlayerGUI.h"
#include "ComputerGUI.h"
#include <SFML/Graphics.hpp>

class TicTacToeGameGUI {
private:
	enum page { mainMenu = 0, displayRules = 1, playingGame = 2, winningScreen = 3, difficulty= 4};

	const float gridSize = 300.f;
	const float optionWidth = 400.f;
	const float optionHeight = 200.f;
	const float returnHeight = 50.f;
	const float returnWidth = 100.f;
	const int windowWidth = 1500;
	const int windowHeight = 1500;
	const float offset = 100.f;
	Board board;
	int playerCount;
	int currentPlayer;
	int moves;
	enum page p = mainMenu;
	PlayerGUI *player1;
	PlayerGUI *player2;
	int round;
	sf::RectangleShape grid[10];
	sf::RectangleShape diff[2];
	sf::Texture diffTexture[2];
	sf::Texture gridTextures[10];
	sf::Text diffMessage;
	sf::Text winMessage;
	sf::Text menuMessage;
	sf::Text rulesMessage;
	sf::RectangleShape returnMenu;
	sf::RectangleShape options[3];
	sf::Texture optionTextures[3];
	sf::Texture returnMenuTexture;
	sf::Font font;

	void runGame();
	void initGridShapes();
	void initMainMenu();
	void initWinningScreen();
	void initReturnMessage();
	void initRulesPage();
	void initDifficultySelection();
	void drawGridShapes(sf::RenderWindow &window);
	void drawMainMenu(sf::RenderWindow& window);
	void drawWin(sf::RenderWindow& window, int winner);
	void drawDifficulty(sf::RenderWindow& window);
	void drawRules(sf::RenderWindow& window);
	void playerMove(sf::Vector2i pos);
	void checkForMove(sf::RenderWindow& window, sf::Event event);
	void displayDraw(sf::RenderWindow& window);
	void computerMove();
	void checkForSelection(sf::RenderWindow& window, sf::Event event);
	void checkForDifficultyChoice(sf::RenderWindow& window, sf::Event event);
	void difficultySelection(sf::RenderWindow& window, sf::Vector2i pos);
	void menuSelection(sf::RenderWindow& window, sf::Vector2i pos);
	void checkForReturn(sf::RenderWindow& window, sf::Event event);
	void returnToMenu(sf::RenderWindow& window, sf::Vector2i pos);
	void clearBoard();

public:
	TicTacToeGameGUI();
};
