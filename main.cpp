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

    std::cout << std::endl << "This is the generated Board:" << std::endl;
    //printing the board
    newBoard.printBoard();

    //printing generation duration
    std::cout << std::endl;
    std::cout << "Generating the sudoku board took: " << duration.count() << " ms" << std::endl;

    //create the puzzle
    std::cout << std::endl;
    newBoard.createPuzzle(2);

    std::cout << std::endl << "This is the generated puzzle:" << std::endl;
    newBoard.printBoard();

    //solve the puzzle

    //time the finding of the missing numbers
    start = std::chrono::high_resolution_clock::now();

    //finding the missing numbers
    newBoard.findMissingNumbers();

    //stop time, duration and log of the time
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << std::endl;
    std::cout << "Finding the missing numbers took : " << duration.count() << " ms" << std::endl << std::endl;


    //actually solve the puzzle

    //time the solving
    start = std::chrono::high_resolution_clock::now();

    //solve it
    newBoard.solvePuzzle();
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);


    std::cout << "Solving the puzzle took " << duration.count() << " ms." << std::endl;
    std::cout << std::endl << "This is the solution:" << std::endl;
    newBoard.printBoard();

    return 0;
}
