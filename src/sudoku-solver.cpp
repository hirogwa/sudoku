// sudoku-solver.cpp
// class responsible for solving sudoku board
#include <iostream>
#include <set>
#include "sudoku-solver.h"
Sudoku_solver::Sudoku_solver()
{
	domop = new Domain_operation();
}
Sudoku_solver::~Sudoku_solver()
{
	delete domop;
}
void Sudoku_solver::execute(Board& board)
{
	std::cout << "solving starts..." << std::endl;
	board.print();
	if (this->solve_sudoku(board) == SOLVED)
	{
		std::cout << "solved." << std::endl;
		board.print();
	}
	else
	{
		std::cout << "solving failed." << std::endl;
	}
}
Solver_status Sudoku_solver::solve_sudoku(Board& board)
{
	if (refresh_domains(board))
	{
		return this->solve(board);
	}
	else
	{
		return FAILURE;
	}
}
bool Sudoku_solver::refresh_domains(Board& board)
{
	return (this->domop->refresh_domains(board) == DOM_SUCCESS);
}
Solver_status Sudoku_solver::solve(Board& board)
{
	Cell* cell = board.get_blank_cell();
	if (cell == NULL)
	{
		return SOLVED;
	}

	std::set<int> nums = cell->domain;
	for (std::set<int>::iterator it = nums.begin(); it != nums.end(); ++it)
	{
		assign_value(*cell, *it);
		if (domop->update_domains(board, *cell) == DOM_SUCCESS)
		{
			if (solve(board) == SOLVED)
				return SOLVED;
		}
	}
	// tried all the numbers but no luck.
	unassign_value(*cell);
	domop->update_domains(board, *cell);
	return FAILURE;
}
void Sudoku_solver::assign_value(Cell& cell, int val)
{
	cell.number = val;
	cell.blank = false;
}
void Sudoku_solver::unassign_value(Cell& cell)
{
	cell.number = 0;
	cell.blank = true;
}
