#ifndef DOMINO_H
#define DOMINO_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct domino
{
    int x;
    int y;
    bool foiUsada;
    struct domino *prox;
    struct domino *ant;
}Peca;

typedef struct {
    int tamanho;
    Peca *pInicio, *pFim;
}Dominol;

Dominol* dominoCria();
bool dominoDestroi();
bool dominoAdicionaPecaInicio();
bool dominoAdicionaPecaFinal();
bool adicionaPecaMeio();
bool dominoEhPossivelOrganizar();
void dominoImprime();
bool dominoEhPossivelOrganizar();
void atualizaPonteiros();
void dominoLer();
void dominoFalsificaPecas();//atualiza o foiUsada de todas as peças

#endif