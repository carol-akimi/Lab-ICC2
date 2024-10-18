#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef struct carta_{
    int valor;
    short int posicao;
}Carta;

int busca_linear(Carta *baralho, int n, int k);
int busca_binaria(Carta *baralho, int n, int k);
int comparar(Carta *a, Carta *b);

int main(void){
    int n, k; 
    scanf("%d %d", &n, &k); 

    Carta *baralho = (int*) malloc(sizeof(Carta) * n); 

    for (int i = 0; i < n; i++){
        scanf("%d", baralho[i].valor); 
        baralh[i].posicao = i + 1; 
    }
    clock_t = ini1, fim1; 
    ini1 = clock(); 
    qsort(baralho, n, sizeof(int), comparar); 
    int pos = busca_binaria(baralho, 0, n-1, k); 
    fim1 = clock(); 

    clock_t = ini2, fim2; 
    ini2 = clock(); 
    //busca_linear(baralho, n, k);
    fim2 = clock();  
    
    printf("%d\n", pos); 
    printf("Tempo de execução da busca binaria %lf\n", ((double) (fim1 - ini1)) / CLOCK_PER_SECOND); 
    printf("Tempo de execução da busca linear %lf\n", ((double) (fim2 - ini2)) / CLOCK_PER_SECOND); 
}

int busca_linear(Carta *baralho, int n, int k){
    for (int i = 0; i < n; i++){
        if (baralho[i].valor == k){
            return baralho[i].posicao; 
        }
    }
    return -1; //nao encontramos o item 
}

int busca_binaria(Carta *baralho, int ini, int fim, int k){ //iterativa 
    while (ini <= fim){
        int meio = (ini + fim)/2; 
        int valor = baralho[meio].valor; 
        if (valor == k){
            while (baralho[meio-1].valor == k){
                meio--; 
            }
            return baralho[meio].posicao; 
        }
        if (valor > k)
            ini = meio + 1; 
        if (valor < k)
            fim = meio; 
        
    }
}

//usado na funçaõ qsort para ordenar o vetor (podemos mudar para outro algoritmo mais eficiente)
int comparar(Carta *a, Carta *b){
    if (*a > *b)
        return 1; 
    else if (*a == *b)
        return 0; 
    else
        return -1; 
}