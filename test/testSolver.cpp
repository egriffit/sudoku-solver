#include "catch.hpp"    //CATCH testing framework
#include "../src/SudokuSolver.h"
#include "../src/Board.h"
#include <cstdlib>
#include <iostream>



TEST_CASE("SudokuSolver constructors are called", "[constructor]")
{
    
    //default
    SudokuSolver A; 
    std::vector<bool> c(9, false);

    REQUIRE( A.board.getFilled() == 0 );
    REQUIRE( A.getChecker() == c );
    
    
    //alternate constructor
    std::vector<int> testBoard(81, 0);
    Board test(testBoard);  
    SudokuSolver B(test);
    REQUIRE( B.board == test );


    //copy constructor
    SudokuSolver C(B);
    REQUIRE( C == B );
    
}

TEST_CASE("SudokuSolver accessors are called", "[accessor]")
{
    SudokuSolver A;
    std::vector<bool> c(9, false);

    REQUIRE( A.getChecker() == c );
}

TEST_CASE("SudokuSolver mutators are called", "[mutator]")
{
    SudokuSolver A;
    std::vector<bool> newChecker(9, true);
    std::vector<bool> allFalse(9, false);


    //set checker
    A.setChecker(newChecker);
    REQUIRE( A.getChecker() == newChecker );


    //reset checker
    A.resetChecker();
    REQUIRE( A.getChecker() == allFalse );
}

TEST_CASE("Solve a row/column/block with 1 empty space", "[solving]")
{
    std::vector<int> test(9, -1);
    for(int i = 0; i < 9; i++)
        test[i] = i + 1;
    std::vector<int> solvedTest = test;
    test[5] = -1;


    //solve row
    SudokuSolver A;
    A.board.setRow(3, test);
        
    A.solve8Full(3, 'r');
    REQUIRE( A.board.getRow(3) == solvedTest );


    //solve column
    SudokuSolver B;
    B.board.setCol(2, test);

    B.solve8Full(2, 'c');
    REQUIRE( B.board.getCol(2) == solvedTest );


    //solve block
    SudokuSolver C;
    C.board.setBlock(8, test);

    C.solve8Full(8, 'b');
    REQUIRE( C.board.getBlock(8) == solvedTest );
}

TEST_CASE("Cross checker algorithms are called", "[solving]")
{
    // Block test
    SudokuSolver A;

    
    //test that the algorithm writes if theres only one possible space
    A.board.setCell(3, 1, 3);
    A.board.setCell(7, 2, 3);
    A.board.setCell(1, 5, 3);
    A.board.setCell(2, 8, 3);

    A.crossCheckBlock(0, 3);

    REQUIRE( A.board.getCell(0, 0) == 3 );


    //test that algorithm does not write if there are two empty spaces
    A.board.setCell(0, 0, -1);
    A.board.setCell(2, 8, -1);

    SudokuSolver pre(A);
    A.crossCheckBlock(0, 3);

    REQUIRE( A == pre );

    
    
    
    // Row test
    SudokuSolver B;


    // test that the algorithm does not write if there are multiple empty spaces
    B.board.setCell(0, 1, 3);
    B.board.setCell(1, 7, 3);
    B.board.setCell(5, 5, 3);
    pre = B;

    B.crossCheckCol(2, 3);

    REQUIRE( B == pre );

    //test that the algirthm does write if there is one empty space
    B.board.setCell(8, 3, 3);
    
    B.crossCheckRow(2, 3);

    REQUIRE( B.board.getCell(2, 4) == 3 );



    // Column test
    SudokuSolver C;


    //test that the algorithm won't write with multiple empty spaces
    C.board.setCell(3, 1, 3);
    C.board.setCell(6, 2, 3);
    C.board.setCell(1, 3, 3);
    pre = C;

    C.crossCheckCol(0, 3);

    REQUIRE( C == pre );


    // test that the algorithm writes with one empty space
    C.board.setCell(2, 6, 3);

    C.crossCheckCol(0, 3);

    REQUIRE( C.board.getCell(0, 0) == 3 );

}
TEST_CASE("Driver for the solver is called", "[solving]")
{
    std::vector<int> testBoard = {4, 2, 3, 6, 9, 7, 8, 1, 5,
                                  6, 9, 1, 5, 3, 8, 4, 7, 2,
                                  5, 8, 7, 4, 2, 1, 6, 3, 9,
                                  3, 1, 9, 8, 7, 5, 2, 6, 4,
                                  2, 5, 6, 1, 4, 9, 3, 8, 7,
                                  7, 4, 8, 3, 6, 2, 5, 9, 1,
                                  9, 6, 4, 2, 1, 3, 7, 5, 8,
                                  1, 3, 5, 7, 8, 4, 9, 2, 6,
                                  8, 7, 2, 9, 5, 6, 1, 4, 3};
    
    std::vector<int> solvedBoard = testBoard;

    //remove certain values of the board
    testBoard[6] = -1;
    testBoard[55] = -1;
    testBoard[23] = -1;

    Board tester(testBoard);
    Board solved(solvedBoard);


    SudokuSolver A(tester);
    A.solveDriver();
    
    REQUIRE( A.board == solved );


    //more robust test case
    std::vector<int> boardA =
                {-1,  4, -1, -1,  9, -1, -1,  3, -1,
                  7,  3, -1,  1,  4, -1, -1,  9, -1,
                 -1, -1,  8,  2, -1,  5, -1, -1,  1,
                  3, -1,  7, -1, -1, -1, -1, -1, -1,
                 -1,  5,  9,  4,  8,  3,  7,  2, -1,
                 -1, -1, -1, -1, -1, -1,  9, -1,  3,
                  5, -1, -1,  8, -1,  9,  3, -1, -1,
                 -1,  2, -1, -1,  7,  1, -1,  6,  5,
                 -1,  7, -1, -1,  5, -1, -1,  1, -1};
    
    std::vector<int> boardASolved =
                {2, 4, 1, 7, 9, 6, 5, 3, 8,
                 7, 3, 5, 1, 4, 8, 6, 9, 2,
                 6, 9, 8, 2, 3, 5, 4, 7, 1,
                 3, 8, 7, 9, 6, 2, 1, 5, 4,
                 1, 5, 9, 4, 8, 3, 7, 2, 6,
                 4, 6, 2, 5, 1, 7, 9, 8, 3,
                 5, 1, 6, 8, 2, 9, 3, 4, 7,
                 9, 2, 4, 3, 7, 1, 8, 6, 5,
                 8, 7, 3, 6, 5, 4, 2, 1, 9};

    Board testA(boardA);
    Board solvedA(boardASolved);
    SudokuSolver B(testA);
    SudokuSolver C(solvedA);

    B.solveDriver();

    REQUIRE( B == C );

}

