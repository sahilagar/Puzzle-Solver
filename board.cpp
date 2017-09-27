#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::Board(const Board& other)
{
	size_ = other.size();
	tiles_ = new int[size_];
	for (int i = 0; i < size(); i++)
	{
		tiles_[i] = other.tiles_[i];
	}
	
}
Board::~Board()
{
	delete[] tiles_;

}


void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
	map<int, Board*> validMoves;

	int side_dim = dim();
  	int br, bc;

	// find blank row and column
	int j=-1;
	while(tiles_[++j] != 0);

	br = j / side_dim;
	bc = j % side_dim;
	Board* temp;

	for (int i = 0; i < size_; i++){
		int tr = i / side_dim;
		int tc = i%side_dim;
		if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) == 1){
			temp = new Board(*this);
			int moveValue = tiles_[i];
			temp->move(moveValue);
			validMoves.insert(make_pair(moveValue, temp));
		}
	}		

	return validMoves;
  
}

bool Board::solved() const
{
	for (int i=0; i < size_; i++){
		if (tiles_[i] != i){
			return false;
		}
	}
	return true;
}

bool Board::operator<(const Board& rhs) const
{
	for (int i=0; i < size_; i++){
		if (this->tiles_[i] < rhs[i]){
			return true;
		}
		else if (this->tiles_[i] == rhs[i]){
			continue;
		}
		else{
			return false;
		}
	}
	return false;

}


const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
std::ostream& operator<<(std::ostream &os, const Board &b)
{
	//print
	int i = 0;
	while (i < b.size()){
		b.printRowBanner(os);
		for (int j=0; j < b.dim(); j++){			
			//not 0 less than 10
			if (b[i] != 0 && b[i] < 10){
				os << "| " << b[i++];
			}
			//num is two digits
			else if(b[i] >= 10){
				os << "|" << b[i++];
			}
			else{
				i++;
				os << "|  ";
			}
		}
		os << "|" << endl;
	}
	b.printRowBanner(os);
	return os;

}