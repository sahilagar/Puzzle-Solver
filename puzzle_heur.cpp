#include "puzzle_heur.h"
#include <cmath>

using namespace std;

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int count = 0;
	for (int i = 1; i < b.size(); i++){
		int numIndex = -1;
		for (int j = 0; j < b.size(); j++){
			if (b[j] == i){ //find actual num index
				numIndex = j;
				break;
			}
		}

		int rCorrect = i/b.dim();
		int cCorrect = i%b.dim();

		int rActual = numIndex/b.dim();
		int cActual = numIndex%b.dim();

		count += abs(rActual - rCorrect) + abs(cActual - cCorrect);
	}

	return count;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int count = 0;
	for (int i=1; i < b.size(); i++)
	{
		if (b[i] != i){
			count++;
		}
	}
	return count;
}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}