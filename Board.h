//
// Created by yuanhao on 5/22/16.
//

#ifndef MOVE_THE_BOX_GAME_H
#define MOVE_THE_BOX_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Box.h"


class Board {

public:
    /*
     * Method:          Board()
     * Description:     default constructor. User could use this method to initialize a new game board. It will read
     *                  the game board from a txt file,
     * */
    Board();

    /*
     * Method:          play()
     * Description:     this is the main function of the class, it will assemble the other functions of the game
     * */
    void play();

    /*
     * Method:          ~Board()
     * Description:     default deconstructor, since I didn't use any dynamic memory, it's empty now
     * Parameters:
     * */
    ~Board();

private:

    // width of the game board
    int width_;

    // height of the game board
    int height_;

    // game board
    vector<vector<Box> > board_;

    // this map is used to count the number of each type of non-empty box
    map <int, int> boxCount_;


    /*
     * Method:          void print() const;
     * Description:     this method will print the game board
     * */
    void print() const;

    /*
     * Method:          swap(int row1, int col1, int row2, int col2);
     * Description:     this method will swap the type of 2 boxes
     * Parameters:      all the 4 parameters are integer, the first 2 are the position of first box, and the other 2
     *                  are the position of second box.
     * */
    bool swap(int row1, int col1, int row2, int col2);

    /*
     * Method:          move(int row, int col, int dir);
     * Description:     this method is used to move the box based on the user input
     * Parameters:      all the three parameters are integer, the first 2 are position of box that user wants to move,
     *                  the third one is the direction that user want to move. note: 0-up, 1-down, 2-left, 3-right.
     * */
    void move(int row, int col, int dir);

    /*
     * Method:          clearMask()
     * Description:     this function is used to set the mask of each box to default value, which is false
     * */
    void clearMask();

    /*
     * Method:          findClear()
     * Description:     this method is used to traverse the game board, and find is there any consecutive boxes, and
     *                  the number is over 3. This traverse method will traverse 2 twice, the one is vertical direction,
     *                  the other one is horizontal direction. the main idea is like 2 pointers.
     * */
    bool findClear();

    /*
     * Method:          doClear()
     * Description:     this method is used to executive the clear action, it will set all the boxes, that need to be
     *                  clear, to empty, which is -1
     * */
    void doClear();

    /*
     * Method:          gravity()
     * Description:     this method is used to traverse the game board, and find is there any box that has no support.
     *                  if this box cannot be hold up, it will falling down until it can be hold up.
     * */
    void gravity();

    /*
     * Method:          win()
     * Description:     this method is used to check whether user wins the game. The idea is to traverse the boxCount
     *                  map, if this map is empty, it means the game board is empty, so user wins, and then return true,
     *                  otherwise, return false.
     * */
    bool win() const;

    /*
     * Method:          canWin()
     * Description:     this method is used to check whether user still can win the game. The idea is to traverse the
     *                  boxCount map, if any type of box that the number is lower than 3, then return false. otherwise,
     *                  user still can win, and game continue, return true.
     * */
    bool canWin();
};


#endif //MOVE_THE_BOX_GAME_H
