//
// Created by Christoph Manucredo on 10.05.20.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
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

private:

    static const int sudokuSize = 9;
    const int sudokuPatch = std::sqrt(sudokuSize);
    int allNumbers[sudokuSize][sudokuSize];

    std::vector<int> nineNumbers;

    bool checkRow(int colNumber, int value);
    bool checkColumn(int rowNumber, int value);

    void fillNumbersVector(int batchSize);
    void eraseCell(int totalNumber);
    void createVectors();

    std::vector<std::vector<int>> cellVectors;

};


#endif //SUDOKUSOLVER_BOARD_H
