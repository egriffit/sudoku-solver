#ifndef SUDOKUSOLVER_H_INCLUDED
#define SUDOKUSOLVER_H_INCLUDED

#include <vector>
#include <iostream>

#include "Board.h"

class SudokuSolver
{
    private:
        std::vector<bool> checker;  ///< tool for checking which numbers exist in a row
    
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
         * Get the checker array
         *
         * @return array of bools 
         */
        std::vector<bool> getChecker() const;

        /**
         * Set the checker array
         *
         * @param c array of bools to set the checker
         */
        void setChecker(const std::vector<bool>& c);

        /**
         * Reset the checker array to all false
         */
        void resetChecker();

        /**
         * Fill a row/column/block needing one more number
         *
         * @param n row/column/block number to fill
         * @param type determines whether this is a row('r'), column('c'), or block('b')
         */
        void solve8Full(int n, char type);

        /**
         * Search through the rows and columns to attempt to fill in a number
         *
         * @param b block number to analyze
         * @param toSearch number to attempt to place
         */
        void crossCheckBlock(int b, int toSearch);

        /**
         * Driver for all solving processes
         */
        void solveDriver();

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



};

#endif
