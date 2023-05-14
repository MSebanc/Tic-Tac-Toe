#include "ComputerMoves.h"
#include<iostream>
#include<cstdlib>

/*
EFFECT: constructs ComputerMoves by changing the set seed to the current time to maintain
randomness of the program
MODIFIES: this
*/
ComputerMoves::ComputerMoves() {
	srand((unsigned)time(NULL));
}

/*
REQUIRES: given array is length 10
EFFECT: returns true if any of the possible winning rows, columns and diagonals
are equal to given player, false otherwise
MODIFIES: none
*/
bool ComputerMoves::findWinner(int* b, int p) {
	if ((b[3] == b[6] && b[3] == b[9] && b[3] == p) ||
		(b[2] == b[5] && b[2] == b[8] && b[2] == p) ||
		(b[1] == b[4] && b[1] == b[7] && b[1] == p) ||
		(b[3] == b[2] && b[3] == b[1] && b[3] == p) ||
		(b[6] == b[5] && b[6] == b[4] && b[6] == p) ||
		(b[9] == b[8] && b[9] == b[7] && b[9] == p) ||
		(b[3] == b[5] && b[3] == b[7] && b[3] == p) ||
		(b[9] == b[5] && b[9] == b[1] && b[9] == p)) {
		return true;
	}

	return false;
}

/*
* REQUIRES: given array is length 10
EFFECT: returns true if all locations are occupied, false otherwise
*/
bool ComputerMoves::noMoreMoves(int* b) {
	for (int i = 1; i < 10; i++) {
		if (!b[i]) return false;
	}
	return true;
}

/*
REQUIRES: given array is length 10
EFFECT: runs recursive minimax algorithm.
See https://en.wikipedia.org/wiki/Minimax for info on the algorithm
MODIFIES: none
*/
ComputerMoves::scoreStruct ComputerMoves::minimax(int* b, int p) {
	if (findWinner(b, 1)) {
		scoreStruct score;
		score.score = -10;
		score.index = 0;
		return score;
	}
	else if (findWinner(b, 2)) {
		scoreStruct score;
		score.score = 10;
		score.index = 0;
		return score;
	}
	else if (noMoreMoves(b)) {
		scoreStruct score;
		score.score = 0;
		score.index = 0;
		return score;
	}

	scoreStruct scores[10];
	for (int i = 0; i < 10; i++) {
		scores[i].score = 0;
		scores[i].index = i;
	}

	for (int i = 1; i < 10; i++) {
		if (!b[i]) {
			b[i] = p;
			if (p == 2) {
				scores[i].score = minimax(b, 1).score;
				scores[i].index = i;
			}
			else {
				scores[i].score = minimax(b, 2).score;
				scores[i].index = i;
			}
			b[i] = 0;
		}
	}

	int bestMove;
	if (p == 2) {
		int bestScore = -10000;
		for (int i = 1; i < 10; i++) {
			if (!b[i]) {
				if (scores[i].score > bestScore) {
					bestScore = scores[i].score;
					bestMove = i;
				}
			}
		}
	}
	else {
		int bestScore = 10000;
		for (int i = 1; i < 10; i++) {
			if (!b[i]) {
				if (scores[i].score < bestScore) {
					bestScore = scores[i].score;
					bestMove = i;
				}
			}
		}
	}
	scoreStruct bestStruct;
	bestStruct.score = scores[bestMove].score;
	bestStruct.index = bestMove;
	return bestStruct;
}

/*
EFFECT: finds a random number from 1 to 9 until the move is valid, then returns the move location
MODIFIES: none
*/
int ComputerMoves::randomMove(Board board) {
	int location = 0;
	while (location < 1 || location > 9 || !board.isValidMove(location)) {
		location = 1 + (rand() % 9);
	}
	return location;
}