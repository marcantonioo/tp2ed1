
#include "domino.h"

int main(){
    int n, i = 1;
    Dominol *jogo;
    scanf("%d", &n);
    while(n != 0){
        jogo = dominoCria(n);
        Peca *aux = malloc(sizeof(Peca));
   
        //printf("Testanto inserir final: ");
        for(int i = 0; i < n; i++){
            scanf("%d%d", &aux->x, &aux->y);
            aux->foiUsada = false;
            dominoAdicionaPecaFinal(jogo, aux);
        }

        printf("Test %d:\n", i);
        dominoImprime(jogo);
        dominoResolve(jogo);

        i++;
        free(aux);
        scanf("%d", &n);
        printf("\n\n");
        dominoDestroi(jogo);
       

    }
    return 0;

   
   
}
