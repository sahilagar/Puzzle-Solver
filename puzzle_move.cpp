#include "puzzle_move.h"

using namespace std;

PuzzleMove::PuzzleMove(Board* board): tileMove(-1), b(board), g(0), h(0), prev(NULL)
{
}

  // Constructor for subsequent search boards 
  // (i.e. those returned by Board::potentialMoves() 
PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent): tileMove(tile),
 b(board), g(parent->g + 1), h(0), prev(parent)
{
}

  // Destructor
PuzzleMove::~PuzzleMove()
{
	delete b;
}