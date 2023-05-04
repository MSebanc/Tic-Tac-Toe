#include "Player.h"
#include "Computer.h"

class Game {
private:
	int **board;
	int playerCount;
	Player player1;
	Player player2;

	void initPlayers() {
		player1 = Player();
		if (playerCount == 1) {
			player2 = Computer();
		}
		else {
			player2 = Player();
		}
	}

	void initBoard() {
		board = new int*[3];
		for (int i = 0; i < 3; i++) {
			board[i] = new int(0);
		}
	}

public:
	Game() = default;

	Game(int players) {
		playerCount = players;
		if (playerCount > 2) playerCount = 2;
		if (playerCount < 1) playerCount = 1;
		initPlayers();
		initBoard();
	}

	void placeMove(int player, int location) {

	}

	int** getBoard() {
		return board;
	}

	Player getPlayer(int num) {
		if (num == 1) {
			return player1;
		}
		return player2;
	}
};

