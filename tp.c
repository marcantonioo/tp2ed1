
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
        pPecaInicial = jogo->pInicio->prox;
        do{ 
            dominoFalsificaPecas(jogo);
            jaResolveu =  dominoEhPossivelOrganizar(&jogo, pPecaInicial);//tenta organizar começando da primeira peça
            if(jaResolveu)
                break;
            pPecaInicial = pPecaInicial->prox;//se não deu com a primeira avança até o final da lista de paças testando começar com todas        
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
        scanf("%d", &n);
        dominoDestroi(jogo);
       
    }
    return 0;    
}
