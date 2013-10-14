OBJS = ./src/sudoku-util.cpp sudoku-solver.o domain-operation.o board.o utils.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
INCLUDE = -I ./include

#program main
sudoku-util : $(OBJS)
	$(CC) $(LFLAGS) $(INCLUDE) $(OBJS) -o sudoku-util
sudoku-solver.o : ./src/sudoku-solver.cpp ./include/sudoku-solver.h
	$(CC) $(CFLAGS) $(INCLUDE) ./src/sudoku-solver.cpp
board.o : ./src/board.cpp ./include/board.h
	$(CC) $(CFLAGS) $(INCLUDE) ./src/board.cpp
domain-operation.o : ./src/domain-operation.cpp ./include/domain-operation.h
	$(CC) $(CFLAGS) $(INCLUDE) ./src/domain-operation.cpp
utils.o : ./src/utils.cpp ./include/utils.h
	$(CC) $(CFLAGS) $(INCLUDE) ./src/utils.cpp
#test programs
TESTOBJS = ./src/class-tester.cpp sudoku-solver.o domain-operation.o board.o utils.o
class-tester : $(TESTOBJS)
	$(CC) $(LFLAGS) $(INCLUDE) $(TESTOBJS) -o class-tester
#others
clean:
	\rm *.o *~ sudoku-util class-tester
tar :
	tar cfv sudoku.tar \
		Makefile Readme \
		./src ./include ./sample
