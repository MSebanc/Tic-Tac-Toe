#include "TicTacToeGameGUI.h"
#include "Board.h"
#include "PlayerGUI.h"
#include "ComputerGUI.h"
#include <SFML/Graphics.hpp>

TicTacToeGameGUI::TicTacToeGameGUI() {
	runGame();
}

void TicTacToeGameGUI::runGame() {

    currentPlayer = 1;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tic Tac Toe!");

    initGridShapes();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    processMouseInput(window, sf::Mouse::getPosition(window));
                }
            }
        }

        window.clear();

        drawGridShapes(window);

        window.display();
    }
}

void TicTacToeGameGUI::initGridShapes() {
    float height = windowHeight / 2.f - gridSize;
    for (int i = 0; i < 3; i++) {
        float width = windowHeight / 2.f - gridSize;
        for (int j = 0; j < 3; j++) {
            sf::RectangleShape shape(sf::Vector2f(gridSize, gridSize));
            shape.setOrigin(gridSize / 2, gridSize / 2);
            shape.setPosition(width, height);
            shape.setOutlineColor(sf::Color(105, 105, 105));
            shape.setOutlineThickness(gridSize / 25);
            shapes[3 * (j + 1) - i] = shape;
            width += gridSize;
        }
        height += gridSize;
    }
}

void TicTacToeGameGUI::drawGridShapes(sf::RenderWindow &window) {
    for (int i = 1; i < 10; i++) {
        window.draw(shapes[i]);
    }
}

void TicTacToeGameGUI::processMouseInput(sf::RenderWindow &window, sf::Vector2i pos) {
    for (int i = 1; i < 10; i++) {
        if (shapes[i].getGlobalBounds().contains(window.mapPixelToCoords(pos))) {
            std::string path = "xImage.png";
            if (currentPlayer == 2) path = "oImage.png";
            if (!textures[i].loadFromFile(path)) {
                printf("Error\n");
            }
            shapes[i].setTexture(&textures[i]);
            if (currentPlayer == 1) currentPlayer = 2;
            else currentPlayer = 1;
            break;
        }
    }
}