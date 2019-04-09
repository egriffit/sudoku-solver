#include <iostream>

#include "SudokuSolver.h"

//----------------------------------------------------------------------------
SudokuSolver::SudokuSolver()
{
    
    // board constructor takes care of board
}

//----------------------------------------------------------------------------
SudokuSolver::SudokuSolver(const Board& b)
{
    this->board = b;
}

//----------------------------------------------------------------------------
SudokuSolver::SudokuSolver(const SudokuSolver& src)
{
    // use copy constructor of Board class
    this->board = src.board;
}

//----------------------------------------------------------------------------
SudokuSolver::~SudokuSolver()
{
    // vector handles deallocation
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
bool SudokuSolver::solveDriver()
{
    Board oldBoard;

    while(!(this->board == oldBoard))
    {
        // keep track of the old board to track changes
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

        

        // cross check all missing numbers in rows
        for(int r = 0; r < 9; r++)
        {
            for(int i = 1; i < 10; i++)
            {
                if(!(this->board.searchFor(r, i, 'r')))
                    this->crossCheckRow(r, i);
            }
        }



        
        // cross check all missing numbers in columns
        for(int c = 0; c < 9; c++)
        {
            for(int i = 1; i < 10; i++)
            {
                if(!(this->board.searchFor(c, i, 'c')))
                    this->crossCheckCol(c, i);
            }
        }


       

        
        // std::cerr << "\n" << this->board << "\n";

    }

    if(!(this->board.isFull()))
        return false;
    else
        return true;

}

//----------------------------------------------------------------------------
void SudokuSolver::crossCheckBlock(int b, int toSearch)
{
    // exit function if the block already has the number
    /*std::cerr << "Searching for " << toSearch << " in block " << b << ": "
              << this->board.searchFor(b, toSearch, 'b') << "\n";
    */
    if(this->board.searchFor(b, toSearch, 'b'))
        return;

    std::vector<bool> availSpace(9, false);
    std::vector<int> block = this->board.getBlock(b);

    // find all empty block spaces
    for(int i = 0; i < 9; i++)
    {
        if(block[i] == -1)
            availSpace[i] = true;
    }


    // eliminate empty spaces by checking rows and columns
    int rowStart = (b / 3) * 3;
    int colStart = (b % 3) * 3;

    for(int i = rowStart; i < rowStart + 3; i++)
    {
        // check if that row of the block can be eliminated
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
        // check if col of the block can be eliminated
        if(this->board.searchFor(i, toSearch, 'c'))
        {
            int toElim = i - colStart;
            availSpace[(toElim % 3)] = false;
            availSpace[(toElim % 3) + 3] = false;
            availSpace[(toElim % 3) + 6] = false;
        }
    }

    // check and see if there is one available space left
    bool found = false;
    int avail = -1;
    for(int i = 0; i < 9; i++)
    {
        if(availSpace[i])
        {
            // leave method if there is more than one available space
            if(found)
                return;
            
            found = true;
            avail = i;
        }
    }


    // set the number
    int row = (b / 3) * 3 + (avail / 3);
    int col = (b % 3) * 3 + (avail % 3);
    this->board.setCell(row, col, toSearch);
}

//----------------------------------------------------------------------------
void SudokuSolver::crossCheckRow(int r, int toSearch)
{
    // exit function if the number already exists
    if(this->board.searchFor(r, toSearch, 'r'))
        return;

    std::vector<bool> availSpace(9, false);
    std::vector<int> row = this->board.getRow(r);

    // if the cell is empty, add it to availability
    for(int i = 0; i < 9; i++)
    {
        if(row[i] == -1)
            availSpace[i] = true;
    }

       

    // eliminate free space based on the blocks
    int blockStart = (r / 3) * 3;       // finds the starting of the 3 blocks
    
    // std::cerr << blockStart << "\n";

    for(int i = blockStart; i < blockStart + 3; i++)
    {
        if(this->board.searchFor(i, toSearch, 'b'))
        {
            int blockNum = i - blockStart;      // block num 1, 2, or 3

            availSpace[(3 * blockNum)] = false;     // if block is 0
            availSpace[(3 * blockNum) + 1] = false; // these will be
            availSpace[(3 * blockNum) + 2] = false; // 0, 1, 2
        }
    }


    /*
    for(bool cell: availSpace)
        std::cerr << cell;
    std::cerr << std::endl;
    */


    // eliminate free space based on columns
    for(int i = 0; i < 9; i++)
    {
        if(this->board.searchFor(i, toSearch, 'c'))
        {
            availSpace[i] = false;
        }
    }

    


    // see if there is only one available space
    bool found = false;
    int avail = -1;

    for(int i = 0; i < 9; i++)
    {
        if(availSpace[i])
        {
            // leave method if more than one available space
            if(found)
                return;
            
            found = true;
            avail = i;
        }
    }

    


    // set the value in the correct cell
    this->board.setCell(r, avail, toSearch);

}

//----------------------------------------------------------------------------
void SudokuSolver::crossCheckCol(int c, int toSearch)
{
    // exit if the number already exists in the column
    if(this->board.searchFor(c, toSearch, 'c'))
        return;


    std::vector<bool> availSpace(9, false);
    std::vector<int> col = this->board.getCol(c);


    // set empty spaces to available
    for(int i = 0; i < 9; i++)
    {
        if(col[i] == -1)
            availSpace[i] = true;
    }


    // search through the blocks to eliminate spaces
    int blockStart = c / 3;
    for(int i = blockStart; i <= blockStart + 6; i += 3)
    {
        // eliminate column spaces in that block
        if(this->board.searchFor(i, toSearch, 'b'))
        {
            int blockNum = (i - blockStart) / 3;    // first, second, or third

            availSpace[(blockNum * 3)] = false;
            availSpace[(blockNum * 3) + 1] = false;
            availSpace[(blockNum * 3) + 2] = false;
        }
    }



    // search through the rows to eliminate spaces
    for(int i = 0; i < 9; i++)
    {
        if(this->board.searchFor(i, toSearch, 'r'))
        {
            availSpace[i] = false;
        }
    }


    // exit if there is more than one empty space
    bool found = false;
    int avail = -1;
    for(int i = 0; i < 9; i++)
    {
        if(availSpace[i])
        {
            // exit if already one space found
            if(found)
                return;


            found = true;
            avail = i;
        }
    }


    // set the value
    this->board.setCell(avail, c, toSearch);

}

//----------------------------------------------------------------------------
void SudokuSolver::display(std::ostream& outs) const
{
    outs << this->board;
}
