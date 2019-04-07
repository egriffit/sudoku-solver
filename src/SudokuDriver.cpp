#include <iostream>
#include <fstream>

#include "SudokuSolver.h"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: bin/sudoku-solver [input file]" << std::endl;
        return -1;
    }

    std::ifstream inf;
    inf.open(argv[1]);

    SudokuSolver grid;
    inf >> grid.board;

    
    if(grid.solveDriver())
    {
        std::cout << "\nSuccessfully solved:\n"
                  << grid.board << std::endl;
    }
    else
    {
        std::cout << "\nUnsuccessfully solved...\n"
                  << grid.board << std::endl;
    }

    return 0;
}
