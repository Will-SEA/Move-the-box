//
// Created by yuanhao on 5/22/16.
//
#include "Board.h"
#include <iomanip>
#include <fstream>
#include <sstream>


Board::Board() {

    cout << "Welcome to Move the Box game!" << endl;
    cout << "A logic puzzle about moving boxes around. Clean the dock, do it fast!" << endl;
    cout << "You can move, drop and swap the boxes." << endl;
    cout << "Three or more boxes of the same kind in a line disappear!" << endl << endl;

    cout << "Please input the level that you want to play. " << "We have 10 levels" <<endl;

    string level;
    cin >> level;
    level = "Level/" + level + ".txt";

    ifstream infile(level);
    if (infile.fail()) {
        cout << "Input file opening failed" << endl;
    }
    string str;
    int rowNum = 0;
    int widthCheck = 0;
    while (getline(infile, str)) {
        int colNum = 0;
        istringstream list(str);
        string type;

        while (list >> type) {
            int _type;
            istringstream(type) >> _type;
            if (_type != -1) {
                if (boxCount_.count(_type) == 0) {
                    boxCount_[_type] = 1;
                } else {
                    boxCount_[_type] += 1;
                }
            }
            Box b(_type, rowNum, colNum);
            board_.push_back(b);
            colNum++;
        }
        if (widthCheck == 0) {
            widthCheck = colNum;
        }
        if (colNum != widthCheck) {
            cerr << "the " << rowNum << "th "
            << "row has the different length compared with other row! Please check again!" << endl;
            exit(0);
        }
        widthCheck = colNum;
        rowNum++;
    }

    height_ = rowNum;
    width_ = widthCheck;
    cout << "height_: " << height_ << endl;
    cout << "width_: " << width_ << endl;


}

void Board::play() {

    while (1) {
        cout << "Please enter the position of the box that you want to move and the direction " << endl;
        cout << "NOTE: UP:0, DOWN:1, LEFT:2, RIGHT:3" << endl;
        print();
        int row, col, dir;

        cin >> row >> col >> dir;

        if (move (row, col, dir)) {
            gravity();
            while(1) {
                set<int> clearList;
                if (findClear(clearList)) {
                    doClear(clearList);
                    //print();
                    gravity();
                } else {
                    break;
                }
            }
        } else {
            cout << "move action is invalid!" << endl;
        }

        if(win()) {
            cout << "You Win!" << endl;
            break;
        }

        //cout << canWin() << endl;
        if(!canWin()) {
            cout << "You lose!" << endl;
            break;
        }
    }
}

void Board::print() const{



    cout << "   ";
    for (int i = 0; i < height_; i++) {
        if (i == 0) {//"   1   2   3..."
            for (int j = 0; j < width_; j++) {
                cout.flags(ios::right); //rigth alignment
                cout << " " << setw(3) << j;
            }
            cout << endl;
        }
        cout.flags(ios::right);
        cout << setw(3) << i  << " ";
        for (int j = 0; j < width_; j++) {

            cout.flags(ios::right);
            int pos = getPos(i, j);
            cout << setw(3) << board_[pos].type_ << ' ';
        }
        cout << endl;
    }
}

void Board::gravity() {
// i/j two pointer

    for (int col = 0; col < width_; col++) {
        Box index = board_[getPos(height_ - 1, col)];
        for (int row = height_ - 1; row >= 0; row--) {
            int cur_type = board_[getPos(row, col)].type_;
            if (cur_type != -1) {
                swap(row, col, index.row_, index.col_);
                index = board_[getPos(index.row_ - 1, col)];
            }
        }
    }
}


bool Board::findClear(set<int> &list) {
    int consec_count = 0;
    bool found_match = false;


    //clearMask();

    //find consecutive horizontal matches
    for(int i = 0 ; i < height_ ; i++){

        Box last_box = board_[getPos(i, 0)];
        for(int j  = 1 ; j < width_ ; j++){
            Box cur_box = board_[getPos(i, j)];
            if(cur_box.type_ == last_box.type_ && cur_box.type_ > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int col = last_box.col_; col < cur_box.col_; col++) {
                        list.insert(getPos(i, col));
                        found_match = true;
                    }
                }
                last_box = cur_box;
                consec_count = 0;
            }
        }
        if(consec_count >= 2){

            for (int col = last_box.col_; col < width_; col++) {

                list.insert(getPos(i, col));
                found_match = true;
            }
            consec_count = 0;
        }
    }

    //find consecutive vertical matches
    for(int j = 0; j < width_; j++){
        Box last_box = board_[getPos(0, j)];
        for(int i  = 1 ; i < height_ ; i++){
            Box cur_box = board_[getPos(i, j)];
            if(cur_box.type_ == last_box.type_ && cur_box.type_ > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int row = last_box.row_; row < cur_box.row_; row++) {
                        list.insert(getPos(row, j));
                        found_match = true;
                    }
                }
                last_box = cur_box;
                consec_count = 0;
            }
        }
        if(consec_count >= 2){
            for (int row = last_box.row_; row < height_; row++) {
                list.insert(getPos(row, j));
                found_match = true;
                consec_count = 0;
            }
        }
    }
    return found_match;

}

void Board::doClear(const set<int> &list) {
    //clear the board wherever there matching boxes 3 in a row

    for (set<int>::iterator it = list.begin(); it != list.end(); ++it) {
        int curType = board_[*it].type_;
        if (curType != -1) {
            if (boxCount_[curType] == 1) {
                boxCount_.erase(curType);
            } else {
                boxCount_[curType] -= 1;
            }
        }
        board_[*it].type_ = -1;
    }


}


bool Board::swap(int row1, int col1, int row2, int col2) {

    if (board_[getPos(row1, col1)].type_ == -1) {
        return false;
    }
    if (row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0
        || row1 >= height_ || col1 >= width_ || row2 >= height_ || col2 >= width_) {
        return false;
    }
    int type = board_[getPos(row2, col2)].type_;
    board_[getPos(row2, col2)].type_ = board_[getPos(row1, col1)].type_;
    board_[getPos(row1, col1)].type_ = type;

    return true;

}

bool Board::move(int row, int col, int dir) {
    bool move = false;
    int deltaX = 0;
    int deltaY = 0;
    switch(dir) {
        case UP:
            deltaY = -1;
            if (swap(row, col, row + deltaY, col + deltaX)) {
                move = true;
                break;
            } else {
                break;
            }
        case DOWN:
            deltaY = 1;
            if (swap(row, col, row + deltaY, col + deltaX)) {
                move = true;
                break;
            } else {
                break;
            }
        case LEFT:
            deltaX = -1;
            if (swap(row, col, row + deltaY, col + deltaX)) {
                move = true;
                break;
            } else {
                break;
            }
        case RIGHT:
            deltaX = 1;
            if (swap(row, col, row + deltaY, col + deltaX)) {
                move = true;
                break;
            } else {
                break;
            }

        default:
            break;
    }

    return move;
}

bool Board::canWin() {
    for (map<int, int>::iterator it = boxCount_.begin(); it != boxCount_.end(); ++it) {
        //cout << it->first << ": " << it->second << endl;
        if (it -> second < 3) {
            return false;
        }
    }
    return true;
}

bool Board::win() const{
    return boxCount_.empty();
}

int Board::getPos(int row, int col) const {
    return row * width_ + col;
}

/*int Board::getRowCol(int pos) const {
    int row, col;

}*/

Board::~Board() { }



