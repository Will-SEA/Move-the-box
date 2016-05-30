//
// Created by yuanhao on 5/22/16.
//

#ifndef MOVE_THE_BOX_BOX_H
#define MOVE_THE_BOX_BOX_H
#include <iostream>

using namespace std;

class Box {
private:
    // box type, default value is -1, which means empty box
    int type;

    // the row number of this box in the game board
    int row;

    // the column number of this box in the game board
    int col;

public:
    /*
     * Method:          Box();
     * Description:     this is the default constructor for the box class, user can use this method to initialize a
     *                  empty box, i.e. type equal -1. And both of the column and row will be set as empty
     * */
    Box();

    /*
     * Method:          Box(int type);
     * Description:     this is the constructor that has one parameter
     * Parameters:      the input parameter is an integer which will define the type of box. Type can only be -1, or
     *                  non-negative number
     * */
    Box(int type);

    /*
     * Method:          Box(int type, int row, int col)
     * Description:     this is the constructor that has three parameter
     * Parameters:      all the three parameters are integer, the first parameter is the type of the box,
     *                  and the rest two parameters define the position of this box in the game board
     */
    Box(int type, int row, int col);

    /*
     * Method:          getType()
     * Description:     this method will return the type of the box
     */
    int getType() const;

    /*
     * Method:          setType()
     * Description:     this method will define the type of the box
     * Parameters:      the parameter is a integer, and it will be the new type of the box
     */
    void setType(int type);

    /*
     * Method:          setPosition()
     * Description:     this method will set the position of the box in the game board, the default value is (-1, -1)
     * Parameters:      two parameters are both integer, the first is row, the second is column
     */
    void setPosition(int row, int col);

    /*
     * Method:          getCol()
     * Description:     this method will return the current column value of the box
     */
    int getCol() const;

    /*
     * Method:          getRow()
     * Description:     this method will return the current row value of the box
     */
    int getRow() const;

    /*
     * Method:          ~Box()
     * Description:     default deconstructor, since I didn't use any dynamic memory, it's empty now
     */
    ~Box();
};


#endif //MOVE_THE_BOX_BOX_H
