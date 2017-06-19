cmake_minimum_required(VERSION 3.7)
project(Sudoku)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Sudoku.cpp Sudoku.hpp Posicao.hpp)
add_executable(Sudoku ${SOURCE_FILES})