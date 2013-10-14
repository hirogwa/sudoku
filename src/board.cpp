// board.cpp; sudoku board. implementation.
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include "board.h"
#include "utils.h"
using namespace std;
Board::Board(std::string infile)
{
	ifstream fin(infile.c_str());
	string line;
	int row = -1;
	while (getline(fin, line) && row < size)
	{
		setrow(++row, line);
	}
	fin.close();
}
void Board::setrow(int row, std::string line)
{
	vector<std::string> values = strutils::split(line, ',');
	setrow(row, values);
}
void Board::setrow(int row, std::vector<std::string> values)
{
	for (int i = 0; i < size; ++i)
	{
		this->cells[row][i] = get_given_cell(values.at(i));
		this->cells[row][i].row = row;
		this->cells[row][i].col = i;
	}
}
Cell Board::get_given_cell(std::string str)
{
	int val = get_cell_int(str);
	bool given = (val != 0);
	bool blank = !given;
	Cell cell = {given, blank, val};
	return cell;
}
int Board::get_cell_int(std::string &cell_str)
{
	// check type
	if (strutils::is_digit_only(cell_str))
	{
		int number = atoi(cell_str.c_str());
		// check range
		if (0 < number && number < 10)
			return number;
		else
			return 0;
	}
	else
		return 0;
}
void Board::print()
{
	print_wall("*");
	for (int i = 0; i < size; ++i)
	{	
		print_row(i, " ", "*");
	}
	print_wall("*");
}
void Board::print_wall(std::string wall)
{
	for (int i = 0; i < size * 2 + 1; ++i)
	{
		cout << wall;
	}
	cout << endl;
}
void Board::print_row(int row, std::string delim, std::string wall)
{
	cout << wall;
	for (int i = 0; i < size; ++i)
	{
		if (i != 0)
			cout << delim;
		Cell cell = this->cells[row][i];
		if (cell.blank)
			cout << "X";
		else
			cout << cell.number;
	}
	cout << wall << endl;
}
Cell* Board::get_blank_cell()
{
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			if (cells[row][col].blank)
				return &cells[row][col];
		}
	}
	return NULL;
}
std::set<Cell*> Board::get_cells_of_row(Cell& cell)
{
	std::set<Cell*> cell_set;
	for (int i = 0; i < size; ++i)
	{
		if (i == cell.col)
			continue;
		cell_set.insert(&cells[cell.row][i]);
	}
	return cell_set;
}
std::set<Cell*> Board::get_cells_of_column(Cell& cell)
{
	std::set<Cell*> cell_set;
	for (int i = 0; i < size; ++i)
	{
		if (i == cell.row)
			continue;
		cell_set.insert(&cells[i][cell.col]);
	}
	return cell_set;
}
std::set<Cell*> Board::get_cells_of_box(Cell& cell)
{
	int r_min = (cell.row / box_size) * box_size;
	int c_min = (cell.col / box_size) * box_size;
	std::set<Cell*> cell_set;
	for (int i = r_min; i < r_min + box_size; ++i)
	{
		for (int j = c_min; j < c_min + box_size; ++j)
		{
			if (i == cell.row && j == cell.col)
				continue;
			cell_set.insert(&cells[i][j]);
		}
	}
	return cell_set;
}
std::vector<Cell*> Board::get_cells()
{
	std::vector<Cell*> cell_vector;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cell_vector.push_back(&cells[i][j]);
		}
	}
	return cell_vector;
}
int Board::get_size()
{
	return size;
}
std::set<Cell*> Board::get_constraining_cells(Cell& cell)
{
	std::set<Cell*> cells;
	// row
	std::set<Cell*> cells_r = get_cells_of_row(cell);
	cells.insert(cells_r.begin(), cells_r.end());
	// column
	std::set<Cell*> cells_c = get_cells_of_column(cell);
	cells.insert(cells_c.begin(), cells_c.end());
	// box
	std::set<Cell*> cells_b = get_cells_of_box(cell);
	cells.insert(cells_b.begin(), cells_b.end());
	return cells;
}
