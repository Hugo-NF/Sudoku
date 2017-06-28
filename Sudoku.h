
#ifndef SUDOKU_SUDOKU_HPP
#define SUDOKU_SUDOKU_HPP


#include "Posicao.h"

typedef struct Sudoku{
    Posicao **tabuleiro;

    /**
     * Alocar e desalocar faltando
     * */

    void iniciaTabuleiro(char *string);
    void mostraTabuleiro();
    void solucionaSudoku();

};




#endif //SUDOKU_SUDOKU_HPP
