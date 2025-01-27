#ifndef DOMINO_H
#define DOMINO_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct domino
{
    int x;
    int y;
    struct domino *prox;
    struct domino *ant;
}Peca;

typedef struct {
    int tamanho;
    peca *pInicio, *pFinal;
}Dominol;


Dominol DominoCria();
bool DominoDestroi();
bool DominoAdicionaPecaFinal();
bool DominoImprime();
bool DominoEhPossivelOrganizar();

#endif