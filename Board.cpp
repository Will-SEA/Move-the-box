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

    ifstream infile("board.txt");
    if (infile.fail()) {
        cout << "Input file opening failed" << endl;
    }
    string str;
    while (getline(infile, str)) {
        istringstream list(str);
        string type;
        vector<Box> row;
        while (list >> type) {
            Box b(stoi(type));
            row.push_back(b);
        }
        board.push_back(row);
    }

    height = (int) board.size();
    width = (int) board[0].size();
    cout << "height: " << height << endl;
    cout << "width: " << width << endl;


    // Initialization of game board_mask, boxCount, and set the position of the box.
    std::vector<bool> mask(height, false);
    for (int i = 0; i < height; i++) {
        board_mask.push_back(mask);
        for (int j = 0; j < width; j++) {
            board[i][j].setPosition(i, j);
            int type = board[i][j].getType();
            if (type != -1) {
                if (boxCount.count(type) == 0) {
                    boxCount[type] = 1;
                } else {
                    boxCount[type] += 1;
                }
            }
        }
    }

}

void Board::play() {

    cout << "Welcome to Move the Box game!" << endl;
    cout << "A logic puzzle about moving boxes around. Clean the dock, do it fast!" << endl;
    cout << "You can move, drop and swap the boxes." << endl;
    cout << "Three or more boxes of the same kind in a line disappear!" << endl << endl;



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
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout.flags(ios::right); //rigth alignment
            cout << setw(3) << board[i][j].getType() << ' ';
        }
        cout << endl;
    }
}

void Board::gravity() {
 // i/j two pointer

    for (int col = 0; col < width; col++) {
        Box empty = board[height - 1][col];
        for (int row = height - 2; row >= 0; row--) {
            int cur_type = board[row][col].getType();
            if (cur_type != -1 && empty.getType() == -1) {
                swap(row, col, empty.getRow(),empty.getCol());
                empty = board[row][col];
            } else if (cur_type == -1) {
                empty = board[row][col];
            }

        }
    }

}


bool Board::findClear() {
    int consec_count = 0;
    bool found_match = false;

    clearMask();

    //find consecutive horizontal matches
    for(int i = 0 ; i < height ; i++){
        Box last_box = board[i][0];
        for(int j  = 1 ; j < width ; j++){
            Box cur_box = board[i][j];
            if(cur_box.getType() == last_box.getType() && cur_box.getType() > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int col = last_box.getCol(); col < cur_box.getCol(); col++) {
                        board_mask[i][col] = true;
                        if (!found_match)
                            found_match = true;
                    }
                }
                last_box = cur_box;
                consec_count = 0;
            }



        }
        if(consec_count >= 2){
            for (int col = last_box.getCol(); col < width; col++) {
                board_mask[i][col] = true;
                if (!found_match)
                    found_match = true;
            }
        }
    }

    //find consecutive vertical matches
    for(int j = 0; j < width; j++){
        Box last_box = board[0][j];
        for(int i  = 1 ; i < height ; i++){
            Box cur_box = board[i][j];
            if(cur_box.getType() == last_box.getType() && cur_box.getType() > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int row = last_box.getRow(); row < cur_box.getRow(); row++) {
                        board_mask[row][j] = true;
                        if (!found_match)
                            found_match = true;
                    }
                }
                last_box = cur_box;
                consec_count = 0;
            }



        }
        if(consec_count >= 2){
            for (int row = last_box.getRow(); row < height; row++) {
                board_mask[row][j] = true;
                if (!found_match)
                    found_match = true;
            }
        }
    }

    return found_match;

}

void Board::doClear() {
    //clear the board wherever there matching boxes 3 in a row
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (board_mask[i][j]) {
                int currType = board[i][j].getType();
                // if boxCount[currType] equals 1, it means, it's the last one of this type of box
                if (currType != -1) {
                    if (boxCount[currType] == 1) {
                        boxCount.erase(currType);
                    } else {
                        boxCount[currType] -= 1;
                    }
                }

                board[i][j].setType(-1);
            }

        }
    }
}

void Board::clearMask() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            board_mask[i][j] = false;
        }
    }

}

void Board::swap(int row1, int col1, int row2, int col2) {

    if (board[row1][col1].getType() == -1) {
        return;
    }
    if (row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0
        || row1 >= height || col1 >= width || row2 >= height || col2 >= width) {
        return;
    }
    int type = board[row2][col2].getType();
    board[row2][col2].setType(board[row1][col1].getType());
    board[row1][col1].setType(type);
}

void Board::move(int row, int col, int dir) {
    switch(dir) {
        case UP:
            swap(row, col, row - 1, col);
            break;
        case DOWN:
            swap(row, col, row + 1, col);
            break;
        case LEFT:
            swap(row, col, row, col -1);
            break;
        case RIGHT:
            swap(row, col, row, col + 1);
        default:
            break;
    }


    gravity();


    while(1) {

        if (findClear()) {
            //cout << "123" << endl;
            doClear();
            gravity();
        } else {
            break;
        }
    }
}

bool Board::canWin() {
    for (map<int, int>::iterator it = boxCount.begin(); it != boxCount.end(); ++it) {
        //cout << it->first << ": " << it->second << endl;
        if (it -> second < 3) {
            return false;
        }
    }
    return true;
}

bool Board::win() {
    return boxCount.empty();
}

Board::~Board() { }



