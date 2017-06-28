
#include "Sudoku.h"

Posicao** alocaSudoku(){
    int i;
    Posicao **tabuleiro = (Posicao **) calloc(DIMENSAO,sizeof(Posicao *));
    for(i=0; i<DIMENSAO; i++){
        *(tabuleiro + i) = (Posicao *) calloc(DIMENSAO,sizeof(Posicao));
    }
    return tabuleiro;
}

void desalocaSudoku(Posicao **tabuleiro){
    int i;
    for(i = 0; i<DIMENSAO; i++){
        free(*(tabuleiro + i));
    }
    free(tabuleiro);
}

int* alocaVetor(){
    return (int *) malloc(sizeof(int));
}

void desalocaVetor(int *vetor){
    if(vetor != NULL)
        free(vetor);
}

void mostraTabuleiro(Posicao **tabuleiro){
    int i, j, iParser = 0, jParser = 0;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            printf("%d ", tabuleiro[i][j].numero);
            jParser++;
            if(jParser%3 == 0 && j !=8){
                printf("| ");
            }
        }
        iParser++;
        printf("\n");
        if(iParser%3 == 0 && i != 8){
            printf("- - - - - - - - - - -\n");
        }
    }
}

void iniciaTabuleiro(Posicao **tabuleiro, char *entradas) {
    int i, j, k = 0;
    assert(strlen(entradas) >= POSICOES); //Assegura que teremos entradas suficientes para preenchertodo o tabuleiro
    for(i = 0; i<DIMENSAO; i++){
        for(j = 0; j<DIMENSAO; j++){
            if(entradas[k] != '0'){
                tabuleiro[i][j].numero = (entradas[k] - '0');
                tabuleiro[i][j].inicial = true;
            }
            else{
                tabuleiro[i][j].inicial = false;
            }
            k++;
        }
    }
}

void quickSort (int *a, int n){   ///Array e tamanho
    int i, j, p, t; ///Var. de controle
    if (n < 2) ///Parada da recursão
        return;
    p = a[n / 2]; ///Encontra o meio para o pivo
    for (i = 0, j = n - 1;; i++, j--)   ///Incrementa e decrementa
    {
        while (a[i] < p) ///Incrementa comparando com o pivo
            i++;
        while (p < a[j]) ///Incrementa comparando com o pivo
            j--;
        if (i >= j) ///Verifica o cruzamento dos extremos
            break;
        t = a[i]; ///Troca o [i] com o [j]
        a[i] = a[j];
        a[j] = t;
    }
    quickSort(a, i); ///Chama recursivamente os sub-vetores
    quickSort(a + i, n - i);
}

int binSearch (int x, int *v, int e, int d) {
    int meio = (e + d)/2;
    if (v[meio] == x)
        return meio;
    if (e >= d)
        return -1; // não encontrado
    else
    if (v[meio] < x)
        return binSearch(x, v, meio+1, d);
    else
        return binSearch(x, v, e, meio-1);
}

void solucionaSudoku(Posicao **tabuleiro) {
    int possibilidades[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *linha;
    int *coluna;
    int *quadrado;
    int *linhaDiff;
    int linhaDiffTamanho;
    int *colunaDiff;
    int colunaDiffTamanho;
    int *quadradoDiff;
    int quadradoDiffTamanho;
    int *interseccao1;
    int interseccao1Tamanho;
    int *interseccao2;
    int interseccao2Tamanho;
    int i, j;
    int numerosResolvidos;
    int ultimaVarredura = -1;
    double porcentagem;
    do {
        numerosResolvidos = 0;
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                if (!tabuleiro[i][j].inicial){
                    linha = leLinha(tabuleiro, i, j);
                    coluna = leColuna(tabuleiro, i, j);
                    quadrado = leQuadrado(tabuleiro, i, j);
                    quickSort(linha, DIMENSAO-1);
                    quickSort(coluna, DIMENSAO-1);
                    quickSort(quadrado, DIMENSAO-1);
                    linhaDiff = diferenca(possibilidades, linha, &linhaDiffTamanho, DIMENSAO, DIMENSAO-1);
                    colunaDiff = diferenca(possibilidades, coluna, &colunaDiffTamanho, DIMENSAO, DIMENSAO-1);
                    quadradoDiff = diferenca(possibilidades, quadrado, &quadradoDiffTamanho, DIMENSAO, DIMENSAO-1);
                    interseccao1 = interseccao(linhaDiff, colunaDiff, &interseccao1Tamanho, linhaDiffTamanho, colunaDiffTamanho);
                    interseccao2 = interseccao(quadradoDiff, interseccao1, &interseccao2Tamanho, quadradoDiffTamanho, interseccao1Tamanho);
                    if (interseccao2Tamanho == 1) {
                        tabuleiro[i][j].inicial = true;
                        tabuleiro[i][j].numero = interseccao2[0];
                    }
                    desalocaVetor(linha);
                    desalocaVetor(coluna);
                    desalocaVetor(quadrado);
                    desalocaVetor(linhaDiff);
                    desalocaVetor(colunaDiff);
                    desalocaVetor(quadradoDiff);
                }
                else
                    numerosResolvidos++;
            }
        }
        if(ultimaVarredura == numerosResolvidos){
            desalocaSudoku(tabuleiro);
            printf("Abortando...\nEsse algoritmo nao consegue solucionar esse tabuleiro Sudoku\n");
            exit(0);
        }
        porcentagem = numerosResolvidos/(POSICOES*0.01);
        ultimaVarredura = numerosResolvidos;
        printf("Calculando...\n%d/%d numeros preenchidos\n%.3f%% concluidos\n\n", numerosResolvidos, POSICOES, porcentagem);
    } while (numerosResolvidos != POSICOES);
}

int* leLinha(Posicao **tabuleiro, int i, int j){
    int *linha = (int *) calloc((DIMENSAO-1),sizeof(int));
    int m, n;
    for(m = 0, n = 0; m<DIMENSAO; m++){
        if(tabuleiro[i][m].numero != tabuleiro[i][j].numero){
            linha[n] = tabuleiro[i][m].numero;
            n++;
        }
    }
    return linha;
}

int* leColuna(Posicao **tabuleiro, int i, int j){
    int *coluna = (int *) calloc((DIMENSAO-1),sizeof(int));
    int m, n;
    for(m = 0, n = 0; m<DIMENSAO; m++){
        if(tabuleiro[m][j].numero != tabuleiro[i][j].numero) {
            coluna[n] = tabuleiro[m][j].numero;
            n++;
        }
    }
    return coluna;
}

int* leQuadrado(Posicao **tabuleiro, int i, int j){
    int m, n, k = 0;
    int inicioI, inicioJ;
    int limiteI, limiteJ;
    int *quadrado = (int *) calloc(DIMENSAO,sizeof(int));
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
            if(tabuleiro[m][n].numero != tabuleiro[i][j].numero) {
                quadrado[k] = tabuleiro[m][n].numero;
                k++;
            }
        }
    }
    return quadrado;
}

int* diferenca(int *possibilidades, int *vetor, int *tamanho, int tamPossibilidades, int tamVetor){
    int i;
    int resultado;
    int *diferenca = NULL;

    *tamanho = 0;
    for(i=0; i<tamPossibilidades; i++){
        resultado = binSearch(possibilidades[i], vetor, 0, tamVetor-1);
        if(resultado == -1){
            if(diferenca == NULL){
                diferenca = alocaVetor();
                diferenca[0] = possibilidades[i];
                *tamanho = 1;
            }
            else{
                diferenca = (int *) realloc(diferenca, (*tamanho + 1)*sizeof(int));
                *tamanho += 1 ;
                diferenca[*tamanho-1] = possibilidades[i];
            }
        }
    }
    return diferenca;
}

int* interseccao(int *possibilidades, int *vetor, int *tamanho, int tamPossibilidades, int tamVetor){
    int i;
    int resultado;
    int *interseccao = NULL;

    *tamanho = 0;
    for(i=0; i<tamPossibilidades; i++){
        resultado = binSearch(possibilidades[i], vetor, 0, tamVetor-1);
        if(resultado != -1){
            if(interseccao == NULL){
                interseccao = alocaVetor();
                interseccao[0] = vetor[resultado];
                *tamanho = 1;
            }
            else{
                interseccao = (int *) realloc(interseccao, (*tamanho + 1)*sizeof(int));
                *tamanho += 1;
                interseccao[*tamanho-1] = vetor[resultado];
            }
        }
    }
    return interseccao;
}

void printaVetor(int *vetor, int tamanho){
    int i;
    for(i = 0; i<tamanho; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}