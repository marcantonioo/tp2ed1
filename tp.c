
#include "domino.h"

int main(){
    int n, i = 1;
    bool jaResolveu;
    Dominol *jogo;
    Peca *pPecaInicial;
    scanf("%d", &n);
    while(n != 0){
        jogo = dominoCria(n); 
        dominoLer(jogo, n);

        //Peca *pAux;
        pPecaInicial = jogo->pInicio->prox;
        do{
            //dominoImprime(jogo);
            falso(jogo);
            //printf("\n");
            jaResolveu =  dominoResolve(&jogo, pPecaInicial);
            if(jaResolveu)
                break;
            pPecaInicial = pPecaInicial->prox;
           
        }while(pPecaInicial != NULL);

        if(jaResolveu){//se entru aqui é pq deu certo e resolveu
            printf("Test %d:\nYES\n", i);
            dominoImprime(jogo);
            printf("\n\n");
        }else{
            printf("Test %d:\nNO\n", i);
            printf("\n");
        }
        i++;
       // free(aux);
        scanf("%d", &n);
        //printf("\n");
        dominoDestroi(jogo);
       

    }
    return 0;

   
   
}
