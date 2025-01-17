//
// Created by Christoph Manucredo on 10.05.20.
//

#include "Board.h"

//constructs the intial board
Board::Board() {

    std::srand(unsigned(std::time(0))); //initialize random seed

    //creates the vector which holds all vectors used for the cells
    createVectors();

    //creates an "empty" board, meaning that all places are filled with zeros
    for (int i = 0; i < sudokuSize; ++i) {
        for (int j = 0; j < sudokuSize; ++j) {
            allNumbers[i][j] = 0;
        }
    }
}

//prints the board
void Board::printBoard() {

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

    std::cout << "-------------------------" << std::endl;

}

//this is the actual board generation
void Board::generateBoard() {

    //this bool is used to track if a number fits in the current place
    bool numberFound = false;

    //is used to track which place in the board is being handled
    int totalNumber = 0;

    //is used to keep track of when "backtracking" should occur
    int repetitionCounter = 0;

    //iterates over the cells - not over rows and columns
    for (int i = 0; i < sudokuSize; ++i) {

        for (int j = 0; j < sudokuSize; ++j) {

            numberFound = false;

            while(!numberFound){
                //probably way too complicated way to determine where in the board we are at the moment
                int row = (totalNumber / sudokuPatch) % sudokuSize;
                int col = (totalNumber % sudokuPatch) % sudokuSize +
                          (totalNumber / (sudokuPatch * sudokuSize)) * sudokuPatch;

                //checks if the row OR the column already contains the current number
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

                    //backtracking if no numbers can be filled after trying every number that is in the current
                    //cell vector
                    if (repetitionCounter > cellVectors[i].size()-1){

                        //resetting the current cellvector
                        fillNumbersVector(sudokuSize);
                        cellVectors[i].clear();
                        for (int k = 0; k < sudokuSize; ++k) {
                            cellVectors[i].push_back(numberVector[k]);
                        }

                        //resetting the previous cellvector
                        fillNumbersVector(sudokuSize);
                        for (int k = 0; k < sudokuSize; ++k) {
                            cellVectors[i-1].push_back(numberVector[k]);
                        }

                        //erasing current cell
                        totalNumber = (totalNumber / sudokuSize) * 9;
                        eraseCell(totalNumber);

                        //taking a step back by one cell
                        i = i - 1;
                        j = 0;
                        totalNumber = totalNumber - sudokuSize;

                        //erasing previous cell
                        eraseCell(totalNumber);

                        repetitionCounter = 1;
                    }
                }
            }
        }
    }
    for (int l = 0; l < sudokuSize; ++l) {
        for (int i = 0; i < sudokuSize; ++i) {
            finishedBoard[l][i] = allNumbers[l][i];
        }

    }
}

//returns false if the number "value" already exists in the column
bool Board::checkColumn(int colNumber, int value) {
    for (int i = 0; i < sudokuSize; ++i) {
        if (allNumbers[i][colNumber] == value){
            return false;
        }
    }
    return true;
}

//returns false if the number "value" already exists in the row
bool Board::checkRow(int rowNumber, int value) {
    for (int i = 0; i < sudokuSize; ++i) {
        if (allNumbers[rowNumber][i] == value){
            return false;
        }
    }
    return true;
}

//fills the numberVector with the numbers needed for one cell
void Board::fillNumbersVector(int batchSize) {

    numberVector.clear();

    for (int i = 1; i < batchSize + 1; ++i) { //fill vector with number 1- batchsize
        numberVector.push_back(i);
    }

    //shuffles the vector
    int sizeOfVector = numberVector.size();
    for (int k = 0; k < sizeOfVector; ++k) { //shuffle the vector
        int r = k + rand() % (sizeOfVector - k);
        std::swap(numberVector[k], numberVector[r]);
    }

}

//creates the vector which holds all vectors used for the cells
void Board::createVectors() {

    cellVectors.clear();
    for (int i = 0; i < sudokuSize; ++i) {
        fillNumbersVector(sudokuSize);
        cellVectors.push_back(numberVector);
    }

}

//erases a complete cell. the cell is determined by the "totalnumber", which states where in the array
//the algorithm is operating at the moment
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

void Board::refillCell(int totalNumber) {

    int row = (totalNumber / sudokuPatch) % sudokuSize;
    int col = (totalNumber % sudokuPatch) % sudokuSize +
              (totalNumber / (sudokuPatch * sudokuSize)) * sudokuPatch;

    for (int l = row; l < row + sudokuPatch; ++l) {
        for (int k = col; k < col + sudokuPatch; ++k) {
            allNumbers[l][k] = originalNumbers[l][k];
        }
    }
}

//creates a puzzle from a generated sudoku chart
//difficulty is between 1 - 4 with 1 being the hardest.
void Board::createPuzzle(int difficulty) {

    int randomNumber;
    int counter = 0;
    int totalSudokuSize = sudokuSize * sudokuSize;
    bool breaker = false;

    for (int i = 0; i < sudokuSize; ++i) {
        if (breaker){
            break;
        }
        for (int j = 0; j < sudokuSize; ++j) {

            randomNumber = rand() % 5;

            if (randomNumber >= difficulty){

                allNumbers[i][j] = 0;
                counter++;

                if((totalSudokuSize - counter) == 17){
                    breaker = true;
                    break;
                }
            }
        }
    }

    std::cout << "This many numbers have been deleted: " << counter << std::endl;

}

void Board::findMissingNumbers() {
    int totalNumber = 0;
    bool numberFound = false;
    int repetitionCounter;

    createVectors();

    for (int i = 0; i < sudokuSize; ++i) {


        for (int j = 0; j < sudokuSize; ++j) {

            numberFound = false;
            repetitionCounter = 0;



            while (!numberFound && (repetitionCounter < sudokuSize)) {
                //probably way too complicated way to determine where in the board we are at the moment
                int row = (totalNumber / sudokuPatch) % sudokuSize;
                int col = (totalNumber % sudokuPatch) % sudokuSize +
                          (totalNumber / (sudokuPatch * sudokuSize)) * sudokuPatch;

                if (allNumbers[row][col] == 0){
                    break;
                }

                if(cellVectors[i][0] == allNumbers[row][col]){
                    cellVectors[i].erase(cellVectors[i].begin());
                    numberFound = true;
                } else {
                    int temp = cellVectors[i][0];
                    cellVectors[i].erase(cellVectors[i].begin());
                    cellVectors[i].push_back(temp);
                }

            }
            totalNumber = totalNumber + 1;
        }
    }

    missingNumbersVec.clear();
    for (int m = 0; m < sudokuSize; ++m) {
        missingNumbersVec.push_back(cellVectors[m]);
    }

    for (int l = 0; l < sudokuSize; ++l) {
        for (int i = 0; i < sudokuSize; ++i) {
            originalNumbers[l][i] = allNumbers[l][i];
        }
    }



}

void Board::solvePuzzle() {

    int stupidCounter = 0;

    //this bool is used to track if a number fits in the current place
    bool numberFound = false;

    //is used to track which place in the board is being handled
    int totalNumber = 0;

    //is used to keep track of when "backtracking" should occur
    int repetitionCounter = 0;

    //original Puzzle
    for (int l = 0; l < sudokuSize; ++l) {
        for (int i = 0; i < sudokuSize; ++i) {
            allNumbers[l][i] = originalNumbers[l][i];
        }
    }

    //copy missing numbers
    cellVectors.clear();
    for (int m = 0; m < sudokuSize; ++m) {
        cellVectors.push_back(missingNumbersVec[m]);
    }

    //jumble missing numbers vec
    for (int n = 0; n < sudokuSize; ++n) {
        jumbleVectors(n);
    }

    //iterates over the cells - not over rows and columns
    for (int i = 0; i < sudokuSize; ++i) {

        for (int j = 0; j < sudokuSize; ++j) {

            numberFound = false;
            repetitionCounter = 0;

            while(!numberFound){
                //

                //probably way too complicated way to determine where in the board we are at the moment
                int row = (totalNumber / sudokuPatch) % sudokuSize;
                int col = (totalNumber % sudokuPatch) % sudokuSize +
                          (totalNumber / (sudokuPatch * sudokuSize)) * sudokuPatch;

                if (allNumbers[row][col] != 0){
                    totalNumber = totalNumber + 1;
                    break;
                }

                if (checkRow(row, cellVectors[i][0]) && checkColumn(col, cellVectors[i][0])){
                    allNumbers[row][col] = cellVectors[i][0];
                    cellVectors[i].erase(cellVectors[i].begin());
                    numberFound = true;
                    totalNumber = totalNumber + 1;

                } else {
                    int temp = cellVectors[i][0];
                    cellVectors[i].erase(cellVectors[i].begin());
                    cellVectors[i].push_back(temp);
                    repetitionCounter++;

                    //starting backtracking
                    if (repetitionCounter > cellVectors[i].size()) {
                        stupidCounter++;


                        //reset current cell vector
                        cellVectors[i].clear();
                        for (int k = 0; k < missingNumbersVec[i].size(); ++k) {
                            cellVectors[i].push_back(missingNumbersVec[i][k]);
                        }

                        totalNumber = (totalNumber / sudokuSize) * 9;
                        refillCell(totalNumber);


                        //jumble the current vector
                        jumbleVectors(i);

                        //taking a step back by one cell
                        i = i - 1;
                        j = 0;
                        totalNumber = totalNumber - sudokuSize;

                        if (totalNumber < 0){
                            totalNumber = 0;
                        }

                        if (i < 0){
                            i = 0;
                        }

                        //reset previous vector
                        cellVectors[i].clear();
                        for (int k = 0; k < missingNumbersVec[i].size(); ++k) {
                            cellVectors[i].push_back(missingNumbersVec[i][k]);
                        }

                        //jumble the previous vector
                        jumbleVectors(i);

                        refillCell(totalNumber);

                        if (stupidCounter > sudokuSize * 2){
                            solvePuzzle();
                            stupidCounter = 0;
                        }



                    }
                }
            }
        }
    }
}

void Board::jumbleVectors(int cellNumber) {

    //shuffles the vector
    int sizeOfVector;

    sizeOfVector = cellVectors[cellNumber].size();
    for (int i = 0; i < sizeOfVector; ++i) {
        int r = i + rand() % (sizeOfVector - i);
        std::swap(cellVectors[cellNumber][i], cellVectors[cellNumber][r]);

    }
}

void Board::checkSolution() {
    bool uniqueSolution = true;

    for (int i = 0; i < sudokuSize; ++i) {
        for (int j = 0; j < sudokuSize; ++j) {
            if (allNumbers[i][j] != finishedBoard[i][j]){
                uniqueSolution = false;
            }
        }
    }

    if (uniqueSolution) {
        std::cout << std::endl << "This solution is unique...probably!" << std::endl;
    } else {
        std::cout << std::endl << "This solution is  NOT unique!" << std::endl;
    }

}







