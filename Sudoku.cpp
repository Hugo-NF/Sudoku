
#include "Sudoku.hpp"

void Sudoku::mostraTabuleiro(){
    int i, j, iParser = 0, jParser = 0;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            cout<<this->tabuleiro[i][j].numero<<" ";
            jParser++;
            if(jParser%3 == 0 && j !=8){
                cout<<"| ";
            }
        }
        iParser++;
        cout<<"\n";
        if(iParser%3 == 0 && i != 8){
            cout<<"- - - - - - - - - - -\n";
        }
    }
}

Sudoku::Sudoku(){
    int i;
    this->tabuleiro = (Posicao **) calloc(9, sizeof(Posicao *));
    for (i = 0; i<9; i++){
        *(this->tabuleiro + i) = (Posicao *) calloc(9, sizeof(Posicao));
    }
}

Sudoku::~Sudoku() {
    int i;
    for (i = 0; i<9; i++){
        free(*(this->tabuleiro + i));
    }
    free(this->tabuleiro);
}

void Sudoku::iniciaTabuleiro(string entradas) {
    int i, j, k = 0;
    assert(entradas.size() >= (9*9)); //Assegura que teremos entradas suficientes para preenchertodo o tabuleiro
    for(i = 0; i<9; i++){
        for(j = 0; j<9; j++){
            if(entradas[k] != '0'){
                this->tabuleiro[i][j].numero = (entradas[k] - '0');
                this->tabuleiro[i][j].inicial = true;
            }
            else{
                this->tabuleiro[i][j].inicial = false;
            }
            k++;
        }
    }
}

void Sudoku::solucionaSudoku() {
    bool finishFlag = false;
    bool positionChanged = true;
    vector<int> possibilidades = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> linha;
    vector<int> coluna;
    vector<int> quadrado;
    vector<int> linhaDiff(9);
    vector<int> colunaDiff(9);
    vector<int> quadradoDiff(9);
    vector<int>::iterator linhaIt;
    vector<int>::iterator colunaIt;
    vector<int>::iterator quadradoIt;
    vector<int> interseccao1(9);
    vector<int>::iterator interseccao1It;
    vector<int> interseccao2(9);
    vector<int>::iterator interseccao2It;
    int i, j;
    do {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                if (!this->tabuleiro[i][j].inicial){
                    positionChanged = false;
                    linha = this->leLinha(i, j);
                    coluna = this->leColuna(i, j);
                    quadrado = this->leQuadrado(i, j);
                    sort(linha.begin(), linha.end());
                    sort(coluna.begin(), coluna.end());
                    sort(quadrado.begin(), quadrado.end());
                    set_difference(possibilidades.begin(), possibilidades.end(), linha.begin(), linha.end(), linhaDiff.begin());
                    set_difference(possibilidades.begin(), possibilidades.end(), coluna.begin(), coluna.end(), colunaDiff.begin());
                    set_difference(possibilidades.begin(), possibilidades.end(), quadrado.begin(), quadrado.end(), quadradoDiff.begin());
                    linhaDiff.resize(linhaIt - linhaDiff.begin());
                    colunaDiff.resize(colunaIt - colunaDiff.begin());
                    quadradoDiff.resize(quadradoIt - quadradoDiff.begin());
                    set_intersection(linhaDiff.begin(), linhaDiff.end(), colunaDiff.begin(), colunaDiff.end(), interseccao1.begin());
                    interseccao1.resize(interseccao1It - interseccao1.begin());
                    set_intersection(interseccao1.begin(), interseccao1.end(), quadradoDiff.begin(), quadradoDiff.end(), interseccao2.begin());
                    interseccao2.resize(interseccao2It - interseccao2.begin());
                    if (interseccao2.empty())
                        this->tabuleiro[i][j].inicial = true;
                    else {
                        this->tabuleiro[i][j].numero = interseccao2[0];
                        positionChanged = true;
                    }
                    linhaDiff.resize(9);
                    colunaDiff.resize(9);
                    quadradoDiff.resize(9);
                    interseccao1.resize(9);
                    interseccao2.resize(9);
                    linha.clear();
                    coluna.clear();
                    quadrado.clear();
                    linhaDiff.clear();
                    colunaDiff.clear();
                    quadradoDiff.clear();
                    interseccao1.clear();
                    interseccao2.clear();
                    linhaIt.base();
                    colunaIt.base();
                    quadradoIt.base();
                    interseccao1It.base();
                    interseccao2It.base();
                }
                else
                    finishFlag = true;
            }
        }
    } while (!finishFlag && !positionChanged);
}

vector<int> Sudoku::leLinha(int i, int j){
    vector <int> linha;
    int m;
    for(m = 0; m<9; m++){
        if(this->tabuleiro[i][m].numero != this->tabuleiro[i][j].numero)
            linha.push_back(this->tabuleiro[i][m].numero);
    }
    return linha;
}

vector<int> Sudoku::leColuna(int i, int j){
    vector <int> coluna;
    int m;
    for(m = 0; m<9; m++){
        if(this->tabuleiro[m][j].numero != this->tabuleiro[i][j].numero)
            coluna.push_back(this->tabuleiro[m][j].numero);
    }
    return coluna;
}

vector<int> Sudoku::leQuadrado(int i, int j){
    int m, n;
    int inicioI, inicioJ;
    int limiteI, limiteJ;
    vector<int> quadrado;
    if(i <= 2) {
        limiteI = 2;
        inicioI = 0;
    }
    else if (i > 2 && i<=5) {
        limiteI = 5;
        inicioI = 3;
    }
    else if (i > 5 && i<=8) {
        limiteI = 8;
        inicioI = 6;
    }
    if(j <= 2) {
        limiteJ = 2;
        inicioJ = 0;
    }
    else if (j > 2 && j<=5) {
        limiteJ = 5;
        inicioJ = 3;
    }
    else if (j > 5 && j<=8) {
        limiteJ = 8;
        inicioJ = 6;
    }
    for(m=inicioI; m<=limiteI; m++){
        for(n=inicioJ; n<=limiteJ; n++){
            if(this->tabuleiro[m][n].numero != this->tabuleiro[i][j].numero)
                quadrado.push_back(this->tabuleiro[m][n].numero);
        }
    }
    return quadrado;
}
