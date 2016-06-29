//
// Created by yuanhao on 6/21/16.
//

#ifndef MOVETHEBOX_BOARD_H
#define MOVETHEBOX_BOARD_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>

class Board {
public:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT};

    struct Move {
        int row_;
        int col_;
        Direction dir_;
        Move(int row, int col, Direction dir);
    };

    /*
     * Method:          Board();
     * Description:     default constructor
     * */
    Board();

    /*
     * Method:          Board(std::string filePath);
     * Description:     constructor that read from file
     * Parameters:      the file path
     * */
    Board(const std::string &filePath);

    /*
     * Method:          Board(std::vector<int> listOfBox, std::vector<Move> path, int width, int height);
     * Description:     constructor that
     * Parameters:      the file path
     * */
    Board(std::vector<int> listOfBox, std::vector<Move> path, int width, int height);

    /*
     * Method:          Board(const Board& board);
     * Description:     copy constructor
     * Parameters:      the board instance that you want to copy
     * */
    Board(const Board& board);

    /*
     * Method:          bool operator==(Board& rhs) const;
     * Description:     overload == operator, only compare the width, height and listOfBox
     * Parameters:      just a flag when read from file
     * */
    bool operator==(Board& rhs) const;

    /*
     * Method:          Board();
     * Description:     default de-constructor
     * Parameters:      other Board instance
     * */
    ~Board();

    /*
     * Method:          void print() const;
     * Description:     this method will print the game board
     * Parameter:       the gameBoard
     * */
    void print() const;

    /*
     * Method:          Board move(int row, int col, int dir)
     * Description:     this method is used to move the box based on the user input
     * Parameters:      all the three parameters are integer, the first 2 are position of box that user wants to move,
     *                  the third one is the direction that user want to move.
     *                  note: 0-up, 1-down, 2-left, 3-right.
     * */
    Board move( int row, int col, int dir, bool &isMoved) const;

    /*
     * Method:          bool win() const;
     * Description:     this method is used to check whether user wins the game. The idea is to traverse the boxCount
     *                  map, if this map is empty, it means the game board is empty, so user wins, and then return true,
     *                  otherwise, return false.
     * */
    bool win() const;

    /*
     * Method:          bool canWin()
     * Description:     this method is used to check whether user still can win the game. The idea is to traverse the
     *                  boxCount map, if any type of box that the number is lower than 3, then return false. otherwise,
     *                  user still can win, and game continue, return true.
     * */
    bool canWin() const;


    /*
     * Method:          bool isValidBoard() const;
     * Description:     this method is used to check whether the current board is empty, if it's empty it's width and
     *                  height should be -1, then return false
     * */
    bool isValidBoard() const;

    /*
     * Method:          Board findAllMove(std::vector<Board> &allMoves) const
     * Description:     this method is used to find all possible moves of the current board, when finish the move, if
     *                  win the game return the final board, otherwise return a empty board.
     * Parameters:      the vector of board stores all the possible boards after all possible moves, and the function
     *                  will keep push new board into it until find the solution to win.
     * */
    Board findAllMove(std::vector<Board> &allMoves) const;

    /*
    * Method:          unsigned long pathSize() const;
    * Description:     this method is used to show the size of the path vector, which means the step numbers
     * */
    unsigned long pathSize() const;

    /*
     * Method:          Board::Move getPath(int step) const;
     * Description:     this method is used to show the certain move of current board
     * Parameters:      the step means the order in the path.
     * */
    Board::Move getPath(int step) const;

private:

    bool canSwap(int row1, int col1, int row2, int col2) const;

    /*
     * Method:          bool swap(int row1, int col1, int row2, int col2)
     * Description:     this method will swap the type of 2 boxes
     * Parameters:      all the 4 parameters are integer, the first 2 are the position of first box, and the
     *                  other 2 are the position of second box.
     * */
    std::vector<int> swap( int row1, int col1, int row2, int col2) const;

    /*
     * Method:          std::set<int> findClearBox(const std::vector<int> &tmpBoard) const;;
     * Description:     this method is used to traverse the game board, and find is there any consecutive boxes, and
     *                  the number is over 3. This traverse method will traverse 2 twice, the one is vertical direction,
     *                  the other one is horizontal direction. the main idea is like 2 pointers. after the traverse, it
     *                  would return the set.
     * Parameters:      the parameter is a copy of the current board's layout, which is a vector of int.
     * */
    std::set<int> findClearBox(const std::vector<int> &tmpBoard) const;

    /*
     * Method:          bool gravity(std::vector<int> &tmpBoard) const
     * Description:     this method is used after the move action, it will traverse the layout of the current board,
     *                  if there is a box needs to do the gravity move, then it will fall down and return  true, if
     *                  current state is steady, return false.
     * Parameters:      the parameter is a copy of the current board's layout, which is a vector of int.
     * */
    bool gravity(std::vector<int> &tmpBoard) const;

    /*
     * Method:          getPos(int row, int col)
     * Description:     this method will return the position of certain box with row and col in the 1D vector
     * Parameters:      row is the row number of the box in the game board and the col is the column number.
     */
    int getPos(int row, int col) const;

    /*
     * Method:          int boxAt(int row, int col) const
     * Description:     this method will return the type value of certain box with row and col in the 1D vector
     * Parameters:      row is the row number of the box in the game board and the col is the column number.
     */
    int boxAt(int row, int col) const;

    // width of the game board
    int width_;

    // height of the game board
    int height_;

    // game board
    std::vector<int> listOfBox_;

    // path that from initial state to current state
    std::vector<Move> path_;

};


#endif //MOVETHEBOX_BOARD_H
