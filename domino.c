#include "domino.h"

Dominol* dominoCria(int tamanho){
    Dominol *tabuleiro = (Dominol*) malloc(sizeof(Dominol)); 
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

bool dominoDestroi(Dominol* tabuleiro){
    Peca* aux = tabuleiro->pInicio;
    while(aux != NULL){
        Peca* aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(tabuleiro);
    return true;
}


//antes de chamar essa func, a peça tem que estar na posiçao certa, seja invertida ou não
bool dominoAdicionaPecaFinal(Dominol* tabuleiro, Peca* peca){
    if (tabuleiro == NULL ||peca == NULL)
        return false;
    Peca *novaPeca = (Peca*) malloc(sizeof(Peca));
    if(novaPeca == NULL){
        dominoDestroi(tabuleiro);
        return false;
    }
    novaPeca->x = peca->x;
    novaPeca->y = peca->y;
    novaPeca->prox = NULL;
    if (tabuleiro->pInicio == tabuleiro->pFim) {
        novaPeca->ant = tabuleiro->pInicio;
        tabuleiro->pInicio->prox = novaPeca;
    } else {
        novaPeca->ant = tabuleiro->pFim;
        tabuleiro->pFim->prox = novaPeca;
    }
    tabuleiro->pFim = novaPeca;

    return true;
} 

//so chmar se peca tiver organizada
bool dominoAdicionaPecaInicio(Dominol *tabuleiro, Peca *peca){
    Peca* novaPeca = (Peca*) malloc(sizeof(Peca));
    if(novaPeca == NULL)
        return false;

    novaPeca->x = peca->x;
    novaPeca->y = peca->y;
    novaPeca->prox = tabuleiro->pInicio->prox;
    novaPeca->ant = tabuleiro->pInicio; //Apont pra cabeça
    if(tabuleiro->pInicio->prox != NULL)
        tabuleiro->pInicio->prox->ant = novaPeca;
    else
        tabuleiro->pFim = novaPeca;
    tabuleiro->pInicio->prox = novaPeca;
  
    return true;
}


void dominoInvertePeca(Peca **peca){
    int aux;
    aux = (*peca)->x;
    (*peca)->x = (*peca)->y;
    (*peca)->y = aux;
}

void dominoImprime(Dominol* tabPronto){
    if(tabPronto->pInicio == NULL || tabPronto->pInicio->prox == NULL){
        // printf("Tabuleiro Vazio\n");
        return;
    }
    Peca* aux = tabPronto->pInicio->prox;
    while(aux != NULL){
        if(aux->prox == NULL){
            printf("%d%d", aux->x, aux->y);
            break;
        }
        printf("%d%d|", aux->x, aux->y);
        aux = aux->prox;
    }   
}
 
void atualizaPonteiros(Peca **pJogoOriginal, Dominol **pAux, Dominol **pTabuleiro){
    (*pJogoOriginal)->foiUsada = true;
    (*pJogoOriginal) = (*pTabuleiro)->pInicio->prox;
    (*pAux)->tamanho ++;
}


bool dominoResolve(Dominol *tabuleiro){
    int tam = 1;
    Dominol *aux = dominoCria(tam);
   // bool control = false;//controlar se houve inserção

    tabuleiro->pInicio->prox->foiUsada = true;
    dominoAdicionaPecaInicio(aux, tabuleiro->pInicio->prox);//o auxiliar começa com a 1º peça do 
    Peca *JogoOriginal = tabuleiro->pInicio->prox->prox;

    //inicia o domino auxiliar colocando a primeira peça pra iniciar
   // while(aux->tamanho != tabuleiro->tamanho  control == false){

        while(JogoOriginal != NULL){//qunado sair desse while percorreu todas as peças inserindo ou não
            //control = false;
            if((aux->pInicio->prox->x == JogoOriginal->y) && JogoOriginal->foiUsada == false){//inserir no início
                dominoAdicionaPecaInicio(aux, JogoOriginal);
                atualizaPonteiros(&JogoOriginal, &aux, &tabuleiro);
            } else  
            if((aux->pFim->y == JogoOriginal->x) && JogoOriginal->foiUsada == false){//inserir no final
                dominoAdicionaPecaFinal(aux, JogoOriginal);
                atualizaPonteiros(&JogoOriginal, &aux, &tabuleiro);
            }else
            if((aux->pInicio->prox->x == JogoOriginal->x)  && JogoOriginal->foiUsada == false){//inserir no inicio invertida;
                dominoInvertePeca(&JogoOriginal);
                dominoAdicionaPecaInicio(aux, JogoOriginal);
                atualizaPonteiros(&JogoOriginal, &aux, &tabuleiro);
            }else
            if ((aux->pFim->y == JogoOriginal->y) && JogoOriginal->foiUsada == false){//inserir no final invertida
                dominoInvertePeca(&JogoOriginal);
                dominoAdicionaPecaFinal(aux, JogoOriginal);
                atualizaPonteiros(&JogoOriginal, &aux, &tabuleiro);
            }else{//aqui é se não deu pra inserir no inicio nem no final
                //vou passar para a proxima peça
                JogoOriginal = JogoOriginal->prox;
            }
        }
   // }
    if(aux->tamanho == tabuleiro->tamanho){
        printf("YES\n");
        dominoImprime(aux);
        printf("\n\n");
        dominoDestroi(aux);
        return true;
    }else{
        printf("NO\n\n");
        dominoImprime(aux);
        dominoDestroi(aux);
        return false;
    }
    

}
