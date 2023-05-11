#include "TicTacToeGameGUI.h"
#include "Board.h"
#include "PlayerGUI.h"
#include "ComputerGUI.h"
#include <SFML/Graphics.hpp>
#include <cmath>

TicTacToeGameGUI::TicTacToeGameGUI() {
	runGame();
}

void TicTacToeGameGUI::runGame() {

    currentPlayer = 1;
    moves = 0;

    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        printf("Error!\n");
    }
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tic Tac Toe!", sf::Style::Titlebar | sf::Style::Close);

    initGridShapes();
    initWinningScreen(window);

    p = playingGame;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (p == playingGame) {
                checkForMove(window, event);
            }
            else if (p == winningScreen) {

            }
        }

        

        player1 = new PlayerGUI(board, 1, &window, &grid[0], &gridTextures[0]);
        player2 = new PlayerGUI(board, 2, &window, &grid[0], &gridTextures[0]);

        window.clear();

        if (p == playingGame || p == winningScreen) drawGridShapes(window);

        int winner = board.findWinner();
        if (winner || moves == 9) p = winningScreen;
        if (p == winningScreen) drawWin(window, winner);

        window.display();
    }
}

void TicTacToeGameGUI::initWinningScreen(sf::RenderWindow &window) {
    winMessage.setFont(font);
    winMessage.setCharacterSize(125);
    winMessage.setPosition(windowWidth/6.f, windowHeight/11.f);
}

void TicTacToeGameGUI::drawWin(sf::RenderWindow& window, int winner) {
    if (winner == 1) player1->drawWin(winMessage);
    else if (winner == 2) player2->drawWin(winMessage);
    else displayDraw(window);
}

void TicTacToeGameGUI::displayDraw(sf::RenderWindow& window) {
    winMessage.setString("Looks Like A Draw!");
    window.draw(winMessage);
}

void TicTacToeGameGUI::initGridShapes() {
    float height = windowHeight / 2.f - gridSize + offset;
    for (int i = 0; i < 3; i++) {
        float width = windowHeight / 2.f - gridSize;
        for (int j = 0; j < 3; j++) {
            sf::RectangleShape shape(sf::Vector2f(gridSize, gridSize));
            shape.setOrigin(gridSize / 2, gridSize / 2);
            shape.setPosition(width, height);
            shape.setOutlineColor(sf::Color(105, 105, 105));
            shape.setOutlineThickness(gridSize / 25);
            grid[3 * (j + 1) - i] = shape;
            width += gridSize;
        }
        height += gridSize;
    }
}

void TicTacToeGameGUI::drawGridShapes(sf::RenderWindow &window) {
    for (int i = 1; i < 10; i++) {
        window.draw(grid[i]);
    }
}

void TicTacToeGameGUI::checkForMove(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            playerMove(window, sf::Mouse::getPosition(window));
        }
    }
}

void TicTacToeGameGUI::playerMove(sf::RenderWindow& window, sf::Vector2i pos) {
    if (currentPlayer == 1) {
        if (player1->makeMove(sf::Mouse::getPosition(window))) {
            currentPlayer = 2;
            moves++;
        }
    }
    else {
        if (player2->makeMove(sf::Mouse::getPosition(window))) { 
            currentPlayer = 1; 
            moves++;
        }
    }
}