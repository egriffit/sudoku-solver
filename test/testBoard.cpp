#include "catch.hpp"    // CATCH testing framework
#include "../src/Board.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

TEST_CASE("SudokuBoard constructors are called", "[constructor]")
{
    // a test board and default board
    std::vector<int> testBoard(81, 7);
    std::vector<int> defaultBoard(81, -1);
    
    
    // call each constructor
    Board A;            // Default Constructor
    Board B(testBoard); // Second Constructor
    Board C(B);         // Copy Constructor
    

    // Assertions
    REQUIRE( A.getBoard() == defaultBoard );
    REQUIRE( B.getBoard() == testBoard );
    REQUIRE( C == B );
}

TEST_CASE("Accessors are called", "[accessor]")
{
    // test board
    std::vector<int> testBoard(81, -1);

    // fill in cells with row count
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            testBoard[(i * 9) + j] = i;
    
    
    // row to be compared to
    std::vector<int> fifthRow(9, 4);

    // column to be compared to
    std::vector<int> fourthCol;
    for(int i = 0; i < 9; i++)
        fourthCol.push_back(i);

    // block to compare to
    std::vector<int> sixthBlock;
    for(int i = 3; i < 6; i++)
    {
        sixthBlock.push_back(i);
        sixthBlock.push_back(i);
        sixthBlock.push_back(i);
    }

    // Board
    Board A(testBoard);

    // Assertions
    REQUIRE( A.getRow(4) == fifthRow);
    REQUIRE( A.getCol(3) == fourthCol);
    REQUIRE( A.getCell(3, 3) == 3);
    REQUIRE( A.getBlock(5) == sixthBlock);
    
}

TEST_CASE("Mutators are called", "[mutator]")
{
    // test board
    std::vector<int> testBoard(81, -1);
    Board A(testBoard);
    
    // changed rows, cols, and cells
    std::vector<int> row(9, 4);
    std::vector<int> col(9, 6);
    std::vector<int> block(9, 9);

    // check getFilled = 0
    REQUIRE( A.getFilled() == 0);
    


    // check setCell()
    A.setCell(0, 0, 9);
    REQUIRE( A.getCell(0, 0) == 9 );
    
    // check setRow()
    A.setRow(5, row);
    REQUIRE( A.getRow(5) == row );
    
    // check setCol()
    A.setCol(8, col);
    REQUIRE( A.getCol(8) == col );
    
    // check setBlock()
    A.setBlock(6, block);
    REQUIRE( A.getBlock(6) == block);

    // check filled again
    REQUIRE( A.getFilled() == 27);

}

TEST_CASE("Check for the board being filled", "[fullboard]")
{
    // test board
    std::vector<int> testBoard(81, 9);
    Board A(testBoard);

    // check full
    REQUIRE( A.getFilled() == 81 );
    REQUIRE( A.getRowFilled(0) == 9 );
    REQUIRE( A.getColFilled(0) == 9 );
    REQUIRE( A.getRowEmpty(0) == 0 );
    REQUIRE( A.getColEmpty(0) == 0 );
    REQUIRE( A.isRowFull(0) == true );
    REQUIRE( A.isColFull(0) == true );
    REQUIRE( A.isFull() == true );

    // change one value to empty
    A.setCell(0, 0, -1);

    // check for change
    REQUIRE( A.getFilled() == 80 );
    REQUIRE( A.getRowFilled(0) == 8 );
    REQUIRE( A.getColFilled(0) == 8 );
    REQUIRE( A.getRowEmpty(0) == 1 );
    REQUIRE( A.getColEmpty(0) == 1 );
    REQUIRE( A.isRowFull(0) == false );
    REQUIRE( A.isColFull(0) == false );
    REQUIRE( A.isFull() == false );
}

TEST_CASE("Comparison operators are called", "[compare]")
{
    Board A;
    Board B;
    

    // boards should be equal
    REQUIRE( B == A );

    A.setCell(0, 0, 9);
    B.setCell(0, 0, 9);

    REQUIRE( B == A );
    REQUIRE( (B < A) == false );
    REQUIRE( (A < B) == false );

    B.setCell(1, 1, 9);

    REQUIRE( (B == A) == false );
    REQUIRE( (A < B) == true );
    REQUIRE( (B < A) == false );
}

TEST_CASE("Assignment operator is used", "[assignment]")
{
    // test board
    std::vector<int> testBoard;
    for(int i = 0; i < 81; i++)
        testBoard.push_back(i);

    Board A(testBoard);
    Board B = A;

    REQUIRE( A == B );

}

TEST_CASE("Searches for numbers is called", "[search]")
{
    std::vector<int> testBoard(81, -1);
    testBoard[6] = 3;
    testBoard[44] = 2;
    Board test(testBoard);
    

    // search a row
    REQUIRE( test.searchFor(0, 3, 'r') == true );
    REQUIRE( test.searchFor(0, 2, 'r') == false );
    REQUIRE( test.searchFor(4, 2, 'r') == true );

    // search columns
    REQUIRE( test.searchFor(6, 3, 'c') == true );
    REQUIRE( test.searchFor(3, 6, 'c') == false );
    REQUIRE( test.searchFor(8, 2, 'c') == true );

    
    // search blocks
    REQUIRE( test.searchFor(2, 3, 'b') == true );
    REQUIRE( test.searchFor(3, 5, 'b') == false );
    REQUIRE( test.searchFor(5, 2, 'b') == true );
}

TEST_CASE("Read function is called", "[read]")
{
    std::vector<int> testBoard(81, 7);
    Board A(testBoard);

    std::ifstream inf;
    inf.open("test/testRead.txt");

    Board B;
    inf >> B;

    REQUIRE( B == A );
}
