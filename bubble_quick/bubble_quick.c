#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

typedef struct prato_{
    int prioridade; 
    int tempo; 
    char nome[51]; 
}Prato; 


void swap(Prato *a, Prato *b);
void bubble_sort(Prato *cardapio, int k);
void quick_sort(Prato *cardapio, int inicio, int fim);
int mediana(int a, int b, int c, Prato* cardapio);
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

    clock_t i1, f1, i2, f2;
    i1=clock();
    bubble_sort(cardapio, k);
    f1=clock();

    i2=clock();
    //quick_sort(cardapio, 0, k-1);
    f2=clock();

    printf("\n");
    print_cardapio(cardapio, k);

    free(cardapio);

    printf("\n\nTempo do Bubble Sort para %d elementos: %lf s\n", k, (double)(f1-i1)/CLOCKS_PER_SEC);
    //printf("\nTempo do Quicksort para %d elementos: %lf s\n", k, (double)(f2-i2)/CLOCKS_PER_SEC);

    return 0;
}


void swap(Prato *a, Prato *b){
    Prato aux; 
    aux = *a; 
    *a = *b; 
    *b= aux;
}


void bubble_sort(Prato *cardapio, int k){
    int trocas = 1;
    for(int i = 0; i < k-1; i++){
        trocas = 0; 
        for (int j = 0; j < k - i -1; j++){
            if (cardapio[j+1].prioridade < cardapio[j].prioridade){
                swap(&cardapio[j+1], &cardapio[j]); 
                trocas = 1; 
            } if (cardapio[j+1].prioridade == cardapio[j].prioridade){
                if(cardapio[j+1].tempo > cardapio[j].tempo){
                    swap(&cardapio[j+1], &cardapio[j]); 
                }
            }
        }
        if(trocas == 0)
            break; 
    }
}


void quick_sort(Prato *cardapio, int inicio, int fim){
    int i = inicio; 
    int j = fim;
    Prato pivo = cardapio[mediana(inicio, (inicio+fim)/2, fim, cardapio)];

    do {
        while (cardapio[i].prioridade < pivo.prioridade || (cardapio[i].prioridade==pivo.prioridade && cardapio[i].tempo>pivo.tempo)) i++; 
        while (cardapio[j].prioridade > pivo.prioridade || (cardapio[j].prioridade==pivo.prioridade && cardapio[j].tempo<pivo.tempo)) j--; 
        if (i <= j){
            swap(&cardapio[i], &cardapio[j]); 
            i++;
            j--; 
        }
    } while (i < j); 
    if (j > inicio) 
        quick_sort(cardapio, inicio, j);
    if(i < fim)
        quick_sort(cardapio, i, fim); 
}


/*  Função auxiliar para a escolha do pivô do Quicksort. Retorna o índice do pivô escolhido  */

int mediana(int a, int b, int c, Prato* cardapio){
        int x=cardapio[a].prioridade, y=cardapio[b].prioridade, z=cardapio[c].prioridade;

        if((x>=y && x<=z)||(x<=y && x>=z))
            return a;
        else if((y>=x && y<=z)||(y<=x && y>=z))
            return b;
        else
            return c;
}


void print_cardapio(Prato *cardapio, int k){
    for (int i = 0; i < k; i++){
        printf("%s\n", cardapio[i].nome); 
    }
}