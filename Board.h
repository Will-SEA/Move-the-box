//
// Created by yuanhao on 6/17/16.
//

#ifndef MOVE_THE_BOX_BOARD_H
#define MOVE_THE_BOX_BOARD_H


#include "Box.h"
#include <vector>
#include <map>

using namespace std;

struct Move {
    int row_;
    int col_;
    int dir_;
    Move(int row, int col, int dir);
};


struct Board {
    // game board
    vector<Box> listOfBox_;

    // this map is used to count the number of each type of non-empty box
    map <int, int> boxCount_;

    // solution
    vector<Move> path;



};


#endif //MOVE_THE_BOX_BOARD_H
