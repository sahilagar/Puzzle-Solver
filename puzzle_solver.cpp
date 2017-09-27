#include "puzzle_solver.h"
#include <iostream>

using namespace std;

// Constructor (makes a copy of the Board and stores it in b_)
//  Also takes a PuzzleHeuristic which will score boards
PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph): b_(b), expansions_(0), ph_(ph)
{
}

// Destructor
PuzzleSolver::~PuzzleSolver()
{
	for (unsigned int i= 0; i < puzzleMoves.size(); i++){
		if (puzzleMoves[i])
	 		delete puzzleMoves[i];
	}
	
}

// Run the A* search and builds the solution and tracks
// the number of expansions
void PuzzleSolver::run()
{
	PuzzleMoveScoreComp scoreComp; 
	Heap<PuzzleMove*, PuzzleMoveScoreComp> open(2,scoreComp);
  	
	Board* b = new Board(b_);
 	PuzzleMove* initialPuzzleMove = new PuzzleMove(b);
 	open.push(initialPuzzleMove);
 	puzzleMoves.push_back(initialPuzzleMove);

 	while(open.empty() != true)
 	{

 		PuzzleMove* temp = open.top();
 		temp->h = ph_->compute(b_);
 		closed.insert(temp);
 		open.pop();

 		if (temp->b->solved()){
 			//backtrack and solve
 			while(temp->prev != NULL){
 				solution_.push_front(temp->tileMove);
 				temp = temp->prev;
 			}
 			
 			return;
 		}
 		//iterate through potential moves map
 		map<int, Board*> potentialMoves = temp->b->potentialMoves();
 		for (map<int, Board*>::iterator it = potentialMoves.begin(); it != potentialMoves.end(); ++it){
 			//if didn't find the board in closed, add it to open
 			PuzzleMove* toAdd = new PuzzleMove(it->first, it->second, temp);
 			puzzleMoves.push_back(toAdd);
 			PuzzleMoveSet::iterator sit = closed.find(toAdd); 			
 			if (sit == closed.end()){
 				//construct a puzzle move and push it 				
 				toAdd->h = ph_->compute(*it->second);
 				open.push(toAdd);
 				closed.insert(toAdd);
 				expansions_++;
 			}
 		} 		
 	}
}

// Return the solution deque
std::deque<int> PuzzleSolver::getSolution()
{
	return solution_;
}

// Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions()
{
	return expansions_;
}