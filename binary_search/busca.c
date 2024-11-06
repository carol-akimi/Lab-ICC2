#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef struct carta_{
    int valor;
    int posicao;
}Carta;

int busca_linear(Carta *baralho, int n, int k);
int busca_binaria(Carta *baralho, int ini, int fim, int k);
int comparar(const void *A, const void *B);
int binaria_recursiva(Carta *baralho, int ini, int fim, int k);

int main(void){
    int n, k; 
    scanf("%d %d", &n, &k); 

    Carta *baralho = (Carta*) malloc(sizeof(Carta) * n); 

    for (int i = 0; i < n; i++){
        scanf("%d", &baralho[i].valor); 
        baralho[i].posicao = i + 1; 
    }
    
    clock_t ini1, fim1; 
    ini1 = clock(); 
    qsort(baralho, n, sizeof(Carta), comparar);
    int pos=binaria_recursiva(baralho, 0, n-1, k);
    //int pos = busca_binaria(baralho, 0, n-1, k); 
    fim1 = clock(); 

    // clock_t ini2, fim2; 
    // ini2 = clock(); 
    // int pos = busca_linear(baralho, n, k);
    // fim2 = clock();
    
    printf("%d\n", pos); 
    printf("\nTempo da busca binaria na posição %d entre %d elementos: %lf s\n", pos, n, ((double) (fim1 - ini1)) / CLOCKS_PER_SEC); 
    //printf("\nTempo da busca linear na posição %d entre %d elementos: %lf s\n", pos, n, ((double) (fim2 - ini2)) / CLOCKS_PER_SEC); 
}

int busca_linear(Carta *baralho, int n, int k){
    for (int i = 0; i < n; i++){
        if (baralho[i].valor == k){
            return i+1; 
        }
    }
    return -1; //nao encontramos o item 
}

int busca_binaria(Carta *baralho, int ini, int fim, int k){ //iterativa 
    while (ini <= fim){
        int meio = (ini + fim)/2; 
        int valor = baralho[meio].valor; 
        if (valor == k){
            while (meio > 0 && baralho[meio-1].valor == k){
                meio--; 
            }
            return baralho[meio].posicao; 
        }
        if (k > valor)
            ini = meio + 1; 
        if (k < valor)
            fim = meio; 
    }
    return -1;
}

//usado na função qsort para ordenar o vetor (podemos mudar para outro algoritmo mais eficiente)
int comparar(const void *A, const void *B){
    Carta *a = (Carta*)A, *b = (Carta*)B;
    if ((*a).valor > (*b).valor)
        return 1; 
    else if ((*a).valor == (*b).valor)
        return 0; 
    else
        return -1; 
}

int binaria_recursiva(Carta *baralho, int ini, int fim, int k){
    int meio = (ini + fim)/2; 
        int valor = baralho[meio].valor; 
        if (valor == k){
            while (meio > 0 && baralho[meio-1].valor == k){
                meio--; 
            }
            return baralho[meio].posicao; 
        }
        if(ini==fim)
            return -1;

        if (k > valor)
            return binaria_recursiva(baralho, meio+1, fim, k); 
        if (k < valor)
            return binaria_recursiva(baralho, ini, meio, k);
}