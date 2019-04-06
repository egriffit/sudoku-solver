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
    int emptyCell = -1;         // location of the empty cell
    std::vector<int> target;    // holds target construct to be filled


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
    Board oldBoard;

    while(!(this->board == oldBoard))
    {
        //keep track of the old board to track changes
        oldBoard = this->board;


        // cross check all missing numbers in all blocks
        for(int b = 0; b < 9; b++)
        {
            for(int i = 1; i < 10; i++)
            {
                /*
                std::cerr << "Searching for " << i << " in block " << b
                          << ": " << !(this->board.searchFor(b, i, 'b'))
                          << "\n";
                */

                if(!(this->board.searchFor(b, i, 'b')))
                    this->crossCheckBlock(b, i);
            }
        }


        // try to find rows/cols/blocks with 1 empty space
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

        //exit if board is full
        if(this->board.isFull())
            break;

        
        //std::cerr << "\n" << this->board << "\n";

    }

    if(!(this->board.isFull()))
        std::cout << this->board
                  << "\nUnfortunately we could not solve the board fully\n";
    else
        std::cout << this->board
                  << "\nBoard was solved successfully\n";

}

//----------------------------------------------------------------------------
void SudokuSolver::crossCheckBlock(int b, int toSearch)
{
    //exit function if the block already has the number
    /*std::cerr << "Searching for " << toSearch << " in block " << b << ": "
              << this->board.searchFor(b, toSearch, 'b') << "\n";
    */
    if(this->board.searchFor(b, toSearch, 'b'))
        return;

    std::vector<bool> availSpace(9, false);
    std::vector<int> block = this->board.getBlock(b);

    //find all empty block spaces
    for(int i = 0; i < 9; i++)
    {
        if(block[i] == -1)
            availSpace[i] = true;
    }


    //eliminate empty spaces by checking rows and columns
    int rowStart = (b / 3) * 3;
    int colStart = (b % 3) * 3;

    for(int i = rowStart; i < rowStart + 3; i++)
    {
        //check if that row of the block can be eliminated
        if(this->board.searchFor(i, toSearch, 'r'))
        {
            int toElim = i - rowStart;     // tracks row to be eliminated
            availSpace[(toElim * 3)] = false;
            availSpace[(toElim * 3) + 1] = false;
            availSpace[(toElim * 3) + 2] = false;
        }
    }

    for(int i = colStart; i < colStart + 3; i++)
    {
        //check if col of the block can be eliminated
        if(this->board.searchFor(i, toSearch, 'c'))
        {
            int toElim = i - colStart;
            availSpace[(toElim % 3)] = false;
            availSpace[(toElim % 3) + 3] = false;
            availSpace[(toElim % 3) + 6] = false;
        }
    }

    //check and see if there is one available space left
    bool found = false;
    int avail = -1;
    for(int i = 0; i < 9; i++)
    {
        if(availSpace[i])
        {
            //leave method if there is more than one available space
            if(found)
                return;
            
            found = true;
            avail = i;
        }
    }


    //set the number
    int row = (b / 3) * 3 + (avail / 3);
    int col = (b % 3) * 3 + (avail % 3);
    this->board.setCell(row, col, toSearch);
}
