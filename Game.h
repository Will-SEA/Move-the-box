//
// Created by yuanhao on 6/17/16.
//

#ifndef MOVE_THE_BOX_GAME_H
#define MOVE_THE_BOX_GAME_H

#include <set>
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
    void play();

    /*
     * Method:          void findSolution()
     * Description:     this method is used to find the solution of the game.
     * */
    void findSolution();


    /*
     * Method:          ~Game()
     * Description:     destrctor of the Game class.
     * */
    ~Game();


private:

    // width of the game board
    int width_;

    // height of the game board
    int height_;

    // game board
    Board gameBoard_;

    /*
     * Method:          void print(Board board) const;
     * Description:     this method will print the game board
     * Parameter:       the gameBoard
     * */
    void print(Board board) const;

    /*
     * Method:          Board move(Board board,int row, int col, int dir)
     * Description:     this method is used to move the box based on the user input
     * Parameters:      the first element is a gameBoard, all the other three parameters are integer, the first 2 are
     *                  position of box that user wants to move, the third one is the direction that user want to move.
     *                  note: 0-up, 1-down, 2-left, 3-right.
     * */
    bool move(Board &board, int row, int col, int dir);

    /*
     * Method:          Board simulateMove(Board &board, int row, int col, int dir)
     * Description:     this method is used to simulate the move action and each time return a new moved board.
     * Parameters:      the first element is a gameBoard, all the other three parameters are integer, the first 2 are
     *                  position of box that user wants to move,
     *                  the third one is the direction that user want to move. note: 0-up, 1-down, 2-left, 3-right.
     * */
    Board simulateMove(Board &board, int row, int col, int dir);

    /*
     * Method:          bool swap(Board &board, int row1, int col1, int row2, int col2)
     * Description:     this method will swap the type of 2 boxes
     * Parameters:      the first element represents the game board.
     *                  all the other 4 parameters are integer, the first 2 are the position of first box, and the
     *                  other 2 are the position of second box.
     * */
    bool swap(Board &board, int row1, int col1, int row2, int col2);

    /*
     * Method:          bool findClear(Board board, set<int> &list);
     * Description:     this method is used to traverse the game board, and find is there any consecutive boxes, and
     *                  the number is over 3. This traverse method will traverse 2 twice, the one is vertical direction,
     *                  the other one is horizontal direction. the main idea is like 2 pointers.
     * Parameters:      the first element is the game board, the second element will store the box that needs to be cleared
     * */
    bool findClear(Board board, set<int> &list);

    /*
     * Method:          void doClear(Board board, const set<int> &list)
     * Description:     this method is used to executive the clear action, it will set all the boxes, that need to be
     *                  clear, to empty, which is -1
     * Parameters:      the first element is the game board, the second element stores the position of the box that
     *                  needs to be cleared
     * */
    void doClear(Board &board, const set<int> &list);

    /*
     * Method:          void gravity(Board board)
     * Description:     this method is used to traverse the game board, and find is there any box that has no support.
     *                  if this box cannot be hold up, it will falling down until it can be hold up.
     * Parameters:      the element is the game board
     * */
    void gravity(Board &board);

    /*
     * Method:          bool win(Board board) const;
     * Description:     this method is used to check whether user wins the game. The idea is to traverse the boxCount
     *                  map, if this map is empty, it means the game board is empty, so user wins, and then return true,
     *                  otherwise, return false.
     * Parameters:      the element is the game board
     * */
    bool win(Board board) const;

    /*
     * Method:          bool canWin(Board board)
     * Description:     this method is used to check whether user still can win the game. The idea is to traverse the
     *                  boxCount map, if any type of box that the number is lower than 3, then return false. otherwise,
     *                  user still can win, and game continue, return true.
     * Parameters:      the element is the game board
     * */
    bool canWin(Board board);

    /*
     * Method:          getPos(int row, int col)
     * Description:     this method will return the position of certain box with row and col in the 1D vector
     * Parameters:      row is the row number of the box in the game board and the col is the column number.
     */
    int getPos(int row, int col) const;



    /*
     * Method:          void allPossibleMove(vector<Board> &solution, int position);
     * Description:     this method is a recursion method to find the optimum solution of the game board.
     * Parameters:      the first element is a vector of Board, it stores the each kind of move, the second parameter is
     *                  the recursion times.
     * */
    void allPossibleMove(vector<Board> &solution, int position);

/*
    *//*
     * Method:          bool isSameBoard(Board board1, Board board2)
     * Description:
     * Parameters:
     * *//*
    bool isSameBoard(Board board1, Board board2);*/


};


#endif //MOVE_THE_BOX_GAME_H
