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
}peca;

typedef struct Lista
{
    int tamanho;
    peca* cab;
}dominol;


dominol DominoCria();
bool DominoDestroi();
bool DominoAdicionaPeca();
bool DominoImprime();
bool DominoEhPossivelOrganizar();

#endif