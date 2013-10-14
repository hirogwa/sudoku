// sudoku board
#ifndef BOARD_H_
#define BOARD_H_
#include <string>
#include <vector>
#include <set>
#include <math.h>
struct Cell
{
	bool given;
	bool blank;
	int number;
	int row;
	int col;
	std::set<int> domain;
};
class Board
{
private:
	static const int size = 9;
	static const int box_size = 3;

	Cell cells[size][size];
	int get_cell_int(std::string &cell_str);
	void setrow(int row, std::string line);
	void setrow(int row, std::vector<std::string> values);
	void print_row(int row, std::string delim, std::string wall);
	void print_wall(std::string wall);
	Cell get_given_cell(std::string str);
	std::set<Cell*> get_cells_of_row(Cell& cell);
	std::set<Cell*> get_cells_of_column(Cell& cell);
	std::set<Cell*> get_cells_of_box(Cell& cell);
public:
	Board(std::string infile); 
	int get_size();
	void print();
	Cell* get_blank_cell();
	std::vector<Cell*> get_cells();
	std::set<Cell*> get_constraining_cells(Cell& cell);
};
#endif
