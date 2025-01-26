#include "domino.h"

domino* DominoCria(int tamanho){
    domino *tabuleiro = (domino*) malloc(sizeof(domino)); 
    if (domino == NULL)
        return NULL;
    tabuleiro->tamanho = tamanho;
    tabuleiro->cab = (peca*) malloc(sizeof(peca));
    tabuleiro->cab->prox = NULL;
    return tabuleiro;
}

bool DominoDestroi(domino* tabuleiro){
    peca* aux = tabuleiro->cab;
    while(aux != NULL){
        peca* auxx = aux->prox;
        free(aux);
        aux = auxx;
    }
    free(tabuleiro);
    return true;
}

bool DominoAdicionaPeca(domino* tabuleiro, peca* peca){
    peca* aux = tabuleiro->cab;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = peca;
    peca->ant = aux;
    peca->prox = NULL;
    return true;
}

void DominoImprime(domino* tabPronto){
    peca* aux = tabPronto->cab->prox;
    while(aux != NULL){
        printf("%d%d|", aux->x, aux->y);
    }
}

bool DominoEhPossivelOrganizar(domino* tabuleiro, peca* aux){
    if (pecateste == NULL)
        aux = tabuleiro->cab->prox;
        while(aux != NULL){
            if (aux->y == aux->prox->x){
                aux = aux->prox;
                continue;
                }
            else
                return false;
        }

    if (aux2 == NULL)
        return false;

}

int Compara2Peca(peca* aux){
    if (aux->y == aux->prox->y){
        return 1;
    }
    else if (aux->y == aux->prox->x){
        return 2;
    }
    return 0;
}