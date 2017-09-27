#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

	int n = atoi(argv[1]);
	int initMoves = atoi(argv[2]);
	int seed = atoi(argv[3]);
	int heur = atoi(argv[4]);
	Board b(n, initMoves, seed);

	int input;
	deque<int> d;
	cout << b << endl;
	
	cout << "Enter tile number to move or -1 for a cheat: ";
	while(cin >> input){		
		if (input == -1){
			PuzzleHeuristic* h = NULL;			
			if(heur == 0){
				h = new PuzzleBFSHeuristic;
			}
			if(heur == 1){
				h = new PuzzleOutOfPlaceHeuristic;
			}
			if(heur == 2){
				h = new PuzzleManhattanHeuristic;
			}
			PuzzleSolver solver(b, h);
			solver.run();
			
			d.clear();
			d = solver.getSolution();
			cout << "Solution Sequence:" << endl;
			for (unsigned int i=0; i < d.size(); i++){

				cout << d[i] << " ";				
			}
			cout << endl;
			cout << "Number of Expansions: " << solver.getNumExpansions() << endl;
			delete h;
		}
		if (input == 0){
			break;
		}
		if(input >=0 && input <= n*n){
			b.move(input);
		}		
		if (b.solved()){
			cout << b << endl;
			break;
		}
		cout << b << endl;		
	}
	

    return 0;
}
