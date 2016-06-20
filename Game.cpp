//
// Created by yuanhao on 6/17/16.
//

#include "Game.h"
#include <iomanip>
#include <fstream>
#include <sstream>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT};



Game::Game() {
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
                if (gameBoard_.boxCount_.count(_type) == 0) {
                    gameBoard_.boxCount_[_type] = 1;
                } else {
                    gameBoard_.boxCount_[_type] += 1;
                }
            }
            Box b(_type, rowNum, colNum);
            gameBoard_.listOfBox_.push_back(b);
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

Game::~Game() { }

void Game::play() {

    while (1) {
        cout << "Please enter the position of the box that you want to move and the direction " << endl;
        cout << "NOTE: UP:0, DOWN:1, LEFT:2, RIGHT:3" << endl;
        print(gameBoard_);
        int row, col, dir;

        cin >> row >> col >> dir;

        if (move (gameBoard_, row, col, dir)) {
            gravity(gameBoard_);
            while(1) {
                set<int> clearList;
                if (findClear(gameBoard_, clearList)) {
                    doClear(gameBoard_, clearList);
                    //print();
                    gravity(gameBoard_);
                } else {
                    break;
                }
            }
        } else {
            cout << "move action is invalid!" << endl;
        }

        if(win(gameBoard_)) {
            cout << "You Win!" << endl;
            break;
        }

        //cout << canWin() << endl;
        if(!canWin(gameBoard_)) {
            cout << "You lose!" << endl;
            break;
        }
    }
}


void Game::print(Board board) const {
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
            cout << setw(3) << board.listOfBox_[pos].type_ << ' ';
        }
        cout << endl;
    }
}

void Game::gravity(Board &board) {
    for (int col = 0; col < width_; col++) {
        Box index = board.listOfBox_[getPos(height_ - 1, col)];
        for (int row = height_ - 1; row >= 0; row--) {
            int cur_type = board.listOfBox_[getPos(row, col)].type_;
            if (cur_type != -1) {
                swap(board, row, col, index.row_, index.col_);
                index = board.listOfBox_[getPos(index.row_ - 1, col)];
            }
        }
    }
}

bool Game::findClear(Board board, set<int> &list) {
    int consec_count = 0;
    bool found_match = false;


    //clearMask();

    //find consecutive horizontal matches
    for(int i = 0 ; i < height_ ; i++){

        Box last_box = board.listOfBox_[getPos(i, 0)];
        for(int j  = 1 ; j < width_ ; j++){
            Box cur_box = board.listOfBox_[getPos(i, j)];
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
        Box last_box = board.listOfBox_[getPos(0, j)];
        for(int i  = 1 ; i < height_ ; i++){
            Box cur_box = board.listOfBox_[getPos(i, j)];
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

void Game::doClear(Board &board, const set<int> &list) {
    for (set<int>::iterator it = list.begin(); it != list.end(); ++it) {
        int curType = board.listOfBox_[*it].type_;
        if (curType != -1) {
            if (board.boxCount_[curType] == 1) {
                board.boxCount_.erase(curType);
            } else {
                board.boxCount_[curType] -= 1;
            }
        }
        board.listOfBox_[*it].type_ = -1;
    }
}

bool Game::swap(Board &board, int row1, int col1, int row2, int col2) {
    if (board.listOfBox_[getPos(row1, col1)].type_ == -1 && board.listOfBox_[getPos(row2, col2)].type_ == -1) {
        return false;
    }
    if (row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0
        || row1 >= height_ || col1 >= width_ || row2 >= height_ || col2 >= width_) {
        return false;
    }
    int type = board.listOfBox_[getPos(row2, col2)].type_;
    board.listOfBox_[getPos(row2, col2)].type_ = board.listOfBox_[getPos(row1, col1)].type_;
    board.listOfBox_[getPos(row1, col1)].type_ = type;

    return true;
}

bool Game::move(Board &board, int row, int col, int dir) {
    bool move = false;
    int deltaX = 0;
    int deltaY = 0;
    switch(dir) {
        case UP:
            deltaY = -1;
            if (swap(board, row, col, row + deltaY, col + deltaX)) {
                move = true;
                break;
            } else {
                break;
            }
        case DOWN:
            deltaY = 1;
            if (swap(board, row, col, row + deltaY, col + deltaX)) {
                move = true;
                break;
            } else {
                break;
            }
        case LEFT:
            deltaX = -1;
            if (swap(board, row, col, row + deltaY, col + deltaX)) {
                move = true;
                break;
            } else {
                break;
            }
        case RIGHT:
            deltaX = 1;
            if (swap(board, row, col, row + deltaY, col + deltaX)) {
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

Board Game::simulateMove(Board &board, int row, int col, int dir) {
    int deltaX = 0;
    int deltaY = 0;
    Board movedBoard;

    movedBoard = board;

    switch(dir) {
        case UP:
            deltaY = -1;
            if (swap(movedBoard, row, col, row + deltaY, col + deltaX)) {
                Move m(row, col, UP);
                movedBoard.path.push_back(m);
                break;
            } else {
                cout << "move action is invalid!" << endl;
                break;
            }
        case DOWN:
            deltaY = 1;
            if (swap(movedBoard, row, col, row + deltaY, col + deltaX)) {
                Move m(row, col, DOWN);
                movedBoard.path.push_back(m);
                break;
            } else {
                cout << "move action is invalid!" << endl;
                break;
            }
        case LEFT:
            deltaX = -1;
            if (swap(movedBoard, row, col, row + deltaY, col + deltaX)) {
                Move m(row, col, LEFT);
                movedBoard.path.push_back(m);
                break;
            } else {
                cout << "move action is invalid!" << endl;
                break;
            }
        case RIGHT:
            deltaX = 1;
            if (swap(movedBoard, row, col, row + deltaY, col + deltaX)) {
                Move m(row, col, RIGHT);
                movedBoard.path.push_back(m);
                break;
            } else {
                cout << "move action is invalid!" << endl;
                break;
            }

        default:
            break;
    }

    return movedBoard;
}

bool Game::win(Board board) const {
    return board.boxCount_.empty();
}

bool Game::canWin(Board board) {
    for (map<int, int>::iterator it = board.boxCount_.begin(); it != board.boxCount_.end(); ++it) {
        //cout << it->first << ": " << it->second << endl;
        if (it -> second < 3) {
            return false;
        }
    }
    return true;
}


int Game::getPos(int row, int col) const {
    return row * width_ + col;
}

void Game::allPossibleMove(vector<Board> &solution, int position) {
    const char * direction[] = {"Up", "Down", "Left", "Right"};
    Board curBoard;
    curBoard = solution[position];
    //print(curBoard);
    for (int row = 0; row < height_; row++) {
        for (int col = 0; col < width_; col++) {

            if (curBoard.listOfBox_[getPos(row, col)].type_ != -1 ||
                curBoard.listOfBox_[getPos(row, col + 1)].type_ != -1) {

                Board movedBoard = simulateMove(curBoard, row, col, RIGHT);
                gravity(movedBoard);
                while(1) {
                    set<int> clearList;
                    if (findClear(movedBoard, clearList)) {
                        doClear(movedBoard, clearList);
                        gravity(movedBoard);
                    } else {
                        break;
                    }
                }
                if (win(movedBoard)) {
                    cout << "The solution is:" << endl;
                    for (int path = 0; path < movedBoard.path.size(); path++) {
                        cout << path + 1 << " step is: " << endl;
                        cout << "the row number: " << movedBoard.path[path].row_ << endl;
                        cout << "the column number: " << movedBoard.path[path].col_ << endl;
                        cout << "move direction: " << direction[movedBoard.path[path].dir_ ]<< endl;
                    }
                    cout << "searched " << solution.size() << " times" << endl;
                    cout << "the recursion times: " << position << endl;
                    return;
                }
                if (canWin(movedBoard)) {
                    solution.push_back(movedBoard);
                }
            }

            if (curBoard.listOfBox_[getPos(row, col)].type_ != -1 ||
                curBoard.listOfBox_[getPos(row + 1, col)].type_ != -1) {
                Board movedBoard = simulateMove(curBoard, row, col, DOWN);
                gravity(movedBoard);
                while(1) {
                    set<int> clearList;
                    if (findClear(movedBoard, clearList)) {
                        doClear(movedBoard, clearList);
                        gravity(movedBoard);
                    } else {
                        break;
                    }
                }
                if (win(movedBoard)) {
                    cout << "The solution is:" << endl;
                    for (int path = 0; path < movedBoard.path.size(); path++) {
                        cout << "the " << path + 1 << " is: " << endl;
                        cout << "the row number: " << movedBoard.path[path].row_ << endl;
                        cout << "the column number: " << movedBoard.path[path].col_ << endl;
                        cout << "move direction: " << direction[movedBoard.path[path].dir_ ] << endl;
                    }
                    cout << "we searched " << solution.size() << " times" << endl;
                    cout << "the recursion times: " << position << endl;

                    return;
                }
                if (canWin(movedBoard)) {
                    solution.push_back(movedBoard);
                }
            }
        }
    }

    allPossibleMove(solution, position + 1);
}

void Game::findSolution() {
    vector<Board> allMove;
    allMove.push_back(gameBoard_);
    allPossibleMove(allMove, 0);
}
