#include <iostream>
#include "Board.h"
#include <chrono>

int main() {

    //initializing a board
    Board newBoard;

    //start time of generation
    auto start = std::chrono::high_resolution_clock::now();

    //creating a coherent sudoku board
    newBoard.generateBoard();

    //stop time of generation
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    //printing the board
    newBoard.printBoard();

    //printing generation duration
    std::cout << std::endl;
    std::cout << "Generating the sudoku board took: " << duration.count() << " ms" << std::endl;

    //create the puzzle
    std::cout << std::endl;
    newBoard.createPuzzle(3);
    newBoard.printBoard();

    //solve the puzzle

    newBoard.solvePuzzle();
    newBoard.printBoard();


    return 0;
}
