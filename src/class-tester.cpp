// class-tester.cpp; test class calling class features.
#include <string>
#include <iostream>
#include "sudoku-solver.h"
using namespace std;
void test_board(string infile);
void test_solve(string infile);
int main()
{
	cout << "===class-tester===" << endl;

	string infile("./sample/board");
	//test_board(infile);
	test_solve(infile);
}
void test_board(std::string infile)
{
	cout << "===test_board===" << endl;
	cout << "infile:" << infile << endl;
	Board board(infile);
	board.print();
}
void test_solve(std::string infile)
{
	cout << "===test_solve===" << endl;
	cout << "infile:" << infile << endl;
	Board board(infile);
	Sudoku_solver solver;
	solver.execute(board);
}
