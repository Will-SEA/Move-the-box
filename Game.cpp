//
// Created by yuanhao on 6/21/16.
//

#include "Game.h"

Game::Game() { }

Game::~Game() { }

void Game::play() {
    while (1) {
        std::cout << "Please enter the position of the box that you want to move and the direction " << std::endl;
        std::cout << "NOTE: UP:0, DOWN:1, LEFT:2, RIGHT:3" << std::endl;
        gameBoard_.print();
        int row, col, dir;


        std::cin >> row >> col >> dir;

        bool isMoved = false;

        gameBoard_.move(row, col, dir, isMoved);

        if (isMoved) {
            gameBoard_ = gameBoard_.move(row, col, dir, isMoved);
            if(gameBoard_.win()) {
                std::cout << "You Win!" << std::endl;
                break;
            }

            if(!gameBoard_.canWin()) {
                std::cout << "You lose!" << std::endl;
                break;
            }

        } else {
            std::cout << "move action invalid" << std::endl;
            continue;
        }
    }
}

void Game::findSolution() {
    std::vector<Board> allPossibleMove;
    allPossibleMove.push_back(gameBoard_);
    int index = 0;

    do {
        Board curBoard = allPossibleMove[index];
        bool findSolution = false;
        curBoard.allPossibleMove(allPossibleMove, findSolution);
        if (findSolution) {
            std::cout << std::endl;
            std::cout << "possible boards: " << allPossibleMove.size() << std::endl;
            std::cout << "the loop times: " << index + 1 << std::endl;
            break;
        }
        index++;
    } while(index < allPossibleMove.size());
}

// board class find all move

