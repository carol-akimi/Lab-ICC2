#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct prato_{
    int prioridade; 
    int tempo; 
    char nome[51]; 
}Prato;


void swap(Prato *a, Prato *b);
void merge_sort(Prato *cardapio, int ini, int fim);
void intercala(Prato *cardapio, int ini, int meio, int fim);
void heapify(Prato *cardapio, int i, int tam_heap);
void heapsort(Prato *cardapio, int n);
void build_heap(Prato *cardapio, int k);
void print_cardapio(Prato *cardapio, int k);


int main (void){
    //Quantidade de pratos 
    int k; 
    scanf("%d", &k);

    //Alocação do vetor cardapio para armazenar os pratos 
    Prato *cardapio;
    cardapio = (Prato*) malloc(sizeof(Prato)*k); 

    //Leitura dos dados 
    for (int i = 0; i < k; i++){
        scanf("%d %d %s", &cardapio[i].prioridade, &cardapio[i].tempo, cardapio[i].nome); 
    }

    //clock_t i1, f1, i2, f2;
    //i1=clock();
    //merge_sort(cardapio, 0, k-1);
    //f1=clock();

    //i2=clock();
    heapsort(cardapio, k);
    //f2=clock();

    //printf("\n");
    print_cardapio(cardapio, k);

    free(cardapio);

    //printf("\n\nTempo do merge Sort para %d elementos: %lf s\n", k, (double)(f1-i1)/CLOCKS_PER_SEC);
    //printf("\nTempo do Quicksort para %d elementos: %lf s\n", k, (double)(f2-i2)/CLOCKS_PER_SEC);

    return 0;
}

void swap(Prato *a, Prato *b){
    Prato aux; 
    aux = *a; 
    *a = *b; 
    *b= aux;
}

//coloquei no runcodes e não passa nos últimos dois casos 
void merge_sort(Prato *cardapio, int ini, int fim){
    int meio; 
    if (ini < fim){
        meio = (ini+fim)/2; 
        merge_sort(cardapio, ini, meio);
        merge_sort(cardapio, meio+1, fim); 
        intercala(cardapio, ini, meio, fim); 
    }
    return; 
}

void intercala(Prato *cardapio, int ini, int meio, int fim){
    int i, j, k; 
    int n1, n2; 
    n1 = meio - ini + 1;
    n2 = fim - meio;  
    Prato L[n1+1], R[n2+1];
    for (i = 0; i < n1; i++){
        L[i] = cardapio[ini+i]; 
    }
    for (j = 0; j < n2; j++){
        R[j] = cardapio[meio+j+1]; 
    }
    L[n1].prioridade = INT_MAX; 
    R[n2].prioridade = INT_MAX; 
    i = 0; j = 0; 
    for (k = ini; k <= fim; k++){
        if (L[i].prioridade == R[j].prioridade){
            if (L[i].tempo < R[j].tempo){
                cardapio[k] = R[j]; 
                j++;
            }else{
                cardapio[k] = L[i]; 
                i++;
            }
        }
        else if (L[i].prioridade < R[j].prioridade){
            cardapio[k] = L[i]; 
            i++;
        }
        else{
            cardapio[k] = R[j]; 
            j++;
        }
    }
}


void heapsort(Prato *cardapio, int n){
    build_heap(cardapio, n);
    int tam_heap = n; 
    for (int i = 0; i < n; i++){
        swap(&cardapio[0], &cardapio[tam_heap-1]); 
        tam_heap--;
        heapify(cardapio, 0, tam_heap); 
    }
}

void heapify(Prato *cardapio, int i, int tam_heap){  //construir max heap 
    int left, right, max; 
    left = 2*i + 1;
    right = 2*i + 2; 
    max = i; 
    if (left < tam_heap && cardapio[left].prioridade >= cardapio[max].prioridade){
        if (cardapio[left].prioridade == cardapio[max].prioridade){
            if (cardapio[left].tempo > cardapio[right].tempo){
                max = left; 
            }else{
                max = right; 
            }
        }else{
            max = left; 
        }
    }
    if (right < tam_heap && cardapio[right].prioridade > cardapio[max].prioridade){
        max = right; 

    }
    if (max != i){
        swap(&cardapio[max], &cardapio[i]); 
        heapify(cardapio, max, tam_heap);  
    }
}

void build_heap(Prato *cardapio, int k){
    for (int i = (k/2) - 1; i >= 0; i--){
        heapify(cardapio, i, k); 
    }
}

void print_cardapio(Prato *cardapio, int k){
    for (int i = 0; i < k; i++){
        printf("%s\n", cardapio[i].nome); 
    }
}