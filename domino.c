#include "domino.h"


Dominol* dominoCria(int tamanho){
    Dominol *tabuleiro = (Dominol*) malloc(sizeof(Dominol)); //aloca o tabuleiro
    if (tabuleiro == NULL)//se n deu pra alocar retorna false
        return NULL;
    tabuleiro->tamanho = tamanho;//atualiza o tamnho do tabuleiro
    tabuleiro->pInicio = (Peca*) malloc(sizeof(Peca));//aloca a cabeça
    if(tabuleiro->pInicio == NULL){
        free(tabuleiro);
        return NULL;
    }
    tabuleiro->pInicio->prox = NULL;//inicia os indices 
    tabuleiro->pInicio->ant = NULL;
    tabuleiro->pFim = tabuleiro->pInicio;
    return tabuleiro;
}

bool dominoDestroi(Dominol* tabuleiro){
    if (tabuleiro == NULL)
        return false; 
    Peca* aux = tabuleiro->pInicio;
    while(aux != NULL){//percorre o tabuleiro liberand cada posição 
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
    Peca *novaPeca = (Peca*) malloc(sizeof(Peca));//aloca uma novaPeca pra manipulação
    if(novaPeca == NULL){
        dominoDestroi(tabuleiro);
        return false;
    }
    novaPeca->x = peca->x;
    novaPeca->y = peca->y;
    novaPeca->prox = NULL;
    if (tabuleiro->pInicio == tabuleiro->pFim) {//se é a primeira peça a ser inserida
        novaPeca->ant = tabuleiro->pInicio;//novapeca anterior aponta pro antigo inicio
        tabuleiro->pInicio->prox = novaPeca;
    } else {
        novaPeca->ant = tabuleiro->pFim;//aponta pro antigo fim
        tabuleiro->pFim->prox = novaPeca;//o fim agora aponta pra novapeca
    }
    tabuleiro->pFim = novaPeca;

    return true;
} 


bool adicionaPecaMeio(Dominol *tabuleiro, Peca *pecaAnterior, Peca *pecaSeguinte, Peca *novaPeca) {
    if (tabuleiro == NULL || pecaAnterior == NULL || pecaSeguinte == NULL || novaPeca == NULL) {
        return false;
    }
    Peca *nova = (Peca*) malloc(sizeof(Peca));//peca pra manipulação
    if (nova == NULL) {
        return false;
    }
    // Copia os valores 
    nova->x = novaPeca->x;
    nova->y = novaPeca->y;
    nova->foiUsada = false;
    nova->ant = pecaAnterior;//nova aponta pra anterior
    nova->prox = pecaSeguinte;//nova aponta pra seguinte
    pecaAnterior->prox = nova;//a prox da anterior aponta pra nova
    pecaSeguinte->ant = nova;//a ant da seguinte aponta pra nova

    tabuleiro->tamanho++;//atualiza o tamanho

    return true; 
}


//so chmar se peca tiver organizada
bool dominoAdicionaPecaInicio(Dominol *tabuleiro, Peca *peca){
    Peca* novaPeca = (Peca*) malloc(sizeof(Peca));//nova pra manipulaçao
    if(novaPeca == NULL)
        return false;
    //substitui valores
    novaPeca->x = peca->x;
    novaPeca->y = peca->y;
    novaPeca->prox = tabuleiro->pInicio->prox;//a nova prox aponta pro antigo inicio
    novaPeca->ant = tabuleiro->pInicio; //Apont pra cabeça
    if(tabuleiro->pInicio->prox != NULL)
        tabuleiro->pInicio->prox->ant = novaPeca;
    else
        tabuleiro->pFim = novaPeca;
    tabuleiro->pInicio->prox = novaPeca;
  
    return true;
}


void dominoInvertePeca(Peca **peca){//inverte uma peça
    int aux;
    aux = (*peca)->x;
    (*peca)->x = (*peca)->y;
    (*peca)->y = aux;
}

void dominoLer(Dominol *pJogo, int n){//lê todas as peças do dimino adicionando no final ate completar a lista
    Peca *aux = malloc(sizeof(Peca));
    for(int i = 0; i < n; i++){
        scanf("%d%d", &aux->x, &aux->y);
        aux->foiUsada = false;
        dominoAdicionaPecaFinal(pJogo, aux);
    }
    free(aux);
}

void dominoFalsificaPecas(Dominol *tabuleiro){//atualiza o satus de foiUsada de todas as peças
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

void dominoImprime(Dominol* tabPronto){//imprime o jogo resolvido
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
 
void atualizaPonteiros(Peca **pJogoOriginal, Dominol **pAux, Dominol **pTabuleiro){//avança os ponteiros com base na inserção das peças
    (*pJogoOriginal)->foiUsada = true;
    (*pJogoOriginal) = (*pTabuleiro)->pInicio->prox;
    (*pAux)->tamanho ++;
}

/*
Complexidade assintótica O(n^2), devido a dominoDestroi que é a função com mainor grau de n,
mas devido ao do while presente na main que percorre todas as peças onde dominoEhPossívelOrganizar é chmado, 
a complexidade fica O(n) * O(n^2), resultando em O(n^3);
*/

bool dominoEhPossivelOrganizar(Dominol **tabuleiro, Peca *pPecaInicial){
    int tam = 1;
    Dominol *aux = dominoCria(tam);

    pPecaInicial->foiUsada = true;
    dominoAdicionaPecaInicio(aux, pPecaInicial);//o auxiliar começa com a 1º peça do 
    Peca *JogoOriginal = (*tabuleiro)->pInicio->prox;

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
    if(aux->tamanho == (*tabuleiro)->tamanho){//se resolveu 
        dominoDestroi(*tabuleiro);
        (*tabuleiro) = aux;
        return true;
    }else 
    if(aux->tamanho == ((*tabuleiro)->tamanho) - 1 && (*tabuleiro)->tamanho > 2){//aqui é se falta apenas uma peça pra inserir e essa peça contem o x e y iguais
        
        JogoOriginal= (*tabuleiro)->pInicio->prox;//aqui eu encontro essa peça
        while(JogoOriginal != NULL){
            if((JogoOriginal->foiUsada == false) && JogoOriginal->x == JogoOriginal->y){
                break;
            }
            JogoOriginal = JogoOriginal->prox;
        }

        //nesse momento JogoOriginal é a peça que não foi usada
        Peca *JogoDoAux = aux->pInicio->prox;
        while(JogoDoAux->prox != NULL){//aqui eu encontro uma posição na lista pra inserir
            if(JogoDoAux->y == JogoOriginal->x){
                break;
            }
            JogoDoAux = JogoDoAux->prox;
        }
        adicionaPecaMeio(aux, JogoDoAux, JogoDoAux->prox, JogoOriginal);//eu insiro JogoOriginal entre JogoDoAux e JogoDoAux->prox
        dominoDestroi(*tabuleiro);
        (*tabuleiro) = aux;//substituo o tabuleiro na main
        return true;

    }else{//se não encontrou solução retorna false 
        dominoDestroi(aux);
        return false;
    }
}


