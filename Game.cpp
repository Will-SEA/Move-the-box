//
// Created by yuanhao on 6/21/16.
//

#include "Game.h"

Game::Game() {
    std::cout << "Welcome to Move the Box game!" << std::endl;
    std::cout << "A logic puzzle about moving boxes around. Clean the dock, do it fast!" << std::endl;
    std::cout << "You can move, drop and swap the boxes." << std::endl;
    std::cout << "Three or more boxes of the same kind in a line disappear!" << std::endl << std::endl;
    std::cout << "Please input the level that you want to play. " << "We have 10 levels" << std::endl;

    std::string level;
    std::cin >> level;
    filePath_ = "Level/" + level + ".txt";
}

Game::~Game() { }

void Game::play() const {
    Board gameBoard = Board(filePath_);
    while (1) {
        std::cout << "Please enter the position of the box that you want to move and the direction " << std::endl;
        std::cout << "NOTE: UP:0, DOWN:1, LEFT:2, RIGHT:3" << std::endl;
        gameBoard.print();

        int row, col, dir;
        std::cin >> row >> col >> dir;

        bool isMoved;
        gameBoard.move(row, col, dir, isMoved);

        if (isMoved) {
            gameBoard = gameBoard.move(row, col, dir, isMoved);
            if(gameBoard.win()) {
                std::cout << "You Win!" << std::endl;
                break;
            }
            if(!gameBoard.canWin()) {
                std::cout << "You lose!" << std::endl;
                break;
            }
        } else {
            std::cout << "move action invalid" << std::endl;
            continue;
        }
    }
}

void Game::findSolution() const{
    const char * direction[] = {"Up", "Down", "Left", "Right"};
    Board gameBoard = Board(filePath_);
    std::vector<Board> allPossibleMove;
    allPossibleMove.push_back(gameBoard);
    int index = 0;

    do {
        Board curBoard = allPossibleMove[index];

        Board tmpBoard = curBoard.findAllMove(allPossibleMove);
        if (tmpBoard.isValidBoard()) {
            std::cout << std::endl;
            std::cout << "Already find the solution!" << std::endl;
            std::cout << "The solution is:" << std::endl;
            for (int path = 0; path < tmpBoard.pathSize(); path++) {
                std::cout << path + 1 << " step is: " << std::endl;
                std::cout << "the row number: " << tmpBoard.getPath(path).row_ << std::endl;
                std::cout << "the column number: " << tmpBoard.getPath(path).col_ << std::endl;
                std::cout << "move direction: " << direction[tmpBoard.getPath(path).dir_ ]<< std::endl;
            }
            std::cout << std::endl;
            std::cout << "possible boards: " << allPossibleMove.size() << std::endl;
            std::cout << "the loop times: " << index + 1 << std::endl;
            break;
        }

        index++;
    } while(index < allPossibleMove.size());
}


