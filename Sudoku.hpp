
#ifndef SUDOKU_SUDOKU_HPP
#define SUDOKU_SUDOKU_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cassert>
#include "Posicao.hpp"

using namespace std;

class Sudoku{
private:
    Posicao **tabuleiro;
public:
    Sudoku();
    ~Sudoku();
    void iniciaTabuleiro(string);
    void mostraTabuleiro();
    void solucionaSudoku();
    vector<int> leLinha(int, int);
    vector<int> leColuna(int, int);
    vector<int> leQuadrado(int, int);
};




#endif //SUDOKU_SUDOKU_HPP
