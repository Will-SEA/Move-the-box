//
// Created by yuanhao on 5/22/16.
//
#include "Board.h"
#include <iomanip>
#include <fstream>
#include <sstream>

#define UP     0
#define DOWN   1
#define LEFT   2
#define RIGHT  3


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
    while (getline(infile, str)) {
        int colNum = 0;
        istringstream list(str);
        string type;
        vector<Box> row;
        while (list >> type) {
            if (stoi(type) != -1) {
                if (boxCount_.count(stoi(type)) == 0) {
                    boxCount_[stoi(type)] = 1;
                } else {
                    boxCount_[stoi(type)] += 1;
                }
            }
            Box b(stoi(type), rowNum, colNum, false);
            row.push_back(b);
            colNum++;
        }
        board_.push_back(row);
        rowNum++;
    }

    height_ = (int) board_.size();
    width_ = (int) board_[0].size();
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

        move (row, col, dir);

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

            if (j == 0) { //first column
                cout.flags(ios::right); //rigth alignment
                cout << setw(3) << board_[i][j].getType() << ' ';
            }
            else { //other column
                cout.flags(ios::right); //rigth alignment
                cout << setw(3) << board_[i][j].getType() << ' ';
            }
        }
        cout << endl;
    }
}

void Board::gravity() {
// i/j two pointer

    for (int col = 0; col < width_; col++) {
        Box index = board_[height_ - 1][col];
        for (int row = height_ - 1; row >= 0; row--) {
            int cur_type = board_[row][col].getType();
            if (cur_type != -1) {
                swap(row, col, index.getRow(), index.getCol());
                index = board_[index.getRow() - 1][col];
            }
        }
    }
}


bool Board::findClear() {
    int consec_count = 0;
    bool found_match = false;

    clearMask();

    //find consecutive horizontal matches
    for(int i = 0 ; i < height_ ; i++){
        Box last_box = board_[i][0];
        for(int j  = 1 ; j < width_ ; j++){
            Box cur_box = board_[i][j];
            if(cur_box.getType() == last_box.getType() && cur_box.getType() > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int col = last_box.getCol(); col < cur_box.getCol(); col++) {
                        board_[i][col].setMask(true);
                        found_match = true;
                    }
                }
                last_box = cur_box;
                consec_count = 0;
            }
        }
        if(consec_count >= 2){
            for (int col = last_box.getCol(); col < width_; col++) {
                board_[i][col].setMask(true);
                found_match = true;
            }
        }
    }

    //find consecutive vertical matches
    for(int j = 0; j < width_; j++){
        Box last_box = board_[0][j];
        for(int i  = 1 ; i < height_ ; i++){
            Box cur_box = board_[i][j];
            if(cur_box.getType() == last_box.getType() && cur_box.getType() > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int row = last_box.getRow(); row < cur_box.getRow(); row++) {
                        board_[row][j].setMask(true);
                        found_match = true;
                    }
                }
                last_box = cur_box;
                consec_count = 0;
            }
        }
        if(consec_count >= 2){
            for (int row = last_box.getRow(); row < height_; row++) {
                board_[row][j].setMask(true);
                found_match = true;
            }
        }
    }

    return found_match;

}

void Board::doClear() {
    //clear the board wherever there matching boxes 3 in a row
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            if (board_[i][j].getMask()) {
                int currType = board_[i][j].getType();
                // if boxCount_[currType] equals 1, it means, it's the last one of this type of box
                if (currType != -1) {
                    if (boxCount_[currType] == 1) {
                        boxCount_.erase(currType);
                    } else {
                        boxCount_[currType] -= 1;
                    }
                }
                board_[i][j].setType(-1);
            }
        }
    }
}

void Board::clearMask() {
    for(int i = 0; i < height_; i++) {
        for(int j = 0; j < width_; j++) {
            board_[i][j].setMask(false);
        }
    }

}

bool Board::swap(int row1, int col1, int row2, int col2) {

    if (board_[row1][col1].getType() == -1) {
        return false;
    }
    if (row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0
        || row1 >= height_ || col1 >= width_ || row2 >= height_ || col2 >= width_) {
        return false;
    }
    int type = board_[row2][col2].getType();
    board_[row2][col2].setType(board_[row1][col1].getType());
    board_[row1][col1].setType(type);

    return true;

}

void Board::move(int row, int col, int dir) {

    switch(dir) {
        case UP:
            if (swap(row, col, row - 1, col)) {
                break;
            } else {
                cout << "Your move is invalid " << endl;
                break;
            }
        case DOWN:
            if (swap(row, col, row + 1, col)) {
                break;
            } else {
                cout << "Your move is invalid " << endl;
                break;
            }
        case LEFT:
            if (swap(row, col, row, col -1)) {
                break;
            } else {
                cout << "Your move is invalid " << endl;
                break;
            }
        case RIGHT:
            if (swap(row, col, row, col + 1)) {
                break;
            } else {
                cout << "Your move is invalid " << endl;
                break;
            }

        default:
            break;
    }


    gravity();


    while(1) {
        if (findClear()) {
            doClear();
            //print();
            gravity();
        } else {
            break;
        }
    }
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

Board::~Board() { }



