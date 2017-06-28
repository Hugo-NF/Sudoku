cmake_minimum_required(VERSION 3.7)
project(Sudoku)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c Sudoku.c Sudoku.h Posicao.h)
add_executable(Sudoku ${SOURCE_FILES})