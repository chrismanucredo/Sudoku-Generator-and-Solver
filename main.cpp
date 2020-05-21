#include <iostream>
#include "Board.h"

int main() {

    //initializing a board
    Board newBoard;

    //creating a coherent sudoku board
    newBoard.generateBoard();

    //printing the board
    newBoard.printBoard();


    return 0;
}
