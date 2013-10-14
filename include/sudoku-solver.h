// sudoku-sover.h
// class responsible for solving sudoku board.
#include "board.h"
#include <set>
#include "domain-operation.h"
enum Solver_status {FAILURE, SOLVED};
class Sudoku_solver
{
private:
	Domain_operation* domop;
	Solver_status solve(Board& board);
	Solver_status solve_sudoku(Board& board);
	bool refresh_domains(Board& board);
	void assign_value(Cell& cell, int val);
	void unassign_value(Cell& cell);
public:
	Sudoku_solver();
	~Sudoku_solver();
	void execute(Board& board);
};
