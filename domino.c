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
       

    novaPeca->x = peca->x;//talvez se colocar uma struct só com x e y
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


//função que o deepseek fez
/* bool dominoAdicionaPecaFinal(Dominol *tabuleiro, Peca *peca) {
    if (tabuleiro == NULL || peca == NULL) {
        return false; // Verifica se o tabuleiro ou a peça são válidos
    }

    Peca *novaPeca = (Peca*) malloc(sizeof(Peca));
    if (novaPeca == NULL) {
        return false; // Verifica se a alocação foi bem-sucedida
    }

    // Copia os valores da peça para a nova peça
    novaPeca->x = peca->x;
    novaPeca->y = peca->y;
    novaPeca->foiUsada = peca->foiUsada;

    // Atualiza os ponteiros da nova peça
    novaPeca->prox = NULL; // Nova peça é a última, então prox é NULL
    novaPeca->ant = tabuleiro->pFim; // Nova peça aponta para a antiga última peça

    // Atualiza o ponteiro da antiga última peça para apontar para a nova peça
    tabuleiro->pFim->prox = novaPeca;

    // Atualiza o pFim para apontar para a nova peça
    tabuleiro->pFim = novaPeca;

    return true;
} */
 

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

//Função que o deepseek fez
/* bool dominoAdicionaPecaInicio(Dominol *tabuleiro, Peca *peca) {
    if (tabuleiro == NULL || peca == NULL) {
        return false; // Verifica se o tabuleiro ou a peça são válidos
    }

    Peca *novaPeca = (Peca*) malloc(sizeof(Peca));
    if (novaPeca == NULL) {
        return false; // Verifica se a alocação foi bem-sucedida
    }

    // Copia os valores da peça para a nova peça
    novaPeca->x = peca->x;
    novaPeca->y = peca->y;
    novaPeca->foiUsada = peca->foiUsada;

    // Atualiza os ponteiros da nova peça
    novaPeca->prox = tabuleiro->pInicio->prox; // Nova peça aponta para a antiga primeira peça
    novaPeca->ant = tabuleiro->pInicio;        // Nova peça aponta para a cabeça

    // Atualiza o ponteiro da cabeça para apontar para a nova peça
    if (tabuleiro->pInicio->prox != NULL) {
        tabuleiro->pInicio->prox->ant = novaPeca; // Antiga primeira peça aponta para a nova peça
    }
    tabuleiro->pInicio->prox = novaPeca;

    // Se o tabuleiro estava vazio, atualiza o pFim para apontar para a nova peça
    if (tabuleiro->pFim == tabuleiro->pInicio) {
        tabuleiro->pFim = novaPeca;
    }

    return true;
} */

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
 


bool dominoResolve(Dominol *tabuleiro){
    int tam = 1;
    Dominol *aux = dominoCria(tam);
   // bool control = false;//controlar se houve inserção

    tabuleiro->pInicio->prox->foiUsada = true;
    dominoAdicionaPecaInicio(aux, tabuleiro->pInicio->prox);//o auxiliar começa com a 1º peça do 
    Peca *JogoOriginal = tabuleiro->pInicio->prox->prox;
    // dominoImprime(aux);

    //inicia o domino auxiliar colocando a primeira peça pra iniciar
   // while(aux->tamanho != tabuleiro->tamanho  control == false){
     //   JogoOriginal = tabuleiro->pInicio;

        while(JogoOriginal != NULL){//qunado sair desse while percorreu todas as peças inserindo ou não

            //control = false;
            // printf("\nEntrou\n");
            if((aux->pInicio->prox->x == JogoOriginal->y) && JogoOriginal->foiUsada == false){//inserir no início;
                // printf("Entrou no if maldito nº 1\n");
                // printf("VAlor do JogoOriginal: %d %d\n",JogoOriginal->x, JogoOriginal->y);
                //  dominoImprime(aux);
                //  printf("\n");
                dominoAdicionaPecaInicio(aux, JogoOriginal);
                //  dominoImprime(aux);
                JogoOriginal->foiUsada = true;
                JogoOriginal = JogoOriginal->prox;
                //JogoAuxiliar = JogoAuxiliar->prox;
                aux->tamanho++;
                JogoOriginal = tabuleiro->pInicio->prox;
                //control = true;
            } else  

            //   /*   printf("\naux->pFim: %d, %d", aux->pFim->x, aux->pFim->y);
                //printf("\n\naux->pFim->ant: %d, %d", aux->pFim->ant->x, aux->pFim->ant->y);
                //printf("\naux->pFim->prox: %d, %d", aux->pFim->prox->x, aux->pFim->prox->y);
                // printf("\n JogoOriginal: %d, %d\n\n", JogoOriginal->x, JogoOriginal->y); */


            if((aux->pFim->y == JogoOriginal->x) && JogoOriginal->foiUsada == false){//inserir no final
                // printf("Entrou no if maldito nº 2\n");
                // dominoImprime(aux);
                dominoAdicionaPecaFinal(aux, JogoOriginal);
                // printf("\nDepois de adicionar: ");
                // dominoImprime(aux);
                // printf("\n\n");
                JogoOriginal->foiUsada = true;
                JogoOriginal = JogoOriginal->prox;
                //JogoAuxiliar = JogoAuxiliar->prox;
                aux->tamanho++;
                JogoOriginal = tabuleiro->pInicio->prox;
                //control = true;
            }else
            
            if(/* (aux->pFim != NULL)  &&*/ (aux->pFim->y == JogoOriginal->y) && JogoOriginal->foiUsada == false){//inserir no inicio;
                //  printf("Entrou no if maldito nº 3\n");
                //printf("aux->pFim->ant: %d %d\n",aux->pFim->ant->x, aux->pFim->ant->y);
                dominoInvertePeca(&JogoOriginal);
                // dominoImprime(aux);
                // printf("\n");
                dominoAdicionaPecaFinal(aux, JogoOriginal);
                // dominoImprime(aux);
                JogoOriginal->foiUsada = true;
                JogoOriginal = JogoOriginal->prox;
                aux->tamanho++;
                JogoOriginal = tabuleiro->pInicio->prox;
                //control = true;
            }else

            if ((aux->pInicio->prox->x == JogoOriginal->x) && JogoOriginal->foiUsada == false){//inserir no final; */
                //printf("VAlor do JogoOriginal: %d %d\n",JogoOriginal->x, JogoOriginal->y);
                // printf("Entrou no if maldito nº 4\n");
                // dominoImprime(aux);
                dominoInvertePeca(&JogoOriginal);
                dominoAdicionaPecaInicio(aux, JogoOriginal);
                JogoOriginal->foiUsada = true;
                JogoOriginal = JogoOriginal->prox;
                //JogoAuxiliar = JogoAuxiliar->prox;
                aux->tamanho++;
                JogoOriginal = tabuleiro->pInicio->prox;
                //control = true;
            }else
            {//aqui é se não deu pra inserir no inicio nem no final
                //vou passar para a proxima peça
                JogoOriginal = JogoOriginal->prox;
            }

        
        }
 //   }
    // printf("Tamnho do aux: %d\n", aux->tamanho);
    // printf("Tamnho do original: %d\n", tabuleiro->tamanho);
    //printf("O valor booleano é: %s\n", control ? "true" : "false");
    if(aux->tamanho == tabuleiro->tamanho){
        //printf("Deu Certo: ");
        //dominoImprime(tabuleiro);
        //printf("\n");
        printf("YES\n");
        dominoImprime(aux);
        printf("\n\n");
        dominoDestroi(aux);
        return true;
    }else{
        //printf("Não deu certo: ");
        //dominoImprime(tabuleiro);
        //printf("\n");
        //dominoImprime(aux);
        printf("NO\n\n");
        dominoDestroi(aux);
        return false;
    }
    

}

// bool DominoEhPossivelOrganizar(Domino* tabuleiro, Peca* aux){
//     if (pecateste == NULL)
//         aux = tabuleiro->cab->prox;
//         while(aux != NULL){
//             if (aux->y == aux->prox->x){
//                 aux = aux->prox;
//                 continue;
//                 }
//             else
//                 return false;
//         }

//     if (aux2 == NULL)
//         return false;

// }

// int Compara2Peca(peca* aux){
//     if (aux->y == aux->prox->y){
//         return 1;
//     }
//     else if (aux->y == aux->prox->x){
//         return 2;
//     }
//     return 0;
// }