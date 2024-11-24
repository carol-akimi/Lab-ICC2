#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nomeLocal[20];
    int destino;
} local;

int main(void){
    int n, k;

    scanf("%d %d", &n, &k);

    local* Locais = (local*) malloc(n * sizeof(local));

    for(int i = 0; i < n; i++){
        scanf("%s %d", Locais[i].nomeLocal, &Locais[i].destino);
    }

    for(int i = 0; i< k; i++){
        char locInicial[20];
        int passos;
        scanf("%s %d", locInicial, &passos);

    // Acho que essa busca que faz demorar
    // Ou faz de outro jeito ou muda a abordagem no geral
        int j;
        for(j = 0; strcmp(locInicial, Locais[j].nomeLocal) != 0; j++);
        local locAtual = Locais[j];
        for(j = passos; j > 0; j--){
            locAtual = Locais[locAtual.destino - 1];
        }

        printf("%s\n", locAtual.nomeLocal);
    }

    free(Locais);

    return 0;
}