//
// Created by yuanhao on 6/21/16.
//

#include "Board.h"

Board::Move::Move(int row, int col, Direction dir): row_(row), col_(col), dir_(dir) { }


Board::Board() {
    height_ = -1;
    width_ = -1;
}

Board::Board(std::vector<int> listOfBox, std::vector<Move> path, int width, int height): listOfBox_(listOfBox),
                                                                                         path_(path),
                                                                                         width_(width),
                                                                                         height_(height) { }

Board::Board(const Board &board) {
    listOfBox_ = board.listOfBox_;
    path_ = board.path_;
    width_ = board.width_;
    height_ = board.height_;
}

Board::Board(const std::string &filePath) {
    std::ifstream infile(filePath);
    if (infile.fail()) {
        std::cout << "Input file opening failed" << std::endl;
    }
    std::string str;
    int rowNum = 0;
    int widthCheck = 0;
    while (getline(infile, str)) {
        int colNum = 0;
        std::istringstream level(str);
        std::string type;
        while (level >> type) {
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
                std::cout.flags(std::ios::right); //right alignment
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

bool Board::isValidBoard() const {
    return !(width_ == -1 || height_ == -1);
}


std::set<int> Board::findClearBox(const std::vector<int> &tmpBoard) const {
    int consec_count = 0;
    std::set<int> clearList;

    //find consecutive horizontal matches
    for(int i = 0 ; i < height_ ; i++){
        int last_type = tmpBoard[getPos(i, 0)];
        int start_col = 0;
        for(int j  = 1 ; j < width_ ; j++){
            int cur_type = tmpBoard[getPos(i, j)];
            if(cur_type == last_type && cur_type > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int col = start_col; col < j; col++) {
                        clearList.insert(getPos(i, col));
                    }
                }
                last_type = tmpBoard[getPos(i, j)];
                start_col = j;
                consec_count = 0;
            }
        }
        if(consec_count >= 2){

            for (int col = start_col; col < width_; col++) {
                clearList.insert(getPos(i, col));
            }
        }
        consec_count = 0;
    }

    //find consecutive vertical matches
    for(int j = 0; j < width_; j++){
        int last_type = tmpBoard[getPos(0, j)];
        int start_row = 0;
        for(int i  = 1 ; i < height_ ; i++){
            int cur_type = tmpBoard[getPos(i, j)];
            if(cur_type == last_type && cur_type > -1 ){
                consec_count++;
            }else{
                if(consec_count >= 2){
                    for (int row = start_row; row < i; row++) {
                        clearList.insert(getPos(row, j));
                    }
                }
                last_type = tmpBoard[getPos(i, j)];
                start_row = i;
                consec_count = 0;
            }
        }
        if(consec_count >= 2){
            for (int row = start_row; row < height_; row++) {
                clearList.insert(getPos(row, j));
            }
        }
        consec_count = 0;
    }
    return clearList;
}

bool Board::canSwap(int row1, int col1, int row2, int col2) const {
    if (boxAt(row1, col1) == boxAt(row2, col2)) {
        return false;
    }

    if (row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0
        || row1 >= height_ || col1 >= width_ || row2 >= height_ || col2 >= width_) {
        return false;
    }

    return true;
}

std::vector<int> Board::swap(int row1, int col1, int row2, int col2) const {
    std::vector<int> newListOfBox = listOfBox_;

    int type = newListOfBox[getPos(row2, col2)];
    newListOfBox[getPos(row2, col2)] = newListOfBox[getPos(row1, col1)];
    newListOfBox[getPos(row1, col1)] = type;

    return newListOfBox;
}

Board Board::move( int row, int col, int dir, bool &isMoved) const {
    isMoved = false;

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


    std::vector<Move> path = path_;
    std::vector<int> listOfBox = listOfBox_;

    if(canSwap(row, col, row + deltaY, col + deltaX)) {
        listOfBox = swap(row, col, row + deltaY, col + deltaX);
        Move m(row, col, (Direction) dir);
        path.push_back(m);
        isMoved = true;
    } else {
        isMoved = false;
        return Board(listOfBox, path, width_, height_);
    }

    // gravity
    gravity(listOfBox);

    // find clear && do clear
    while(1) {
        std::set<int> clearList = findClearBox(listOfBox);
        if (!clearList.empty()) {
            for (std::set<int>::iterator it = clearList.begin(); it != clearList.end(); ++it) {
                listOfBox[*it] = -1;
            }
            if (!gravity(listOfBox)) {
                break;
            }
        } else {
            break;
        }
    }

    return Board(listOfBox, path, width_, height_);
}

bool Board::gravity(std::vector<int> &tmpBoard) const {
    bool doGravity = false;
    for (int i = 0; i < width_; i++) {
        int index_row = height_ - 1;
        int index_col = i;
        for (int j = height_ - 1; j >= 0; j--) {
            int cur_type = tmpBoard[getPos(j ,i)];
            if (cur_type != -1) {
                int type = tmpBoard[getPos(index_row, index_col)];
                tmpBoard[getPos(index_row, index_col)] = tmpBoard[getPos(j ,i)];
                tmpBoard[getPos(j ,i)] = type;
                index_row -= 1;
                doGravity = true;
            }
        }
    }
    return doGravity;
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

Board Board::findAllMove(std::vector<Board> &allMoves) const {
    for (int row = 0; row < height_; row++) {
        for (int col = 0; col < width_; col++) {
            std::vector<int> dir = {1, 3};
            for (int i = 0; i < dir.size(); i++) {
                bool canMove;
                Board movedBoard = move(row, col, dir[i], canMove);
                if (canMove) {
                    if (movedBoard.win()) {
                        return movedBoard;
                    }
                    if (movedBoard.canWin()) {
                        bool storeFlag = true;
                        for (int i = 0; i < allMoves.size(); i++) {
                            if (movedBoard == allMoves[i]) {
                                storeFlag = false;
                                break;
                            }
                        }
                        if (storeFlag) {
                            allMoves.push_back(movedBoard);
                        }
                    }
                }
            }
        }
    }
    return Board();
}

int Board::getPos(int row, int col) const {
    return row * width_ + col;
}

int Board::boxAt(int row, int col) const {
    return listOfBox_[getPos(row, col)];
}

unsigned long Board::pathSize() const {
    return path_.size();
}

Board::Move Board::getPath(int step) const {
    return path_[step];
}