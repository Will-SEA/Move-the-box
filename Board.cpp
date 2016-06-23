//
// Created by yuanhao on 6/21/16.
//

#include "Board.h"

Board::Move::Move(int row, int col, Direction dir): row_(row), col_(col), dir_(dir) { }

Board::Board(bool fileFlag) {
    std::cout << "Please input the level that you want to play. " << "We have 10 levels" << std::endl;

    std::string level;
    std::cin >> level;
    level = "Level/" + level + ".txt";
    std::ifstream infile(level);
    if (infile.fail()) {
        std::cout << "Input file opening failed" << std::endl;
    }
    std::string str;
    int rowNum = 0;
    int widthCheck = 0;
    while (getline(infile, str)) {
        int colNum = 0;
        std::istringstream list(str);
        std::string type;

        while (list >> type) {
            int _type;
            std::istringstream(type) >> _type;
            listOfBox_.push_back(_type);
            colNum++;
        }
        if (widthCheck == 0) {
            widthCheck = colNum;
        }
        if (colNum != widthCheck) {
            std::cerr << "the " << rowNum << "th "
            << "row has the different length compared with other row! Please check again!" << std::endl;
            exit(0);
        }
        widthCheck = colNum;
        rowNum++;
    }

    height_ = rowNum;
    width_ = widthCheck;
    std::cout << "height_: " << height_ << std::endl;
    std::cout << "width_: " << width_  << std::endl;
}

Board::Board() { }

bool Board::operator==(Board &rhs) const {
    if (rhs.listOfBox_.size() != listOfBox_.size() ||
            rhs.width_ != width_ || rhs.height_ != height_) {
        return false;
    }
    for (int i = 0; i < listOfBox_.size(); i++) {
        if (listOfBox_[i] != rhs.listOfBox_[i]) {
            return false;
        }
    }
    return true;
}

Board::~Board() { }

void Board::print() const {
    std::cout << "   ";
    for (int i = 0; i < height_; i++) {
        if (i == 0) {//"   1   2   3..."
            for (int j = 0; j < width_; j++) {
                std::cout.flags(std::ios::right); //rigth alignment
                std::cout << " " << std::setw(3) << j;
            }
            std::cout << std::endl;
        }
        std::cout.flags(std::ios::right);
        std::cout << std::setw(3) << i  << " ";
        for (int j = 0; j < width_; j++) {

            std::cout.flags(std::ios::right);
            int pos = getPos(i, j);
            std::cout << std::setw(3) << listOfBox_[pos] << ' ';
        }
        std::cout << std::endl;
    }
}

bool Board::findClear(std::set<int> &clearList) const{
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
                        clearList.insert(getPos(i, col));
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

                clearList.insert(getPos(i, col));
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
                        clearList.insert(getPos(row, j));
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
                clearList.insert(getPos(row, j));
                found_match = true;
            }
        }
        consec_count = 0;
    }
    return found_match;
}


Board Board::swap(int row1, int col1, int row2, int col2, bool &isSwapped) const {
    Board swapped;
    swapped.listOfBox_ = listOfBox_;
    swapped.path_ = path_;
    swapped.width_ = width_;
    swapped.height_ = height_;

    if (row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0
        || row1 >= height_ || col1 >= width_ || row2 >= height_ || col2 >= width_) {
        //std::cout << "2" << std::endl;
        isSwapped = false;
        return swapped;
    }

    if (listOfBox_[getPos(row1, col1)] == -1 && listOfBox_[getPos(row2, col2)] == -1) {
        //std::cout << "1" << std::endl;
        isSwapped = false;
        return swapped;
    }

    if (listOfBox_[getPos(row1, col1)] == listOfBox_[getPos(row2, col2)]) {
        isSwapped = false;
        return swapped;
        //std::cout << "3" << std::endl;
    }

    int type = swapped.listOfBox_[getPos(row2, col2)];
    swapped.listOfBox_[getPos(row2, col2)] = swapped.listOfBox_[getPos(row1, col1)];
    swapped.listOfBox_[getPos(row1, col1)] = type;

    return swapped;
}

// row col dir bool &isMoved
Board Board::move( int row, int col, int dir, bool &isMoved) const {

    int deltaX = 0;
    int deltaY = 0;
    switch(dir) {
        case UP:
            deltaY = -1;
            break;
        case DOWN:
            deltaY = 1;
            break;
        case LEFT:
            deltaX = -1;
            break;
        case RIGHT:
            deltaX = 1;
            break;
        default:
            break;
    }

    bool isSwapped = true;
    Board movedBoard;
    movedBoard.listOfBox_ = listOfBox_;
    movedBoard.path_ = path_;
    movedBoard.width_ = width_;
    movedBoard.height_ = height_;

    movedBoard = movedBoard.swap(row, col, row + deltaY, col + deltaX, isSwapped);

    if (isSwapped) {
        isMoved = true;
        Move m(row, col, (Direction) dir);
        movedBoard.path_.push_back(m);
    }

    // gravity
    for (int i = 0; i < width_; i++) {
        int index_row = height_ - 1;
        int index_col = i;
        for (int j = height_ - 1; j >= 0; j--) {
            int cur_type = movedBoard.listOfBox_[getPos(j, i)];
            if (cur_type != -1) {
                movedBoard = movedBoard.swap(j, i, index_row, index_col, isSwapped);
                index_row -= 1;
            }
        }
    }

    // find clear && do clear
    while(1) {
        std::set<int> clearList;
        if (movedBoard.findClear(clearList)) {
            for (std::set<int>::iterator it = clearList.begin(); it != clearList.end(); ++it) {
                movedBoard.listOfBox_[*it] = -1;
            }
            for (int i = 0; i < width_; i++) {
                int index_row = height_ - 1;
                int index_col = i;
                for (int j = height_ - 1; j >= 0; j--) {
                    int cur_type = movedBoard.listOfBox_[getPos(j, i)];
                    if (cur_type != -1) {
                        movedBoard = movedBoard.swap(j, i, index_row, index_col, isSwapped);
                        index_row -= 1;
                    }
                }
            }
        } else {
            break;
        }
    }

    return movedBoard;
}

bool Board::win() const {
    std::map <int, int> boxCount;
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
    std::map <int, int> boxCount;
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
    for (std::map<int, int>::iterator it = boxCount.begin(); it != boxCount.end(); ++it) {
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


void Board::allPossibleMove(std::vector<Board> &allMoves, bool &findSolution) const {
    const char * direction[] = {"Up", "Down", "Left", "Right"};
    for (int row = 0; row < height_; row++) {
        for (int col = 0; col < width_; col++) {

            //move right
            Board moveRight;
            moveRight.listOfBox_ = listOfBox_;
            moveRight.path_ = path_;
            moveRight.height_ = height_;
            moveRight.width_ = width_;

            bool movedR = false;
            moveRight = moveRight.move(row, col, RIGHT, movedR);

            if (movedR) {
                if (moveRight.win()) {
                    findSolution = true;
                    std::cout << "The solution is:" << std::endl;
                    for (int path = 0; path < moveRight.path_.size(); path++) {
                        std::cout << path + 1 << " step is: " << std::endl;
                        std::cout << "the row number: " << moveRight.path_[path].row_ << std::endl;
                        std::cout << "the column number: " << moveRight.path_[path].col_ << std::endl;
                        std::cout << "move direction: " << direction[moveRight.path_[path].dir_ ]<< std::endl;
                    }
                    return;
                }
                if (moveRight.canWin()) {
                    bool storeFlag = true;
                    for (int i = 0; i < allMoves.size(); i++) {
                        if (moveRight == allMoves[i]) {
                            storeFlag = false;
                            break;
                        }
                    }
                    if (storeFlag) {
                        allMoves.push_back(moveRight);
                        //moveRight.print();
                    }
                }
            }
            // move down
            Board moveDown;
            moveDown.listOfBox_ = listOfBox_;
            moveDown.path_ = path_;
            moveDown.height_ = height_;
            moveDown.width_ = width_;

            bool moveD = false;
            moveDown = moveDown.move(row, col, DOWN, moveD);
            if (moveD) {
                if (moveDown.win()) {
                    findSolution = true;
                    std::cout << "The solution is:" << std::endl;
                    for (int path = 0; path < moveDown.path_.size(); path++) {
                        std::cout << path + 1 << " step is: " << std::endl;
                        std::cout << "the row number: " << moveDown.path_[path].row_ << std::endl;
                        std::cout << "the column number: " << moveDown.path_[path].col_ << std::endl;
                        std::cout << "move direction: " << direction[moveDown.path_[path].dir_ ]<< std::endl;
                    }
                    return;
                }

                if (moveDown.canWin()) {
                    bool storeFlag = true;
                    for (int i = 0; i < allMoves.size(); i++) {
                        if (moveDown == allMoves[i]) {
                            storeFlag = false;
                            break;
                        }
                    }
                    if (storeFlag) {
                        allMoves.push_back(moveDown);
                    }
                }
            }
        }
    }

}