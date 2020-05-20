cmake_minimum_required(VERSION 3.16)
project(sudokuSolver)

set(CMAKE_CXX_STANDARD 20)

add_executable(sudokuSolver main.cpp Board.cpp Board.h)