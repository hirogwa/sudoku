// sudoku-util.cpp
// entry to sudoku utility
#include <iostream>
#include <cstring>
#include <string>
#include "board.h"
#include "sudoku-solver.h"
void solve(std::string infile);
void show_usage();
int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		show_usage();
	}
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			if (strcmp(argv[i], "-s") == 0)
			{
				solve(argv[i + 1]);
				break;
			}
		}
	}
	return 0;

}
void show_usage()
{
	std::cout << "Usage: sudoku-util [OPTION]... FILE..." << std::endl;
	std::cout << "Utility functions for sudoku board." << std::endl;
	std::cout << "  -s	solve the sudoku board given by the parameter (csv)" << std::endl;
}
void solve(std::string infile)
{
	Board board = Board(infile);
	Sudoku_solver solver;
	solver.execute(board);
}
