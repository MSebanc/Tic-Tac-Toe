#include "TicTacToeGameGUI.h"
#include "Board.h"
#include "PlayerGUI.h"
#include "ComputerGUI.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <stdlib.h>

/*
EFFECT: Constructor, starts the game by calling runGame();
MODIFIES: this
*/
TicTacToeGameGUI::TicTacToeGameGUI() {
	runGame();
}

/*
EFFECT: displays an sfml window and calls functions for each functionity of the window
MODIFIES: this, Board
*/
void TicTacToeGameGUI::runGame() {

    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        printf("Error!\n");
    }
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tic Tac Toe!", sf::Style::Titlebar | sf::Style::Close);

    clearBoard();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        switch (p) {
        case playingGame:
            checkForMove(window, event);
            break;
        case winningScreen:
            checkForReturn(window, event);
            break;
        case mainMenu:
            checkForSelection(window, event);
            break;
        case displayRules:
            checkForReturn(window, event);
            break;
        case difficulty:
            checkForDifficultyChoice(window, event);
            checkForReturn(window, event);
            break;
        }

        window.clear();

        int winner = board.findWinner();
        if (winner || moves == 9) p = winningScreen;
        
        switch (p) {
        case mainMenu:
            drawMainMenu(window);
            break;
        case displayRules:
            drawRules(window);
            break;
        case difficulty:
            drawDifficulty(window);
            break;
        case playingGame:
            drawGridShapes(window);
            break;
        case winningScreen:
            drawWin(window, winner);
            drawGridShapes(window);
            break;
        }

        window.display();
    }

    if (p == playingGame || p == winningScreen) clearBoard();
    board.freeBoard();
}

/*
EFFECT: checks most recent event to see if it is a left mouse click and calls the difficulySelection function
MODIFIES: this
*/
void TicTacToeGameGUI::checkForDifficultyChoice(sf::RenderWindow& window, sf::Event event) {
    window.pollEvent(event);
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        difficultySelection(window, sf::Mouse::getPosition(window));
    }
}

/*
EFFECT: determines if given position vector is contained in the bounds of difficulty selection buttons 
and creates a new Player and Computer based on the difficulty of selection
MODIFIES: this
*/
void TicTacToeGameGUI::difficultySelection(sf::RenderWindow& window, sf::Vector2i pos) {
    for (int i = 0; i < 2; i++) {
        if (diff[i].getGlobalBounds().contains(window.mapPixelToCoords(pos))) {
            player1 = new PlayerGUI(board, 1, &window, &grid[0], &gridTextures[0]);
            player2 = new ComputerGUI(board, &window, &grid[0], &gridTextures[0], i);
            p = playingGame;
        }
    }
}


/*
EFFECT: initializes sfml objects needed for difficulty selection page and positions them on the page
MODIFIES: this
*/
void TicTacToeGameGUI::initDifficultySelection() {
    diffMessage.setFont(font);
    diffMessage.setCharacterSize(90);
    diffMessage.setString("Please Choose A Difficulty\nLevel For Computer\n");
    diffMessage.setPosition(windowWidth / 6.f, windowHeight / 2.f);

    float height = windowHeight / 5.f;
    float width = windowWidth / 2.f - optionWidth - offset/4;
    for (int i = 0; i < 2; i++) {
        sf::RectangleShape shape(sf::Vector2f(optionWidth, optionHeight));
        shape.setOrigin(optionWidth / 2, optionHeight / 2);
        shape.setPosition(width, height);
        shape.setOutlineColor(sf::Color(105, 105, 105));
        shape.setOutlineThickness(optionHeight / 25);
        diff[i] = shape;
        width += optionWidth*2 + offset/2;
    }

    if (!diffTexture[0].loadFromFile("Easy.png")) {
        printf("Error\n");
    }
    diff[0].setTexture(&diffTexture[0]);
    if (!diffTexture[1].loadFromFile("Hard.png")) {
        printf("Error\n");
    }
    diff[1].setTexture(&diffTexture[1]);
}

/*
EFFECT: displays difficulty Selection page onto window 
MODIFIES: this, sf::RenderWindow
*/
void TicTacToeGameGUI::drawDifficulty(sf::RenderWindow& window) {
    for (int i = 0; i < 2; i++) {
        window.draw(diff[i]);
    }
    window.draw(returnMenu);
    window.draw(diffMessage);
}


/*
EFFECT: deallocates player1, player2, and board and creates a new board, sets currentPlayer to 1, playerCount to 1,
moves to 0 and initalizes each page of the game
MODIFIES: this
*/
void TicTacToeGameGUI::clearBoard() {
    delete player1;
    delete player2;

    board.freeBoard();
    board = Board();
    currentPlayer = 1;
    playerCount = 1;
    moves = 0;
    initGridShapes();
    initWinningScreen();
    initRulesPage();
    initDifficultySelection();
    initReturnMessage();
    initMainMenu();
}

/*
EFFECT: checks most recent event to see if it is a left mouse click and calls the returnToMenu function
MODIFIES: this
*/
void TicTacToeGameGUI::checkForReturn(sf::RenderWindow &window, sf::Event event) {
    window.pollEvent(event);
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        returnToMenu(window, sf::Mouse::getPosition(window));
    }
}

/*
EFFECT: determines if given position vector is contained in the bounds of the return button,
clears the game if the current page is winningScreen and sets the page to mainMenu
MODIFIES: this
*/
void TicTacToeGameGUI::returnToMenu(sf::RenderWindow& window, sf::Vector2i pos) {
    if (returnMenu.getGlobalBounds().contains(window.mapPixelToCoords(pos))) {
        if (p == winningScreen) clearBoard();
        p = mainMenu;
    }
}

/*
EFFECT: initializes sfml objects needed for the return button and positions them on the page
MODIFIES: this
*/
void TicTacToeGameGUI::initReturnMessage() {
    sf::RectangleShape shape(sf::Vector2f(returnWidth, returnHeight));
    shape.setOrigin(returnWidth / 2, returnHeight / 2);
    shape.setPosition(windowWidth / 2.f, windowHeight / 15.f);
    shape.setOutlineColor(sf::Color(105, 105, 105));
    shape.setOutlineThickness(returnWidth / 25);
    returnMenu = shape;

    if (!returnMenuTexture.loadFromFile("return.png")) {
        printf("Error\n");
    }
    returnMenu.setTexture(&returnMenuTexture);
}

/*
EFFECT: initializes sfml objects needed for the return page and positions them on the page
MODIFIES: this
*/
void TicTacToeGameGUI::initRulesPage() {
    rulesMessage.setFont(font);
    rulesMessage.setCharacterSize(50);
    std::string message = "The object of Tic Tac Toe is to get three in a row.\n"
        "You play on a three by three game board.\n"
        "The first player is known as X and the second is O.\n"
        "Players alternate placing Xs and Os on the game board until\n"
        "either oppent has three in a row or all nine squares are filled.\n"
        "X always goes first, and in the event that no one has three in a\n"
        "row, the stalemate is a tie so there is a draw.";
    rulesMessage.setString(message);
    rulesMessage.setPosition(windowWidth / 20.f, windowHeight / 7.f);
}

/*
EFFECT: displays rules page onto window
MODIFIES: this, sf::RenderWindow
*/
void TicTacToeGameGUI::drawRules(sf::RenderWindow& window) {
    window.draw(rulesMessage);
    window.draw(returnMenu);
}

/*
EFFECT: checks most recent event to see if it is a left mouse click and calls the menuSelection function
MODIFIES: this
*/
void TicTacToeGameGUI::checkForSelection(sf::RenderWindow& window, sf::Event event) {
    window.pollEvent(event);
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        menuSelection(window, sf::Mouse::getPosition(window));
    }
}

/*
EFFECT: determines if given position vector is contained in the bounds of menu selection buttons
and changes the page according to the button pressed. Allocates new player1 and player2 if two player
button is selected
MODIFIES: this
*/
void TicTacToeGameGUI::menuSelection(sf::RenderWindow& window, sf::Vector2i pos) {
    for (int i = 0; i < 3; i++) {
        if (options[i].getGlobalBounds().contains(window.mapPixelToCoords(pos))) {
            switch (i) {
            case 0:
                p = displayRules;
                break;
            case 1:
                p = difficulty;
                playerCount = 1;
                break;
            case 2:
                p = playingGame;
                playerCount = 2;
                player1 = new PlayerGUI(board, 1, &window, &grid[0], &gridTextures[0]);
                player2 = new PlayerGUI(board, 2, &window, &grid[0], &gridTextures[0]);
                break;
            }
        }
    }
}

/*
EFFECT: initializes sfml objects needed for the winning screen and positions them on the page
MODIFIES: this
*/
void TicTacToeGameGUI::initWinningScreen() {
    winMessage.setFont(font);
    winMessage.setCharacterSize(125);
    winMessage.setPosition(windowWidth / 6.f, windowHeight / 10.f);
}
/*
EFFECT: initializes sfml objects needed for the main menu page and positions them on the page
MODIFIES: this
*/
void TicTacToeGameGUI::initMainMenu() {
    menuMessage.setFont(font);
    menuMessage.setCharacterSize(90);
    menuMessage.setString("Welcome To Tic Tac Toe!\nPlease Select An Option");
    menuMessage.setPosition(windowWidth/6.f, windowHeight/2.f);

    float height = windowHeight / 5.f;
    float width = windowWidth / 2.f - optionWidth - offset / 4;
    for (int i = 0; i < 3; i++) {
        sf::RectangleShape shape(sf::Vector2f(optionWidth, optionHeight));
        shape.setOrigin(optionWidth / 2, optionHeight / 2);
        shape.setPosition(width, height);
        shape.setOutlineColor(sf::Color(105, 105, 105));
        shape.setOutlineThickness(optionHeight / 25);
        options[i] = shape;
        width += optionWidth + offset / 4;
    }

    if (!optionTextures[0].loadFromFile("Rules.png")) {
        printf("Error\n");
    }
    options[0].setTexture(&optionTextures[0]);
    if (!optionTextures[1].loadFromFile("OnePlayer.png")) {
        printf("Error\n");
    }
    options[1].setTexture(&optionTextures[1]);
    if (!optionTextures[2].loadFromFile("TwoPlayer.png")) {
        printf("Error\n");
    }
    options[2].setTexture(&optionTextures[2]);
}

/*
EFFECT: displays main menu page onto window
MODIFIES: this, sf::RenderWindow
*/
void TicTacToeGameGUI::drawMainMenu(sf::RenderWindow &window) {
    window.draw(menuMessage);
    for (int i = 0; i < 3; i++) {
        window.draw(options[i]);
    }
}

/*
EFFECT: displays winning screen page onto window
MODIFIES: this, sf::RenderWindow
*/
void TicTacToeGameGUI::drawWin(sf::RenderWindow& window, int winner) {
    if (winner == 1) player1->drawWin(winMessage);
    else if (winner == 2) player2->drawWin(winMessage);
    else displayDraw(window);
    window.draw(returnMenu);
}

/*
EFFECT: displays draw message onto window
MODIFIES: this, sf::RenderWindow
*/
void TicTacToeGameGUI::displayDraw(sf::RenderWindow& window) {
    winMessage.setString("Looks Like A Draw!");
    window.draw(winMessage);
}

/*
EFFECT: initializes sfml objects needed for the game grid and positions them on the page
MODIFIES: this
*/
void TicTacToeGameGUI::initGridShapes() {
    float height = windowHeight / 2.f - gridSize + 2*offset;
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

/*
EFFECT: displays game grid onto window
MODIFIES: this, sf::RenderWindow
*/
void TicTacToeGameGUI::drawGridShapes(sf::RenderWindow &window) {
    for (int i = 1; i < 10; i++) {
        window.draw(grid[i]);
    }
}

/*
EFFECT: determines if given position vector is contained in the bounds of game grid
and places the player move in that location. If it is the computer's turn the computerMove 
function is called instead
MODIFIES: this
*/
void TicTacToeGameGUI::checkForMove(sf::RenderWindow& window, sf::Event event) {
    window.pollEvent(event);
    if (playerCount == 1 && currentPlayer == 2) {
        computerMove();
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
         playerMove(sf::Mouse::getPosition(window));
    }
}

/*
EFFECT: calls makeMove function for computer player with empty position vector, increases move count and 
changes currentPlayer to 1
MODIFIES: this
*/
void TicTacToeGameGUI::computerMove() {
    sf::Vector2i emptyPos(0, 0);
    player2->makeMove(emptyPos);
    currentPlayer = 1;
    moves++;
}

/*
EFFECT: calls makeMove function of the current player with given position vector, 
increases move count and changes currentPlayer to the next player to move
*/
void TicTacToeGameGUI::playerMove(sf::Vector2i pos) {
    if (currentPlayer == 1) {
        if (player1->makeMove(pos)) {
            currentPlayer = 2;
            moves++;
        }
    }
    else {
        if (player2->makeMove(pos)) { 
            currentPlayer = 1; 
            moves++;
        }
    }
}