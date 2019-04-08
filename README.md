# Sudoku Solver

This program was designed to solve various sudoku puzzles. The implemented strategies include checking the blocks, rows, and columns to see if all but one space can be eliminated, allowing for placement of the target number. By employing these three methods alone, this sudoku solver can solve various easy and medium level problems. More advanced strategies may be implemented to solve more difficult problems in the future.

# Getting Started

In order to get started, download the zip file or tarball and unpack in the directory of your choice. 

## Prerequisites

g++ compiler(any version)

## Installing

Once the files are properly extracted, run make to build the exectuable.

The executable will be located in the bin/ directory and called sudoku-solver

# Running the Test Suite

Automated unit tests were compiled using the Catch2 testing suite. Run 'make test' to compile the executable, located in the bin/ directory and named tester. The tester can be run with no arguments to display which assertions and test cases passed. Command line arguments can be supplied. For more information, read the documentation for [Catch2](https://github.com/catchorg/Catch2).

# Running the Solver

The solver is run using one command line argument. The input file containing the unsolved puzzle must be supplied.

A sample command
```
bin/sudoku-solver unsolvedPuzzle.txt
```

## Input file format

This program accepts a command line argument detailing the file in which the unsolved puzzle is located. 

Structure the file with the following rules:

* Empty spaces are supplied with a -1
* Two parallel bars (||) separate each block by column
* Equals signs separate each block by row

An example
```
 -1  8 -1 || -1  9  4 || -1 -1 -1
 -1 -1  9 ||  1  7 -1 || -1 -1 -1
  4 -1  1 || -1 -1 -1 || -1 -1  3
 =================================
 -1 -1  8 || -1 -1 -1 || -1  2 -1
  5 -1 -1 ||  9  1  3 || -1 -1  8
 -1  9 -1 || -1 -1 -1 ||  4 -1 -1
 =================================
  3 -1 -1 || -1 -1 -1 ||  8 -1  6
 -1 -1 -1 || -1  5  8 ||  2 -1 -1
 -1 -1 -1 ||  2  3 -1 || -1  4 -1
```

# Documentation

Documentation is provided by [Doxygen](doxygen.nl). Documentation file is located at doc/html/index.html.

# Author

* **Edward Griffith** - [Github](https://github.com/egriffit)



