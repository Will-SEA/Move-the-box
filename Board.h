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

using namespace std;

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

class Board {
public:

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
    bool move( int row, int col, int dir);

    /*
     * Method:          bool swap(int row1, int col1, int row2, int col2)
     * Description:     this method will swap the type of 2 boxes
     * Parameters:      all the 4 parameters are integer, the first 2 are the position of first box, and the
     *                  other 2 are the position of second box.
     * */
    bool swap( int row1, int col1, int row2, int col2);

    /*
     * Method:          bool findClear(set<int> &list);
     * Description:     this method is used to traverse the game board, and find is there any consecutive boxes, and
     *                  the number is over 3. This traverse method will traverse 2 twice, the one is vertical direction,
     *                  the other one is horizontal direction. the main idea is like 2 pointers.
     * Parameters:      the element will store the position that needs to be cleared
     * */
    bool findClear( set<int> &list);

    /*
     * Method:          void doClear(const set<int> &list)
     * Description:     this method is used to executive the clear action, it will set all the boxes, that need to be
     *                  clear, to empty, which is -1
     * Parameters:      the  element stores the position of the box that needs to be cleared
     * */
    void doClear( const set<int> &list);

    /*
     * Method:          void gravity()
     * Description:     this method is used to traverse the game board, and find is there any box that has no support.
     *                  if this box cannot be hold up, it will falling down until it can be hold up.
     * */
    void gravity();

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
     * Method:          getPos(int row, int col)
     * Description:     this method will return the position of certain box with row and col in the 1D vector
     * Parameters:      row is the row number of the box in the game board and the col is the column number.
     */
    int getPos(int row, int col) const;

    /*
     * Method:          bool isSameBoard(Board board1, Board board2) const
     * Description:
     * Parameters:
     * */
    bool isSameBoard(Board board) const;



    // width of the game board
    int width_;

    // height of the game board
    int height_;

    // game board
    vector<int> listOfBox_;

    // path
    vector<Move> path_;
};


#endif //MOVETHEBOX_BOARD_H
