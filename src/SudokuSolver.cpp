#include <iostream>

#include "SudokuSolver.h"

//----------------------------------------------------------------------------
SudokuSolver::SudokuSolver()
{
	
	//board constructor takes care of board
	
	//set all checker values to false
	checker.assign(9, false);
}

//----------------------------------------------------------------------------
SudokuSolver::SudokuSolver(const Board& b)
{
	this->board = b;
	checker.assign(9, false);
}

//----------------------------------------------------------------------------
SudokuSolver::SudokuSolver(const SudokuSolver& src)
{
	//use copy constructor of Board class
	this->board = src.board;

	//vector class ensures deep copy
	this->checker = src.getChecker();
}

//----------------------------------------------------------------------------
SudokuSolver::~SudokuSolver()
{
	//vector handles deallocation
}

//----------------------------------------------------------------------------
std::vector<bool> SudokuSolver::getChecker() const
{
	return this->checker;
}

//----------------------------------------------------------------------------
void SudokuSolver::setChecker(const std::vector<bool>& c)
{
	this->checker = c;
}

//----------------------------------------------------------------------------
void SudokuSolver::resetChecker()
{
	std::vector<bool> allFalse(9, false);

	this->checker = allFalse;
}

//----------------------------------------------------------------------------
void SudokuSolver::solve8Full(int n, char type)
{
	int emptyCell = -1;			// location of the empty cell
	std::vector<int> target;	// holds target construct to be filled


	if(type == 'r')
		target = this->board.getRow(n);
	else if(type == 'c')
		target = this->board.getCol(n);
	else if(type == 'b')
		target = this->board.getBlock(n);


	/*
	std::cerr << "Target(before): ";
	for(int i = 0; i < 9; i++)
		std::cerr << target[i];
	std::cerr << "\n";
	*/


	// set the appropriate checker values
	// and find the empty one
	for(int i = 0; i < 9; i++)
	{
		// means nonempty
		if(target[i] != -1)
			checker[target[i] - 1] = true;
		
		// tag the empty one for replacement
		else
			emptyCell = i;
	}



	// find and set the empty cell to the missing number
	for(int i = 0; i < 9; i++)
	{
		//if the number is missing, put that number in the empty cell
		//must add 1 because values must be 1-9
		if(!checker[i])
		{
			target[emptyCell] = i + 1;
			break;
		}
	}

	
	/*
	std::cerr << "Target(after): ";
	for(int i = 0; i < 9; i++)
		std::cerr << target[i];
	std::cerr << "\n";
	*/


	//set the appropriate construct
	if(type == 'r')
		this->board.setRow(n, target);
	else if(type == 'c')
		this->board.setCol(n, target);
	else if(type == 'b')
		this->board.setBlock(n, target);

	//reset checker for next use
	this->resetChecker();

}

//----------------------------------------------------------------------------
bool SudokuSolver::operator==(const SudokuSolver& rhs) const
{
	return this->board == rhs.board;
}

//----------------------------------------------------------------------------
bool SudokuSolver::operator<(const SudokuSolver& rhs) const
{
	return this->board < rhs.board;
}

//----------------------------------------------------------------------------
void SudokuSolver::solveDriver()
{
	while(!(this->board.isFull()))
	{
		//try to find rows/cols/blocks with 1 empty space
		for(int i = 0; i < 9; i++)
		{
			/*
			std::cerr << "Pass(before) " << i << ": "
					  << "Row-" << this->board.getRowEmpty(i) << ": "
					  << "Col-" << this->board.getColEmpty(i) << ": "
					  << "Blo-" << this->board.getBlockEmpty(i) << "\n";
			*/


			if(this->board.getRowEmpty(i) == 1)
			{
				//std::cerr << "Row solver for " << i << "reached\n";
				this->solve8Full(i, 'r');
			}

			if(this->board.getColEmpty(i) == 1)
			{
				//std::cerr << "Column solver for " << i << "reached\n";
				this->solve8Full(i, 'c');
			}

			if(this->board.getBlockEmpty(i) == 1)
			{
				//std::cerr << "Block solver for " << i << "reached\n";
				this->solve8Full(i, 'b');
			}
			

			/*
			std::cerr << "Pass(after) " << i << ": "
					  << "Row-" << this->board.getRowEmpty(i) << ": "
					  << "Col-" << this->board.getColEmpty(i) << ": "
					  << "Blo-" << this->board.getBlockEmpty(i) << "\n";
			*/
		}
	}
}
