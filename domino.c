#include "domino.h"

void falso(Dominol *tabuleiro){
    if(tabuleiro->pInicio == NULL || tabuleiro->pInicio->prox == NULL){
        // printf("Tabuleiro Vazio\n");
        return;
    }
    Peca* aux = tabuleiro->pInicio->prox;
    while(aux != NULL){
            aux->foiUsada = false;
            aux = aux->prox;
    }   
}

Dominol* dominoCria(int tamanho){
    Dominol *tabuleiro = (Dominol*) malloc(sizeof(Dominol)); 
    if (tabuleiro == NULL)
        return NULL;
    tabuleiro->tamanho = tamanho;
    tabuleiro->pInicio = (Peca*) malloc(sizeof(Peca));//aloca a cabeça
    if(tabuleiro->pInicio == NULL){
        free(tabuleiro);
        return NULL;
    }
    tabuleiro->pInicio->prox = NULL;
    tabuleiro->pInicio->ant = NULL;
    tabuleiro->pFim = tabuleiro->pInicio;
    return tabuleiro;
}

bool dominoDestroi(Dominol* tabuleiro){
    if (tabuleiro == NULL) return false; // Evita acessar memória inválida
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


bool adicionaPecaMeio(Dominol *tabuleiro, Peca *pecaAnterior, Peca *pecaSeguinte, Peca *novaPeca) {
    // Verifica se os parâmetros são válidos
    if (tabuleiro == NULL || pecaAnterior == NULL || pecaSeguinte == NULL || novaPeca == NULL) {
        return false; // Parâmetros inválidos
    }

    // Verifica se as peças são consecutivas
    if (pecaAnterior->prox != pecaSeguinte || pecaSeguinte->ant != pecaAnterior) {
        return false; // As peças não estão corretamente conectadas
    }

    // Aloca uma nova peça para evitar modificar `novaPeca` diretamente
    Peca *nova = (Peca*) malloc(sizeof(Peca));
    if (nova == NULL) {
        return false; // Falha na alocação de memória
    }

    // Copia os valores da peça fornecida
    nova->x = novaPeca->x;
    nova->y = novaPeca->y;
    nova->foiUsada = false;

    // Insere a nova peça na lista
    nova->ant = pecaAnterior;
    nova->prox = pecaSeguinte;
    pecaAnterior->prox = nova;
    pecaSeguinte->ant = nova;

    // Atualiza o tamanho do tabuleiro
    tabuleiro->tamanho++;

    return true; // Inserção bem-sucedida
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

void dominoLer(Dominol *pJogo, int n){
    Peca *aux = malloc(sizeof(Peca));
    for(int i = 0; i < n; i++){
        scanf("%d%d", &aux->x, &aux->y);
        aux->foiUsada = false;
        dominoAdicionaPecaFinal(pJogo, aux);
    }
    free(aux);
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


bool dominoResolve(Dominol **tabuleiro, Peca *pPecaInicial){
    int tam = 1;
    Dominol *aux = dominoCria(tam);
   // bool control = false;//controlar se houve inserção

    pPecaInicial->foiUsada = true;
    dominoAdicionaPecaInicio(aux, pPecaInicial);//o auxiliar começa com a 1º peça do 
    //Peca *JogoOriginal = pPecaInicial->prox;
    Peca *JogoOriginal = (*tabuleiro)->pInicio->prox;
    ///printf("[%d-%d]\n",JogoOriginal->ant->x,JogoOriginal->ant->y);

    //inicia o domino auxiliar colocando a primeira peça pra iniciar
   // while(aux->tamanho != tabuleiro->tamanho  control == false){

        while(JogoOriginal != NULL){//qunado sair desse while percorreu todas as peças inserindo ou não
            //control = false;
            if((aux->pInicio->prox->x == JogoOriginal->y) && JogoOriginal->foiUsada == false){//inserir no início
                dominoAdicionaPecaInicio(aux, JogoOriginal);
                atualizaPonteiros(&JogoOriginal, &aux, tabuleiro);
            } else 
            if((aux->pFim->y == JogoOriginal->x) && JogoOriginal->foiUsada == false){//inserir no final
                dominoAdicionaPecaFinal(aux, JogoOriginal);
                atualizaPonteiros(&JogoOriginal, &aux, tabuleiro);
            }else
            if((aux->pInicio->prox->x == JogoOriginal->x)  && JogoOriginal->foiUsada == false){//inserir no inicio invertida;
                dominoInvertePeca(&JogoOriginal);
                dominoAdicionaPecaInicio(aux, JogoOriginal);
                atualizaPonteiros(&JogoOriginal, &aux, tabuleiro);
            }else
            if ((aux->pFim->y == JogoOriginal->y) && JogoOriginal->foiUsada == false){//inserir no final invertida
                dominoInvertePeca(&JogoOriginal);
                dominoAdicionaPecaFinal(aux, JogoOriginal);
                atualizaPonteiros(&JogoOriginal, &aux, tabuleiro);
            }else{//aqui é se não deu pra inserir no inicio nem no final
                //vou passar para a proxima peça
                JogoOriginal = JogoOriginal->prox;
            }
        }
   // }
    if(aux->tamanho == (*tabuleiro)->tamanho){
        dominoDestroi(*tabuleiro);
        (*tabuleiro) = aux;
        return true;
    }else 
    if(aux->tamanho == ((*tabuleiro)->tamanho) - 1 && (*tabuleiro)->tamanho > 2){
        JogoOriginal= (*tabuleiro)->pInicio->prox;
        while(JogoOriginal != NULL){
            if((JogoOriginal->foiUsada == false) && JogoOriginal->x == JogoOriginal->y){
                //printf("\n\n%d [%d %d]\n\n",JogoOriginal->foiUsada, JogoOriginal->x, JogoOriginal->y);
                break;
            }
            JogoOriginal = JogoOriginal->prox;
        }
        //nesse momento JogoOriginal é a peça que não foi usada
        Peca *JogoDoAux = aux->pInicio->prox;
        while(JogoDoAux->prox != NULL){
            if(JogoDoAux->y == JogoOriginal->x){
               // printf("\n\nJogoDoAux: {%d%d} [%d%d] {%d%d}\n\n", JogoDoAux->x, JogoDoAux->y, JogoOriginal->x, JogoOriginal->y, JogoDoAux->prox->x, JogoDoAux->prox->y);
                break;
            }
            JogoDoAux = JogoDoAux->prox;
        }

        //dominoImprime(aux);
        adicionaPecaMeio(aux, JogoDoAux, JogoDoAux->prox, JogoOriginal);
        dominoDestroi(*tabuleiro);
        (*tabuleiro) = aux;
        return true;
    }else{//se não encontrou solução retorna false 
        dominoDestroi(aux);
        return false;
    }
}


