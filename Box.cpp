//
// Created by yuanhao on 5/22/16.
//

#include "Box.h"


Box::Box() {
    setType(-1);
    setPosition(-1, -1);
};

Box::Box(int type){
    setType(type);
    setPosition(-1, -1);
}

Box::Box(int type, int row, int col):type(type), row(row), col(col) {}

int Box::getType() const{
    return type;
}

void Box::setType(int type) {
    this->type = type;
}


void Box::setPosition(int row, int col) {
    this->row = row;
    this->col = col;
}

int Box::getCol() const{
    return col;
}

int Box::getRow() const{
    return row;
}

Box::~Box() {

}