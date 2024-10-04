#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

typedef struct prato_{
    int prioridade; 
    int tempo; 
    char nome[51]; 
}Prato;


void swap(Prato *a, Prato *b);
void merge_sort();
void heapify(Prato* cardapio);
void heapsort(Prato *cardapio, int n);
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
    merge_sort();
    //f1=clock();

    //i2=clock();
    //heapsort();
    //f2=clock();

    printf("\n");
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


void merge_sort(){

}


void heapsort(Prato *cardapio, int n){

}

void heapify(){  /* construir max heap */

}


void print_cardapio(Prato *cardapio, int k){
    for (int i = 0; i < k; i++){
        printf("%s\n", cardapio[i].nome); 
    }
}