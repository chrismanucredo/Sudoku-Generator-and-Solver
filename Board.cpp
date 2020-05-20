//
// Created by Christoph Manucredo on 10.05.20.
//

#include "Board.h"

Board::Board() {

    std::srand(unsigned(std::time(0))); //initialize random seed

    createVectors();

    for (int i = 0; i < sudokuSize; ++i) {
        for (int j = 0; j < sudokuSize; ++j) {
            allNumbers[i][j] = 0;
        }
    }
}

void Board::printBoard() {
    std::cout << "BOARD INCOMING" << std::endl;
    for (int i = 0; i < sudokuSize; ++i) {
        if (i % sudokuPatch == 0){
            std::cout << "-------------------------" << std::endl;
        }
        for (int j = 0; j < sudokuSize; ++j) {
            if (j % sudokuPatch == 0){
                std::cout << "| ";
            }
            std::cout << allNumbers[i][j] << " ";
        }
        std::cout << "| " << std::endl;
    }

    std::cout << "BOARD COMPLETED" << std::endl;
}

void Board::generateBoard() {

    bool numberFound = false;
    int totalNumber = 0;
    int repetitionCounter;

    for (int i = 0; i < sudokuSize; ++i) {

        for (int j = 0; j < sudokuSize; ++j) {
            numberFound = false;

            while(!numberFound){
                int row = (totalNumber / sudokuPatch) % sudokuSize;
                int col = (totalNumber % sudokuPatch) % sudokuSize +
                          (totalNumber / (sudokuPatch * sudokuSize)) * sudokuPatch;

                if (checkColumn(col, cellVectors[i][0]) && checkRow(row, cellVectors[i][0])) {
                    numberFound = true;
                    allNumbers[row][col] = cellVectors[i][0];
                    cellVectors[i].erase(cellVectors[i].begin());
                    totalNumber = totalNumber + 1;
                    repetitionCounter = 0;
                } else {
                    int temp = cellVectors[i][0];
                    cellVectors[i].erase(cellVectors[i].begin());
                    cellVectors[i].push_back(temp);
                    repetitionCounter++;

                    //backtracking if no numbers can be filled
                    if (repetitionCounter > sudokuSize){

                        //resetting the current cellvector
                        fillNumbersVector(sudokuSize);
                        cellVectors[i].clear();
                        for (int k = 0; k < sudokuSize; ++k) {
                            cellVectors[i].push_back(nineNumbers[k]);
                        }

                        //resetting the previous cellvector
                        fillNumbersVector(sudokuSize);
                        for (int k = 0; k < sudokuSize; ++k) {
                            cellVectors[i-1].push_back(nineNumbers[k]);
                        }

                        //erasing current cell
                        totalNumber = (totalNumber / sudokuSize) * 9;
                        i = i - 1;
                        j = 0;

                        eraseCell(totalNumber);

                        //switching back to the previous block
                        totalNumber = totalNumber - sudokuSize;

                        //erasing previous cell
                        eraseCell(totalNumber);


                        repetitionCounter = 1;
                    }
                }
            }
        }
    }
}

//returns false if the number already exists in the column
bool Board::checkColumn(int colNumber, int value) {
    for (int i = 0; i < sudokuSize; ++i) {
        if (allNumbers[i][colNumber] == value){
            return false;
        }
    }
    return true;
}

//returns false if the number already exists in the row
bool Board::checkRow(int rowNumber, int value) {
    for (int i = 0; i < sudokuSize; ++i) {
        if (allNumbers[rowNumber][i] == value){
            return false;
        }
    }
    return true;
}

void Board::fillNumbersVector(int batchSize) {

    nineNumbers.clear();

    for (int i = 1; i < batchSize + 1; ++i) { //fill vector with number 1- batchsize
        nineNumbers.push_back(i);
    }

    int sizeOfVector = nineNumbers.size();
    for (int k = 0; k < sizeOfVector; ++k) { //shuffle the vector
        int r = k + rand() % (sizeOfVector - k);
        std::swap(nineNumbers[k], nineNumbers[r]);
    }

}

void Board::createVectors() {

    cellVectors.clear();
    for (int i = 0; i < sudokuSize; ++i) {
        fillNumbersVector(sudokuSize);
        cellVectors.push_back(nineNumbers);
    }

}

void Board::eraseCell(int totalNumber) {

    int row = (totalNumber / sudokuPatch) % sudokuSize;
    int col = (totalNumber % sudokuPatch) % sudokuSize +
          (totalNumber / (sudokuPatch * sudokuSize)) * sudokuPatch;

    for (int l = row; l < row + sudokuPatch; ++l) {
        for (int k = col; k < col + sudokuPatch; ++k) {
            allNumbers[l][k] = 0;
        }
    }
}







