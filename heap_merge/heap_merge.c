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
void heapify(Prato *cardapio, int i, int tamanho);
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
    for(int i=n/2-1; i>=0; i--)
        heapify(cardapio, i, n);
    int tamanho=n;
    for(int i=n-1; i>0; i--){
        swap(cardapio+0, cardapio+i);
        tamanho--;
        heapify(cardapio, 0, tamanho);
    }
}

void heapify(Prato* cardapio, int i, int tamanho){
    int L, R, maior;
    L=2*i+1;
    R=2*i+2;
    if(L<tamanho && (cardapio[L].prioridade>cardapio[i].prioridade ||
    cardapio[L].prioridade==cardapio[i].prioridade && cardapio[L].tempo<cardapio[i].tempo))
        maior=L;
    else
        maior=i;
    if(R<tamanho && (cardapio[R].prioridade>cardapio[maior].prioridade||
    cardapio[R].prioridade==cardapio[maior].prioridade && cardapio[R].tempo<cardapio[maior].tempo))
        maior=R;
    if (maior!=i) {
        swap(cardapio+i, cardapio+maior);
        heapify(cardapio, maior, tamanho);
    }
}


void print_cardapio(Prato *cardapio, int k){
    for (int i = 0; i < k; i++){
        printf("%s\n", cardapio[i].nome); 
    }
}