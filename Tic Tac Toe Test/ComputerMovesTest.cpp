#include "pch.h"
#include "CppUnitTest.h"
#include "../Tic Tac Toe/ComputerMoves.h"
#include "../Tic Tac Toe/ComputerMoves.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComputerMovesTest
{
	TEST_CLASS(ComputerMovesTest)
	{
	public:

		TEST_METHOD(TestRandomMove) {
			Board board;
			ComputerMoves moves;
			bool inRange = true;
			int random = moves.randomMove(board);
			if (random < 1 || random > 9) inRange = false;
			Assert::IsTrue(inRange);
			
			board.placeMove(1, 1);
			board.placeMove(1, 2);
			board.placeMove(1, 3);
			board.placeMove(1, 4);
			board.placeMove(1, 5);
			board.placeMove(1, 6);
			board.placeMove(1, 7);
			board.placeMove(1, 8);
			Assert::AreEqual(9, moves.randomMove(board));

			board.freeBoard();
		}

		TEST_METHOD(TestMinimax) {
			Board board;
			ComputerMoves moves;
			board.placeMove(1, 3);
			int* b = board.getCondencedBoard();
			Assert::AreEqual(5, moves.minimax(b, 2).index);
			delete b;

			board.placeMove(2, 5);
			board.placeMove(1, 9);
			b = board.getCondencedBoard();
			Assert::AreEqual(6, moves.minimax(b, 2).index);
			delete b;

			board.placeMove(2, 6);
			board.placeMove(1, 7);
			b = board.getCondencedBoard();
			Assert::AreEqual(4, moves.minimax(b, 2).index);
			delete b;

			board.freeBoard();
		}
	};
}