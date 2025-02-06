
#include "domino.h"

int main(){
    int n;
    Dominol *jogo;
    scanf("%d", &n);
    jogo = dominoCria(n);
   
     printf("Testanto inserir final: ");
    for(int i = 0; i < n; i++){
        Peca *aux = malloc(sizeof(Peca));
        scanf("%d%d", &aux->x, &aux->y);
        aux->foiUsada = false;
        dominoAdicionaPecaFinal(jogo, aux);
    }

     /* printf("Testanto inserir inicio: ");
    for(int i = 0; i < n; i++){
        Peca *aux = malloc(sizeof(Peca));
        scanf("%d%d", &aux->x, &aux->y);
        aux->foiUsada = false;
        dominoAdicionaPecaInicio(jogo, aux);
    } */

    dominoImprime(jogo);
    printf("\nOK\n");
    dominoResolve(jogo);
    dominoDestroi(jogo);
}
