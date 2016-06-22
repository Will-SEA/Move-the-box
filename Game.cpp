//
// Created by yuanhao on 6/21/16.
//

#include "Game.h"

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
            gameBoard_.listOfBox_.push_back(_type);
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

    gameBoard_.height_ = rowNum;
    gameBoard_.width_ = widthCheck;
    cout << "height_: " << gameBoard_.height_ << endl;
    cout << "width_: " << gameBoard_.width_  << endl;
}

Game::~Game() { }

void Game::play() {
    while (1) {
        cout << "Please enter the position of the box that you want to move and the direction " << endl;
        cout << "NOTE: UP:0, DOWN:1, LEFT:2, RIGHT:3" << endl;
        gameBoard_.print();
        int row, col, dir;

        cin >> row >> col >> dir;
        Board movedBoard = gameBoard_;
        if (movedBoard.move (row, col, dir)) {
            movedBoard.gravity();
            while(1) {
                set<int> clearList;
                if (movedBoard.findClear(clearList)) {
                    movedBoard.doClear(clearList);
                    movedBoard.gravity();
                } else {
                    break;
                }
            }
            gameBoard_ = movedBoard;
        } else {
            cout << "move action invalid" << endl;
        }


        if(gameBoard_.win()) {
            cout << "You Win!" << endl;
            break;
        }

        if(!gameBoard_.canWin()) {
            cout << "You lose!" << endl;
            break;
        }
    }
}

void Game::findSolution() {
    const char * direction[] = {"Up", "Down", "Left", "Right"};
    vector<Board> allPossibleMove;
    allPossibleMove.push_back(gameBoard_);
    int index = 0;

    do {
        Board curBoard;
        curBoard = allPossibleMove[index];
        for (int row = 0; row < curBoard.height_; row++) {
            for (int col = 0; col < curBoard.width_; col++) {

                //move right
                Board moveRight = curBoard;
                if (moveRight.move(row, col, RIGHT)) {
                    moveRight.gravity();
                    while (1) {
                        set<int> clearList;
                        if (moveRight.findClear(clearList)) {
                            moveRight.doClear(clearList);
                            moveRight.gravity();
                        } else {
                            break;
                        }
                    }

                    if (moveRight.win()) {
                        cout << "The solution is:" << endl;
                        for (int path = 0; path < moveRight.path_.size(); path++) {
                            cout << path + 1 << " step is: " << endl;
                            cout << "the row number: " << moveRight.path_[path].row_ << endl;
                            cout << "the column number: " << moveRight.path_[path].col_ << endl;
                            cout << "move direction: " << direction[moveRight.path_[path].dir_ ]<< endl;
                        }
                        cout << "possible boards: " << allPossibleMove.size() <<  endl;
                        cout << "the loop times: " << index + 1<< endl;
                        return;
                    }

                    if (moveRight.canWin()) {
                        bool storeFlag = true;
                        for (int i = 0; i < allPossibleMove.size(); i++) {
                            if (moveRight.isSameBoard(allPossibleMove[i])) {
                                storeFlag = false;
                                break;
                            }
                        }
                        if (storeFlag) {
                            allPossibleMove.push_back(moveRight);
                        }
                    }
                }

                // move down
                Board moveDown = curBoard;
                if (moveDown.move(row, col, DOWN)) {
                    moveDown.gravity();
                    while (1) {
                        set<int> clearList;
                        if (moveDown.findClear(clearList)) {
                            moveDown.doClear(clearList);
                            moveDown.gravity();
                        } else {
                            break;
                        }
                    }

                    if (moveDown.win()) {
                        cout << "The solution is:" << endl;
                        for (int path = 0; path < moveDown.path_.size(); path++) {
                            cout << path + 1 << " step is: " << endl;
                            cout << "the row number: " << moveDown.path_[path].row_ << endl;
                            cout << "the column number: " << moveDown.path_[path].col_ << endl;
                            cout << "move direction: " << direction[moveDown.path_[path].dir_ ]<< endl;
                        }
                        cout << "possible boards: " << allPossibleMove.size() <<  endl;
                        cout << "the loop times: " << index + 1 << endl;
                        return;
                    }

                    if (moveDown.canWin()) {
                        bool storeFlag = true;
                        for (int i = 0; i < allPossibleMove.size(); i++) {
                            if (moveDown.isSameBoard(allPossibleMove[i])) {
                                storeFlag = false;
                                break;
                            }
                        }
                        if (storeFlag) {
                            allPossibleMove.push_back(moveDown);
                        }
                    }
                }

            }
        }
        index++;
    } while(index < allPossibleMove.size());
}



