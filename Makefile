CC       = g++
CPPFLAGS = -g -Wall

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files

all: puzzle

puzzle: puzzle.cpp puzzle_move.o puzzle_heur.o board.o puzzle_solver.o
	$(CC) $(CPPFLAGS) puzzle.cpp puzzle_move.o puzzle_heur.o board.o puzzle_solver.o -o puzzle

puzzle_move.o: puzzle_move.h puzzle_move.cpp
	$(CC) $(CPPFLAGS) -c puzzle_move.cpp -o puzzle_move.o

puzzle_heur.o: puzzle_heur.h puzzle_heur.cpp
	$(CC) $(CPPFLAGS) -c puzzle_heur.cpp -o puzzle_heur.o

board.o: board.h board.cpp
	$(CC) $(CPPFLAGS) -c board.cpp -o board.o

puzzle_solver.o: puzzle_solver.h heap.h puzzle_solver.cpp 
	$(CC) $(CPPFLAGS) -c puzzle_solver.cpp -o puzzle_solver.o

clean:
	rm puzzle
	rm *.o