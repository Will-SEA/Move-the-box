//
// Created by yuanhao on 6/17/16.
//

#ifndef MOVE_THE_BOX_BOX_H
#define MOVE_THE_BOX_BOX_H


#include <iostream>

using namespace std;

struct Box {
    // box type, default value is -1, which means empty box
    int type_;

    // the row number of this box in the game board
    int row_;

    // the column number of this box in the game board
    int col_;


    /*
    * Method:          Box();
    * Description:     this is the default constructor for the box class, user can use this method to initialize a
    *                  empty box, i.e. type equal -1. And both of the column and row will be set as empty
    * */
    Box();

    /*
    * Method:          Box(int type, int row, int col)
    * Description:     this is the constructor that has three parameter
    * Parameters:      all the three parameters are integer, the first parameter is the type of the box,
    *                  and the rest two parameters define the position of this box in the game board
    */
    Box(int type, int row, int col);
};


#endif //MOVE_THE_BOX_BOX_H
