//
// Created by Christoph Manucredo on 10.05.20.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <random>


#ifndef SUDOKUSOLVER_BOARD_H
#define SUDOKUSOLVER_BOARD_H


class Board {

public:
    Board();
    void printBoard();  //prints the completed sudoku board
    void generateBoard();   //generates a sudoku board
    void createPuzzle(int difficulty);    //transforms a coherent sudoku board to a puzzle
    void findMissingNumbers(); //finds missing number of a sudoku puzzle
    void solvePuzzle(); //actually solves the puzzle
    void checkSolution();

private:

    static const int sudokuSize = 9;
    static const int sudokuPatch = 3;
    int allNumbers[sudokuSize][sudokuSize];
    int originalNumbers[sudokuSize][sudokuSize];
    int finishedBoard[sudokuSize][sudokuSize];

    std::vector<int> numberVector;

    bool checkRow(int colNumber, int value);
    bool checkColumn(int rowNumber, int value);

    void fillNumbersVector(int batchSize); //fills one vector with numbers from 1 to batchSize
    void eraseCell(int totalNumber);    //erases a "block" of numbers
    void refillCell(int totalNumber); //refills a "block" of numbers -> will be refactored to include the above function
    void createVectors();               //creates the vector that holds all other vectors
    void jumbleVectors(int cellNumber); //jumbles a vector

    std::vector<std::vector<int>> cellVectors;      //vector that holds all vectors for the blocks
    std::vector<std::vector<int>> missingNumbersVec;    //vector that holds all vectors with the missing numbers

};


#endif //SUDOKUSOLVER_BOARD_H
