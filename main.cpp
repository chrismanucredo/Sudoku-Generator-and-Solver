/*
 * Copyright (C) Christoph Manucredo, 26.05.2020
 * chris.manucredo@gmail.com
 *
 * This work is licensed under the Attribution 4.0 International (CC BY 4.0) Creative Commons license.
 * Read more about it here: https://creativecommons.org/licenses/by/4.0/
 *
 */


#include <iostream>
#include "Board.h"
#include <chrono>

int main() {

    //initializing a board
    Board newBoard;

    //creating a coherent sudoku board
    newBoard.generateBoard();

    std::cout << std::endl << "This is the generated Board:" << std::endl;
    //printing the board
    newBoard.printBoard();

    //create the puzzle
    std::cout << std::endl;
    newBoard.createPuzzle(2);

    std::cout << std::endl << "This is the generated puzzle:" << std::endl;
    newBoard.printBoard();


    //finding the missing numbers
    newBoard.findMissingNumbers();

    //solve it
    newBoard.solvePuzzle();

    std::cout << std::endl << "This is the solution:" << std::endl;
    newBoard.printBoard();

    newBoard.checkSolution();

    return 0;
}
