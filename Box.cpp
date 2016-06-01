//
// Created by yuanhao on 5/22/16.
//

#include "Box.h"


Box::Box() {
    setType(-1);
    setPosition(-1, -1);
    setMask(false);
};

Box::Box(int type){
    setType(type);
    setPosition(-1, -1);
    setMask(false);
}

Box::Box(int type, int row, int col, bool mask):type_(type), row_(row), col_(col), mask_(mask) {}

int Box::getType() const{
    return type_;
}

void Box::setType(int type) {
    type_ = type;
}


void Box::setPosition(int row, int col) {
    row_ = row;
    col_ = col;
}

int Box::getCol() const{
    return col_;
}

int Box::getRow() const{
    return row_;
}

bool Box::getMask() const {
    return mask_;
}

void Box::setMask(bool mask) {
    mask_ = mask;
}

Box::~Box() {

}