//
// Created by yuanhao on 6/21/16.
//

#ifndef MOVETHEBOX_GAME_H
#define MOVETHEBOX_GAME_H

#include "Board.h"


class Game {
public:
    /*
     * Method:          Game()
     * Description:     default constructor. User could use this method to initialize a new game board. It will read
     *                  the game board from a txt file,
     * */
    Game();

    /*
     * Method:          play()
     * Description:     this is the main function of the class, it will assemble the other functions of the game
     * */
    void play() const;

    /*
     * Method:          void findSolution()
     * Description:     this method is used to find the solution of the game.
     * */
    void findSolution() const;


    /*
     * Method:          ~Game()
     * Description:     de-constrctor of the Game class.
     * */
    ~Game();

private:
    // file path
    std::string filePath_;
};


#endif //MOVETHEBOX_GAME_H
