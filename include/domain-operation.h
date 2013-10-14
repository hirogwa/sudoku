// domain-operator.
// responsible for managing domains of the variables. (ie. cells)
#include "board.h"
#include <set>
enum Domain_status {DOM_FAILURE, DOM_SUCCESS};
class Domain_operation
{
private:
	void reset_domains(Board& board);
	void set_full_domain(int size, Cell& cell);
	Domain_status update_domain(Board& board, Cell& cell);
	Domain_status reflect_constraints(Cell& cell, std::set<Cell*>* cells);
public:
	Domain_status refresh_domains(Board& board);
	Domain_status update_domains(Board& board, Cell& triggering_cell);
};
