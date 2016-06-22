//
// Created by yuanhao on 6/21/16.
//

#include "Board.h"

Move::Move(int row, int col, Direction dir): row_(row), col_(col), dir_(dir) { }

void Board::print() const {
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
            cout << setw(3) << listOfBox_[pos] << ' ';
        }
        cout << endl;
    }
}

void Board::gravity() {
    for (int col = 0; col < width_; col++) {
        int index_row = height_ - 1;
        int index_col = col;
        for (int row = height_ - 1; row >= 0; row--) {
            int cur_type = listOfBox_[getPos(row, col)];
            if (cur_type != -1) {
                swap(row, col, index_row, index_col);
                index_row -= 1;
            }
        }
    }
}

bool Board::findClear(set<int> &list) {
    int consec_count = 0;
    bool found_match = false;

    //find consecutive horizontal matches
    for(int i = 0 ; i < height_ ; i++){
        int last_type = listOfBox_[getPos(i, 0)];
        int start_col = 0;
        for(int j  = 1 ; j < width_ ; j++){
            int cur_type = listOfBox_[getPos(i, j)];
            if(cur_type == last_type && cur_type > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int col = start_col; col < j; col++) {
                        list.insert(getPos(i, col));
                        found_match = true;
                    }
                }
                last_type = listOfBox_[getPos(i, j)];
                start_col = j;
                consec_count = 0;
            }
        }
        if(consec_count >= 2){

            for (int col = start_col; col < width_; col++) {

                list.insert(getPos(i, col));
                found_match = true;
            }
        }
        consec_count = 0;
    }

    //find consecutive vertical matches
    for(int j = 0; j < width_; j++){
        int last_type = listOfBox_[getPos(0, j)];
        int start_row = 0;
        for(int i  = 1 ; i < height_ ; i++){
            int cur_type = listOfBox_[getPos(i, j)];
            if(cur_type == last_type && cur_type > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int row = start_row; row < i; row++) {
                        list.insert(getPos(row, j));
                        found_match = true;
                    }
                }
                last_type = listOfBox_[getPos(i, j)];
                start_row = i;
                consec_count = 0;
            }
        }
        if(consec_count >= 2){
            for (int row = start_row; row < height_; row++) {
                list.insert(getPos(row, j));
                found_match = true;
            }
        }
        consec_count = 0;
    }
    return found_match;
}

void Board::doClear(const set<int> &list) {
    for (set<int>::iterator it = list.begin(); it != list.end(); ++it) {
        listOfBox_[*it] = -1;
    }
}

bool Board::swap(int row1, int col1, int row2, int col2) {
    if (listOfBox_[getPos(row1, col1)] == -1 && listOfBox_[getPos(row2, col2)] == -1) {
        //cout << "1" << endl;
        return false;
    }
    if (row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0
        || row1 >= height_ || col1 >= width_ || row2 >= height_ || col2 >= width_) {
        //cout << "2" << endl;
        return false;
    }
    int type = listOfBox_[getPos(row2, col2)];
    listOfBox_[getPos(row2, col2)] = listOfBox_[getPos(row1, col1)];
    listOfBox_[getPos(row1, col1)] = type;

    return true;
}

bool Board::move( int row, int col, int dir) {
    bool move = false;
    int deltaX = 0;
    int deltaY = 0;
    switch(dir) {
        case UP:
            deltaY = -1;
            if (swap(row, col, row + deltaY, col + deltaX)) {
                move = true;
                Move m(row, col, UP);
                path_.push_back(m);
                break;
            } else {
                break;
            }
        case DOWN:
            deltaY = 1;
            if (swap(row, col, row + deltaY, col + deltaX)) {
                move = true;
                Move m(row, col, DOWN);
                path_.push_back(m);
                break;
            } else {
                break;
            }
        case LEFT:
            deltaX = -1;
            if (swap(row, col, row + deltaY, col + deltaX)) {
                move = true;
                Move m(row, col, LEFT);
                path_.push_back(m);
                break;
            } else {
                break;
            }
        case RIGHT:
            deltaX = 1;
            if (swap(row, col, row + deltaY, col + deltaX)) {
                move = true;
                Move m(row, col, RIGHT);
                path_.push_back(m);
                break;
            } else {
                break;
            }

        default:
            break;
    }

    return move;
}

bool Board::win() const {
    map <int, int> boxCount;
    for (int i = 0; i < listOfBox_.size(); i++) {
        int type = listOfBox_[i];
        if (type != -1) {
            if (boxCount.count(type) == 0) {
                boxCount[type] = 1;
            } else {
                boxCount[type] += 1;
            }
        }
    }
    return boxCount.empty();
}

bool Board::canWin() const {
    map <int, int> boxCount;
    for (int i = 0; i < listOfBox_.size(); i++) {
        int type = listOfBox_[i];
        if (type != -1) {
            if (boxCount.count(type) == 0) {
                boxCount[type] = 1;
            } else {
                boxCount[type] += 1;
            }
        }
    }
    for (map<int, int>::iterator it = boxCount.begin(); it != boxCount.end(); ++it) {
        //cout << it->first << ": " << it->second << endl;
        if (it -> second < 3) {
            return false;
        }
    }
    return true;
}

int Board::getPos(int row, int col) const {
    return row * width_ + col;
}

bool Board::isSameBoard(Board board) const {
    if (listOfBox_.size() != board.listOfBox_.size()) {
        return false;
    }

    for (int i = 0; i < listOfBox_.size(); i++) {
        if (listOfBox_[i] != board.listOfBox_[i]) {
            return false;
        }
    }
    return true;
}