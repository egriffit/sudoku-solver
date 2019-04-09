#ifndef SUDOKUSOLVER_H_INCLUDED
#define SUDOKUSOLVER_H_INCLUDED

#include <vector>
#include <iostream>

#include "Board.h"

/**
 * This class contains all methods focused on solving the sudoku board
 */
class SudokuSolver
{    
    public:
        Board board;                ///< Board that will be solved

        /**
         * Default Constructor
         */
        SudokuSolver();

        /**
         * Constructor if board is already known
         *
         * @param b board to be initialized
         */
        SudokuSolver(const Board& b);

        /**
         * Copy Constructor
         *
         * @param src SudokuSolver object to be copied
         */
        SudokuSolver(const SudokuSolver& src);

        /**
         * Destructor
         */
        ~SudokuSolver();
        
        /**
         * Search through the rows and columns to attempt to fill in a number
         *
         * @param b block number to analyze
         * @param toSearch number to attempt to place
         */
        void crossCheckBlock(int b, int toSearch);

        /**
         * Search through the blocks and columns to attempt to fill in a number in a row
         *
         * @param r row number to analyze
         * @param toSearch number to attempt to place
         */
        void crossCheckRow(int r, int toSearch);
        
        /**
         * Search through the blocks and rows to attempt to fill in a number in a column
         *
         * @param c column number to analyze
         * @param toSearch number to attempt to place
         */
        void crossCheckCol(int c, int toSearch);

        /**
         * Driver for all solving processes
         *
         * @return true if the board is solved successfully
         */
        bool solveDriver();

        /**
         * Overloaded Logical Equivalence Operator
         *
         * @param rhs Right Hand Side object of the comparison
         *
         * @return true if the boards are identical
         */
        bool operator==(const SudokuSolver& rhs) const;

        /**
         * Overloaded Less Than Operator
         *
         * @param rhs Right Hand Side object of the comparison
         *
         * @return true if the lhs board has less filled in
         */
        bool operator<(const SudokuSolver& rhs) const;

        /**
         * Display function
         *
         * @param outs output stream
         */
        void display(std::ostream& outs) const;


};

/** \relates SudokuSolver
 * Overloaded Stream Insertion Operator
 *
 * @param outs output stream
 * @param prt object to be printed
 *
 * @return output stream
 */
inline
std::ostream& operator<<(std::ostream& outs, const SudokuSolver& prt)
{
    prt.display(outs);

    return outs;
}

/** \relates SudokuSolver
 * Overloaed Stream Extraction Operator
 *
 * @param ins input stream
 * @param obj object to be read
 *
 * @return input stream
 */
inline
std::istream& operator>>(std::istream& ins, SudokuSolver& obj)
{
    ins >> obj.board;

    return ins;
}
#endif
