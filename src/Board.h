#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


/**
 * The Board class holds the sudoku board interfaced with by the solver.
 */
class Board
{
    private:
        std::vector<int> board;     ///< Container holding items linearly
                                    ///< Empty spaces will be fill with -1
    
    public:
        /**
         * Default Board Constructor
         */
        Board();
        
        /**
         * Board Constructor if board is already known
         *
         * @param board container of the values of the board
         */
        Board(const std::vector<int>& board);

        /**
         * Boardy Copy Constructor
         *
         * @param src Board to be copied from
         */
        Board(const Board& src);
        
        /**
         * Board Destructor
         */
        ~Board();
        
        /**
         * Access a certain value on the board
         *
         * @param r row of the target value
         * @param c column of the target value
         *
         * @return number located at row r and column c
         */
        int getCell(int r, int c) const;

        /**
         * Access a specific row of the board
         *
         * @param n number of the desired row
         *
         * @return array containing all values in the row
         */
        std::vector<int> getRow(int n) const;

        /**
         * Access a specific column of the board
         *
         * @param n number of the desired column
         *
         * @return array containing all values in the column
         */
        std::vector<int> getCol(int n) const;
        
        /**
         * Access a specific block (3x3) of the board
         *
         * @param n number of the desire block (descends horizontally)
         *
         * @return container of all values in the block
         */
        std::vector<int> getBlock(int n) const;

        /**
         * Access the entire board
         *
         * @return 2D array of the entire sudoku board
         */
        std::vector<int> getBoard() const;
        
        /**
         * Determine how many filled spots are in the board
         *
         * @return the number of values filled into the board
         */
        int getFilled() const;

        /**
         * Determine how many spots are filled in a row
         *
         * @param r row number to examine
         *
         * @return number of filled spots in the row
         */
        int getRowFilled(int r) const;

        /**
         * Determine how many spots are filled in a column
         *
         * @param c column number to examine
         *
         * @return number of filled spots in the column
         */
        int getColFilled(int c) const;
        
        /**
         * Determine how many spots are filled in a block
         *
         * @param b block number to examin
         *
         * @return number of filled spots in the block
         */
        int getBlockFilled(int b) const;

        /**
         * Determine how many spots are empty in a row
         *
         * @param r row number to examine
         *
         * @return number of empty spots in the row
         */
        int getRowEmpty(int r) const;

        /**
         * Determine how many spots are empty in a column
         *
         * @param c column number to be examined
         *
         * @return number of empty spots in the column
         */
        int getColEmpty(int c) const;
        
        /**
         * Determine how many spots are empty in a block
         *
         * @param b block number to be examined
         *
         * @return number of empty spots in the column
         */
        int getBlockEmpty(int b) const;

        /**
         * Set the values of a certain row
         *
         * @param n number of the target row
         * @param row array of values to be set into the row
         */
        void setRow(int n, const std::vector<int>& row);

        /**
         * Set the values of a certain column
         *
         * @param n number of the target column
         * @param col array of values to be set into the column
         */
        void setCol(int n, const std::vector<int>& col);
        
        /**
         * Set the values of a certain column
         *
         * @param n number of the target block
         * @param b container of values to replace the block
         */
        void setBlock(int n, const std::vector<int>& b);

        /**
         * Set the values of the entire sudoku board
         *
         * @param newBoard set of new values to be input into the board
         */
        void setBoard(const std::vector<int>& newBoard);
        
        /**
         * Set the value of a single cell
         *
         * @param r row of the target cell
         * @param c column of the target cell
         * @param val value to be placed in the specific cell
         */
        void setCell(int r, int c, int val);
        
        /**
         * Determine whether the board is full or not
         *
         * @return true if all 81 spots are filled on the board
         */
        bool isFull() const;
        
        /**
         * Determine whether a specific row is full or not
         *
         * @param r row number to be examined
         *
         * @return true if all 9 spots are filled
         */
        bool isRowFull(int r) const;

        /**
         * Determine whehter a specific column is full or not
         *
         * @param c column number to be examined
         *
         * @return true if all 9 spots are filled
         */
        bool isColFull(int c) const;

        /**
         * Search a row/block/col for a certain number
         *
         * @param n row/block/col number
         * @param toSearch number to search for
         * @param type character determining row('r'), column('c'), or block('b')
         *
         * @return true if the row/col/block has the desired number
         */
        bool searchFor(int n, int toSearch, char type) const;

        /**
         * Overloaded asignment operator
         *
         * @param src Board to be assigned to left hand side Board
         *
         * @return newly assigned board
         */
        Board operator=(const Board& src);

        /**
         * Overloaded comparision operator
         * A board is less than another if it has less spaces filled in
         *
         * @param lhs Board on the left hand side of the less than
         *
         * @return true if lhs is less than this
         */
        bool operator<(const Board& lhs) const;
        
        /**
         * Overloaded logical equivalence operator
         *
         * @param lhs Board object to be compared with this
         *
         * @return true if the boards are equivalent
         */
        bool operator==(const Board& lhs) const;

        /**
         * Output the board to an output stream
         *
         * @param outs output stream
         */
        void display(std::ostream& outs) const;

        /**
         * Read in a board from an input stream
         *
         * @param ins input stream
         */
        void read(std::istream& ins);

};

/** \relates Board
 * Overloaded stream insertion operator
 *
 * @param outs output stream
 * @param prt Board object that will be printed to the output stream
 *
 * @return output stream
 */
inline
std::ostream& operator<<(std::ostream& outs, const Board& prt)
{
    prt.display(outs);

    return outs;
}

/** \relates Board
 * Overloaded stream extraction operator
 *
 * @param ins input stream
 * @param obj object to read in
 *
 * @return input stream
 */
inline
std::istream& operator>>(std::istream& ins, Board& obj)
{
    obj.read(ins);

    return ins;
}
#endif
