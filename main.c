#include "Sudoku.h"

int main() {
    string startingPattern;
    cout<<"Digite uma string com as posições iniciais: "<<endl;
    //cin >> startingPattern;
    startingPattern = "530070000600195000098000060800060003400803001700020006060000280000419005000080079";
    Sudoku *tabuleiro = new Sudoku();
    tabuleiro->iniciaTabuleiro(startingPattern);
    cout<<"\nBefore: "<<endl;
    tabuleiro->mostraTabuleiro();
    tabuleiro->solucionaSudoku();
    cout<<"\nAfter: "<<endl;
    tabuleiro->mostraTabuleiro();
    tabuleiro->~Sudoku();
    system("PAUSE");
    return 0;
}
