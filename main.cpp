#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    cout << "Welcome to Move the Box game!" << endl;
    cout << "A logic puzzle about moving boxes around. Clean the dock, do it fast!" << endl;
    cout << "You can move, drop and swap the boxes." << endl;
    cout << "Three or more boxes of the same kind in a line disappear!" << endl << endl;
    Game game;
    //game.play();
    game.findSolution();

    return 0;
}