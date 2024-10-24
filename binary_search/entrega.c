#include <stdio.h> 
#include <stdlib.h>

/* Struct Carta armazena o valor e 
    a posição original da carta */
typedef struct carta_{
    int valor, posicao;
}Carta;

int busca_linear(Carta *baralho, int n, int k);
int comparar(const void *A, const void *B);
int busca_binaria(Carta *baralho, int ini, int fim, int k);
int binaria_recursiva(Carta *baralho, int ini, int fim, int k);

int main(void){
    /* Declara e lê o tamanho n do baralho e o valor k procurado */
    int n, k; 
    scanf("%d %d", &n, &k); 

    /* Aloca o baralho */
    Carta *baralho = (Carta*) malloc(sizeof(Carta) * n); 

    /* Inicializa as cartas */
    for (int i = 0; i < n; i++){
        scanf("%d", &baralho[i].valor);
        /* A posição é conatda começando do 1 */
        baralho[i].posicao = i + 1; 
    }
    /* Ordena o baralho para a busca binária */
    qsort(baralho, n, sizeof(Carta), comparar);
    /* Realiza a busca */
    int pos = busca_binaria(baralho, 0, n-1, k);
    
    /* Imprime a posição do item encontrado */
    printf("%d\n", pos);

    return 0;
}

/* Busca binária iterativa. Retorna a posição da primeira 
    aparição do valor k no vetor original. */
int busca_binaria(Carta *baralho, int ini, int fim, int k){
    while (ini <= fim){
        int meio = (ini + fim)/2; 
        int valor = baralho[meio].valor; 
        if (valor == k){
            // Itera até achar a primeira aparição do valor
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

    return -1; // Item não encontrado
}

/* Busca binária recursiva. Também retorna a posição da primeira 
    aparição do valor k no vetor original.*/
int binaria_recursiva(Carta *baralho, int ini, int fim, int k){
    int meio = (ini + fim)/2; 
        int valor = baralho[meio].valor; 
        if (valor == k){
            while (meio > 0 && baralho[meio-1].valor == k){
                meio--; 
            }
            return baralho[meio].posicao; 
        }
// Se há um item e seu valor não é k, então o elemento não foi encontrado
        if(ini==fim)
            return -1;

        if (k > valor)
            return binaria_recursiva(baralho, meio+1, fim, k); 
        if (k < valor)
            return binaria_recursiva(baralho, ini, meio, k);
}

// Usado pela função qsort para ordenar o vetor
int comparar(const void *A, const void *B){
    Carta *a = (Carta*)A, *b = (Carta*)B;
    if ((*a).valor > (*b).valor)
        return 1; 
    else if ((*a).valor == (*b).valor)
        return 0; 
    else
        return -1; 
}

int busca_linear(Carta *baralho, int n, int k){
    // Percorre o vetor de tamanho n
    for (int i = 0; i < n; i++){
        // Compara cada valor com o procurado
        if (baralho[i].valor == k){
        // Se encontrar, retorna a posição, começando do um
            return i+1; 
        }
    }
// Se o item não foi encontrado, retorna uma posição inválida
    return -1; 
}