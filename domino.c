#include "domino.h"

/*
typedef struct domino
{
    int x;
    int y;
    struct domino *prox;
    struct domino *ant;
}Peca;

typedef struct Lista
{
    int tamanho;
    Peca *pInicio, *pFim;
}Dominol;
*/
Dominol* DominoCria(int tamanho){
    Dominol *tabuleiro = (Dominol*) malloc(sizeof(Domino)); 
    if (tabuleiro == NULL)
        return NULL;
    tabuleiro->tamanho = tamanho;
    tabuleiro->pInicio = (Peca*) malloc(sizeof(Peca));//aloca a cabeça
    if(tabuleiro->pInicio == NULL)
        return NULL;
    tabuleiro->pInicio->prox = NULL;
    tabuleiro->pInicio->ant = NULL;
    tabuleiro->pFim = tabuleiro->pInicio;
    return tabuleiro;
}
/*
domino* DominoCria(int tamanho){
    domino *tabuleiro = (domino*) malloc(sizeof(domino)); 
    if (domino == NULL)
        return NULL;
    tabuleiro->tamanho = tamanho;
    tabuleiro->cab = (peca*) malloc(sizeof(peca));
    tabuleiro->cab->prox = NULL;
    return tabuleiro;
}
*/
bool DominoDestroi(Domino* tabuleiro){
    peca* aux = tabuleiro->pInicio;
    while(aux != NULL){
        peca* aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(tabuleiro);
    return true;
}

/*
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
*/

//antes de chamar essa func, a peça tem que estar na posiçao certa, seja invertida ou não
bool DominoAdicionaPecaFinal(Domino* tabuleiro, Peca* peca){
    Peca* aux = tabuleiro->pFim;//ultima celula atual
    tabuleiro->pFim->prox = (Peca*) malloc(sizeof(Peca));//aloca mais uma
    tabuleiro->pFim = tabuleiro->pFim->prox;//o fim acabou de ser criado
    tabuleiro->pFim->x = peca->x;//talvez se colocar uma struct só com x e y
    tabuleiro->pFim->y = peca->y;
    tabuleiro->pFim->prox = NULL;//a préxima rebebe NULL
    tabuleiro->pFim->ant = aux;
    return true;
}

//so chmar se peca tiver organizada
bool DominoAdicionaPecaInicio(Domino *tabuleiro, Peca *peca){
    Peca* novaPeca = (Peca*) malloc(sizeof(Peca));
    Peca *aux = tabuleiro->pInicio->prox;//celula dpss da beça ante de eu mudar o baguio
    tabuleiro->pInicio->ant = novaPeca;//o antigo 1º no aponta pra o que acabou de ser criaido
    if(novaPeca == NULL)
        return false;
    novaPeca->x = peca->x;
    novaPeca->y = peca->y;
    tabuleiro->pInicio->prox = novaPeca;
    novaPeca->ant = tabuleiro->pInicio; //Apont pra cabeça
    novaPeca->prox = aux;//aponta pra antiga primeira celula
    return true;
}

void DominoInvertePeca(Peca *peca){
    int aux;
    aux = peca->x;
    peca->x = peca->y;
    peca->x = aux;
}

void DominoImprime(Domino* tabPronto){
    Peca* aux = tabPronto->pInicio->prox;
    while(aux != NULL){
        printf("%d%d|", aux->x, aux->y);
    }
}


bool DominoEhPossivelOrganizar(Domino* tabuleiro, Peca* aux){
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