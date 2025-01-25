#include "domino.h"

dominol* DominoCria(int tamanho){
    dominol *domino = (dominol*) malloc(sizeof(dominol)); 
    if (domino == NULL)
        return NULL;
    domino->tamanho = tamanho;
    domino->cab = (peca*) malloc(sizeof(peca));
    domino->cab->prox = NULL;
    return domino;
}

bool DominoDestroi(dominol* domino){
    peca* aux = domino->cab;
    while(aux != NULL){
        peca* auxx = aux->prox;
        free(aux);
        aux = auxx;
    }
    free(domino);
    return true;
}

bool DominoAdicionaPeca(dominol* domino, peca* peca){
    peca* aux = domino->cab;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = peca;
    peca->ant = aux;
    peca->prox = NULL;
    return true;
}

void DominoImprime(dominol* dominoPronto){
    peca* aux = domino->cab->prox;
    while(aux != NULL){
        printf("%d%d|", aux->x, aux->y);
    }
}