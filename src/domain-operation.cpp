// domain-operator.
// responsible for managing domains of the variables. (ie. cells)
#include <iostream>
#include "domain-operation.h"
Domain_status Domain_operation::reflect_constraints(Cell& cell, std::set<Cell*>* cells)
{
	if (cell.blank)
		return DOM_SUCCESS;

	for (std::set<Cell*>::iterator it = cells->begin(); it != cells->end(); ++it)
	{
		((*it)->domain).erase(cell.number);
		if (((*it)->domain).size() < 1)
		{
			return DOM_FAILURE;
		}
	}
	return DOM_SUCCESS;
}
void Domain_operation::reset_domains(Board& board)
{
	std::vector<Cell*> cells = board.get_cells();
	for (int i = 0; i < (int)cells.size(); ++i)
	{
		Cell* cell = cells.at(i);
		if (cell->given)
		{
			(cell->domain).insert(cell->number);
		}
		else
		{
			set_full_domain(board.get_size(), *cell);
		}
	}
}
void Domain_operation::set_full_domain(int size, Cell& cell)
{
	for (int i = 0; i < size; ++i)
	{
		(cell.domain).insert(i + 1);
	}
}
Domain_status Domain_operation::refresh_domains(Board& board)
{
	reset_domains(board);
	std::vector<Cell*> cells = board.get_cells();
	for (int i = 0; i < (int)cells.size(); ++i)
	{
		Cell* cell = cells.at(i);
		if (update_domain(board, *cell) == DOM_FAILURE)
			return DOM_FAILURE;
	}
	return DOM_SUCCESS;
}
Domain_status Domain_operation::update_domains(Board& board, Cell& triggering_cell)
{
	std::set<Cell*> cells = board.get_constraining_cells(triggering_cell);
	for (std::set<Cell*>::iterator it = cells.begin(); it != cells.end(); ++it)
	{
		if (update_domain(board, *(*it)) == DOM_FAILURE)
			return DOM_FAILURE;
	}
	return DOM_SUCCESS;
}
Domain_status Domain_operation::update_domain(Board& board, Cell& cell)
{
	// start from full
	set_full_domain(board.get_size(), cell);
	// discard all no-good values
	std::set<Cell*> cells = board.get_constraining_cells(cell);
	for (std::set<Cell*>::iterator it = cells.begin(); it != cells.end(); ++it)
	{
		if ((*it)->blank)
			continue;
		cell.domain.erase((*it)->number);
	}
	if (cell.domain.empty())
		return DOM_FAILURE;
	else
		return DOM_SUCCESS;
}
