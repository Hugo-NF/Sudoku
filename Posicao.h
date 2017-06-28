
#ifndef SUDOKU_POSICAO_H
#define SUDOKU_POSICAO_H

#include <stdbool.h> //Library boolada
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define DIMENSAO 9
#define POSICOES 81

typedef struct posicao{
    int numero;
    bool inicial;
}Posicao;

#endif //SUDOKU_POSICAO_HPP
