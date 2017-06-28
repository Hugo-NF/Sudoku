#include "Sudoku.h"

int main() {
    Posicao **jogo;
    char startingPattern[1000];
    printf("Digite uma string com os algarismos iniciais: ");
    //gets(startingPattern);
    //getchar();
    strcpy(startingPattern, "600402100901030608000000000304000062000940007500270300020801009058300006400020850");
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
