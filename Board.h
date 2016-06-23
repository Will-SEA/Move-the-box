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
public:

    Board();

    Board(bool loadFlag);

    bool operator==(Board& rhs) const;

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

    void allPossibleMove(std::vector<Board> &allMoves, bool &findSolution) const;


private:
    // width of the game board
    int width_;

    // height of the game board
    int height_;

    // game board
    std::vector<int> listOfBox_;

    // path
    std::vector<Move> path_;

    /*
     * Method:          bool swap(int row1, int col1, int row2, int col2)
     * Description:     this method will swap the type of 2 boxes
     * Parameters:      all the 4 parameters are integer, the first 2 are the position of first box, and the
     *                  other 2 are the position of second box.
     * */
    Board swap( int row1, int col1, int row2, int col2, bool &isSwapped) const;

    /*
     * Method:          bool findClear(set<int> &list);
     * Description:     this method is used to traverse the game board, and find is there any consecutive boxes, and
     *                  the number is over 3. This traverse method will traverse 2 twice, the one is vertical direction,
     *                  the other one is horizontal direction. the main idea is like 2 pointers.
     * Parameters:      the element will store the position that needs to be cleared
     * */
    bool findClear( std::set<int> &clearList) const;

    /*
     * Method:          getPos(int row, int col)
     * Description:     this method will return the position of certain box with row and col in the 1D vector
     * Parameters:      row is the row number of the box in the game board and the col is the column number.
     */
    int getPos(int row, int col) const;

};


#endif //MOVETHEBOX_BOARD_H
