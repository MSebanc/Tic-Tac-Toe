#include "pch.h"
#include "CppUnitTest.h"
#include "../Tic Tac Toe/Board.h"
#include "../Tic Tac Toe/Board.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BoardTest
{
	TEST_CLASS(BoardTest)
	{
	public:

		TEST_METHOD(TestConstructor) {
			Board board;
			int** b = board.getBoard();
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					Assert::IsFalse(b[i][j]);
				}
			}
			board.freeBoard();
		}

		TEST_METHOD(TestPlaceMove) {
			Board board;
			board.placeMove(1, 1);
			int** b = board.getBoard();
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (3 * (j + 1) - i == 1) Assert::AreEqual(1, b[i][j]);
					else Assert::IsFalse(b[i][j]);
				}
			}
			board.placeMove(2, 7);
			b = board.getBoard();
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (3 * (j + 1) - i == 1) Assert::AreEqual(1, b[i][j]);
					else if (3 * (j + 1) - i == 7) Assert::AreEqual(2, b[i][j]);
					else Assert::IsFalse(b[i][j]);
				}
			}

			board.freeBoard();
		}

		TEST_METHOD(TestIsValidMove) {
			Board board;
			Assert::IsFalse(board.isValidMove(0));
			Assert::IsFalse(board.isValidMove(10));
			for (int i = 1; i < 10; i++) {
				Assert::IsTrue(board.isValidMove(i));
			}
			board.placeMove(2, 4);
			Assert::IsFalse(board.isValidMove(4));
			Assert::IsTrue(board.isValidMove(3));
			board.freeBoard();
		}

		TEST_METHOD(TestFindWinner) {
			Board board;
			Assert::IsFalse(board.findWinner());
			board.placeMove(1, 1);
			board.placeMove(1, 2);
			board.placeMove(2, 3);
			Assert::IsFalse(board.findWinner());
			board.placeMove(2, 6);
			board.placeMove(2, 9);
			Assert::IsTrue(board.findWinner());
			board.freeBoard();

			board = Board();
			board.placeMove(1, 1);
			board.placeMove(1, 2);
			board.placeMove(1, 3);
			Assert::IsTrue(board.findWinner());
			board.freeBoard();
		}
	};
}