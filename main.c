#include "Sudoku.h"

int main() {
    Posicao **jogo;
    char startingPattern[1000];
    printf("Digite uma string com os algarismos iniciais: ");
    //gets(startingPattern);
    //getchar();
    strcpy(startingPattern, "530070000600195000098000060800060003400803001700020006060000280000419005000080079");
    jogo = alocaSudoku();
    iniciaTabuleiro(jogo, startingPattern);
    printf("\n\nBefore:\n");
    mostraTabuleiro(jogo);
    solucionaSudoku(jogo);
    printf("\nAfter:\n");
    mostraTabuleiro(jogo);
    desalocaSudoku(jogo);

    return 0;
}
