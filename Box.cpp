//
// Created by yuanhao on 6/17/16.
//

#include "Box.h"


Box::Box() {
    type_ = -1;
    row_  = -1;
    col_  = -1;
};

Box::Box(int type, int row, int col):type_(type), row_(row), col_(col) { }
