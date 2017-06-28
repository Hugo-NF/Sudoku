
#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include "Posicao.h"

Posicao** alocaSudoku();
void desalocaSudoku(Posicao **);
int* alocaVetor();
void desalocaVetor(int *);
void iniciaTabuleiro(Posicao **, char *);
void mostraTabuleiro(Posicao **);


void solucionaSudoku(Posicao **);
void quickSort(int *, int);
int binSearch (int, int *, int, int);
int* leLinha(Posicao **, int, int);
int* leColuna(Posicao **, int, int);
int* leQuadrado(Posicao **, int, int);
int* diferenca(int *, int *, int *, int, int);
int* interseccao(int *, int *, int *, int, int);

void printaVetor(int *, int);


#endif //SUDOKU_SUDOKU_H
