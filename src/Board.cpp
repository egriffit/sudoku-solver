#include <iostream>
#include <utility>
#include <vector>

#include "Board.h"

//----------------------------------------------------------------------------
Board::Board()
{
    // initialize all values of the board to -1 to symbolize empty
    board.assign(81, -1);
}

//----------------------------------------------------------------------------
Board::Board(const std::vector<int>& b)
{
    // reserve memory
    board.reserve(81);
        
    // vector handles deep copy
    board = b;
}

//----------------------------------------------------------------------------
Board::Board(const Board& src)
{
    // reserve memory
    board.reserve(81);

    // vector handles deep copy
    board = src.board;
}

//----------------------------------------------------------------------------
Board::~Board()
{
    // vector handles deallocation
}

//----------------------------------------------------------------------------
std::vector<int> Board::getRow(int n) const
{
    std::vector<int> row;

    for(int i = 0; i < 9; i++)
        row.push_back(this->board[(n * 9) + i]);

    return row;
}

//----------------------------------------------------------------------------
std::vector<int> Board::getCol(int n) const
{
    std::vector<int> col;

    for(int i = 0; i < 9; i++)
        col.push_back(this->board[(i * 9) + n]);

    return col;
}

//----------------------------------------------------------------------------
std::vector<int> Board::getBlock(int n) const
{
    std::vector<int> block;

    // starting row and column of block
    int r = (n / 3) * 3;
    int c = (n % 3) * 3;
        
    // std::cerr << "Block " << n << ": " << r << ", " << c << "\n";

    for(int i = r; i < r + 3; i++)
    {
        for(int j = c; j < c + 3; j++)
        {
                block.push_back(this->board[(i * 9) + j]);
        }
    }

    return block;
}

//----------------------------------------------------------------------------
std::vector<int> Board::getBoard() const
{
    return this->board;
}

//----------------------------------------------------------------------------
int Board::getCell(int r, int c) const
{
    return this->board[(r * 9) + c];
}

//----------------------------------------------------------------------------
int Board::getFilled() const
{
    int count = 0;

    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            if(this->board[(i * 9) + j] != -1)
                count++;
        }

    return count;
}

//----------------------------------------------------------------------------
int Board::getRowFilled(int r) const
{
    int count = 0;

    for(int i = 0; i < 9; i++)
    {
        if(this->board[(r * 9) + i] != -1)
            count++;
    }

    return count;
}

//----------------------------------------------------------------------------
int Board::getColFilled(int c) const
{
    int count = 0;

    for(int i = 0; i < 9; i++)
    {
        if(this->board[(i * 9) + c] != -1)
            count++;
    }

    return count;
}

//----------------------------------------------------------------------------
int Board::getBlockFilled(int b) const
{
    int count = 0;


    std::vector<int> block = this->getBlock(b);

    for(int i = 0; i < 9; i++)
    {
        if(block[i] != -1)
            count++;
    }

    return count;
}

//----------------------------------------------------------------------------
int Board::getRowEmpty(int r) const
{
    return 9 - this->getRowFilled(r);
}

//----------------------------------------------------------------------------
int Board::getColEmpty(int c) const
{
    return 9 - this->getColFilled(c);
}

//----------------------------------------------------------------------------
int Board::getBlockEmpty(int b) const
{
    return 9 - this->getBlockFilled(b);
}

//----------------------------------------------------------------------------
void Board::setRow(int n, const std::vector<int>& row)
{
    for(int i = 0; i < 9; i++)
        this->board[(n * 9) + i] = row[i];
}

//----------------------------------------------------------------------------
void Board::setCol(int n, const std::vector<int>& col)
{
    for(int i = 0; i < 9; i++)
        this->board[(i * 9) + n] = col[i];
}

//----------------------------------------------------------------------------
void Board::setCell(int r, int c, int val)
{
    this->board[(r * 9) + c] = val;
}

//----------------------------------------------------------------------------
void Board::setBlock(int n, const std::vector<int>& b)
{
    int r = (n / 3) * 3;
    int c = (n % 3) * 3;
    int count = 0;

    for(int i = r; i < r + 3; i++)
    {
        for(int j = c; j < c + 3; j++)
        {
            this->board[(i * 9) + j] = b[count];
            count++;
        }
    }
}

//----------------------------------------------------------------------------
void Board::setBoard(const std::vector<int>& newBoard)
{
    this->board = newBoard;
}

//----------------------------------------------------------------------------
bool Board::isFull() const
{
    return this->getFilled() == 81;
}

//----------------------------------------------------------------------------
bool Board::isRowFull(int r) const
{
    return this->getRowFilled(r) == 9;
}

//----------------------------------------------------------------------------
bool Board::isColFull(int c) const
{
    return this->getColFilled(c) == 9;
}

//----------------------------------------------------------------------------
Board Board::operator=(const Board& src)
{
    this->board = src.getBoard();
        
    return *this;
}

//----------------------------------------------------------------------------
bool Board::operator<(const Board& lhs) const
{
    return this->getFilled() < lhs.getFilled();
}

//----------------------------------------------------------------------------
bool Board::operator==(const Board& lhs) const
{
    return this->board == lhs.getBoard();
}

//----------------------------------------------------------------------------
void Board::display(std::ostream& outs) const
{
    for(int i = 0; i < 9; i++)
    {
        outs << " ";

        for(int j = 0; j < 9; j++)
        {
            // print 3 nums and then a separator
            if(j == 3 || j == 6)
                outs << "|| ";

                        
            // print space if the board is empty there
            if(this->board[(i * 9) + j] == -1)
                outs << " ";
            else
                outs << this->board[(i * 9) + j];

            // print a separating space
            if(j != 8)
                outs << " ";
                        
        }
                
            outs << "\n";

            // dividing line between grids
            if(i == 2 || i == 5)
            {
                std::string divide(24, '=');
                outs << divide << "\n";
            }
                

    }
}

//----------------------------------------------------------------------------
void Board::read(std::istream& ins)
{
    char dump;
    std::string dividers;

    for(int i = 0; i < 9; i++)    
    {    
        // remove dividers
        if(i == 3 || i == 6)
            ins >> dividers;


        for(int j = 0; j < 9; j++)
        {
            // remove dividers
            if(j == 3 || j == 6)
                ins >> dump >> dump;

            ins >> this->board[(i * 9) + j];

            // std::cerr << this->board[(i * 9) + j] << std::endl;
        }
    }
}

//----------------------------------------------------------------------------
bool Board::searchFor(int n, int toSearch, char type) const
{
    std::vector<int> target;

    if(type == 'r')
        target = this->getRow(n);
    if(type == 'c')
        target = this->getCol(n);
    if(type == 'b')
        target = this->getBlock(n);

    for(int cell: target)
    {
        if(cell == toSearch)
            return true;
    }

    return false;
}

