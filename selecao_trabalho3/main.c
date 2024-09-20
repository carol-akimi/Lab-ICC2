#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "../../alg1/item/item.h"
#include "pilha.h"
#include <time.h>


typedef struct {
    char nome[51];
    int nota; 
}pessoa; 


void shell_sort(pessoa *jogadores, int n);
PILHA *selecao(pessoa *jogadores, int n);
void imprimir_vetor(pessoa *jogadores, int n);
void imprimir_pilha(PILHA *p, int n);


int main(void){
    int n; 
    scanf("%d", &n); 
    pessoa *jogadores = (pessoa*) malloc(sizeof(pessoa)*n);

    for (int i = 0; i < n; i++){ //recebe os dados e coloca no vetor jogadores 
        scanf("%s %d", jogadores[i].nome, &(jogadores[i].nota));
    }
    clock_t start_1 = clock(); 
    shell_sort(jogadores, n);
    clock_t end_1 = clock(); 
    printf("\nOrdenação com shell_sort\n");
    imprimir_vetor(jogadores, n); 
    printf("O tempo de execução do shell sort foi de %lf\n", ((double) (end_1 - start_1)) / CLOCKS_PER_SEC);
    clock_t start_2 = clock();
    PILHA *p = selecao(jogadores, n);
    clock_t end_2 = clock(); 
    printf("\nOrdenação com selection_sort\n"); 
    imprimir_pilha(p, n);
    printf("O tempo de execução do selection sort foi de %lf\n", ((double) (end_2 - start_2)) / CLOCKS_PER_SEC);
    
    pilha_apagar(&p);
    free(jogadores);
    jogadores = NULL; 
    return (0);
}


void shell_sort(pessoa *jogadores, int n){
    for(int tam=n/2; tam>0; tam/=2){
        for(int i=tam; i<n; i++){
            pessoa temp=jogadores[i];
            int j;
            for(j=i; j>=tam && (jogadores[j-tam].nota>temp.nota||(jogadores[j-tam].nota==temp.nota && strcmp(jogadores[j-tam].nome, temp.nome)<0)); j-=tam)
                jogadores[j]=jogadores[j-tam];
            
            jogadores[j]=temp;
        }
    }
}


PILHA *selecao(pessoa *jogadores, int n){
    PILHA *p; 
    p = pilha_criar();  
    for (int i = 0; i < n; i++){
        pessoa *min;
        min = (pessoa*) malloc(sizeof(pessoa));  
        *min = jogadores[i];
        int posicao = i; 
        //procura pelo menor elemento
        for (int j = i + 1; j < n; j++){
            //se a nota for menor, há uma troca 
            if (jogadores[j].nota < min->nota){
                *min = jogadores[j]; 
                posicao = j; 
            }
            //se a nota for a mesma, colocamos o nome em ordem alfabética
            if (jogadores[j].nota == min->nota){ 
                if((strcmp(jogadores[j].nome, min->nome)) >= 0){ //if s1 < s2 numero negativo 
                    *min = jogadores[j]; 
                    posicao = j; 
                }
            }
        }
        //cria um item e o empilha na pilha em ordem crescente de notas
        ITEM *it = item_criar(i, min);
        pilha_empilhar(p, it);  
        //o lugar do elemento que foi empilhado é ocupado pelo elemento 
        //que está na posição i 
        jogadores[posicao] = jogadores[i];    
    }
    return p; 
}


void imprimir_vetor(pessoa *jogadores, int n){
    for (int i = n-1; i >= 0; i--){
        printf("%s %d\n", jogadores[i].nome, jogadores[i].nota);
    }
    return; 
}


void imprimir_pilha(PILHA* pilha, int n){
    pessoa* jogador;
    for(int i=0; i<n; i++){
        jogador=(pessoa*)item_get_dados(pilha_desempilhar(pilha));
        printf("%s %d\n", jogador->nome, jogador->nota);
    }
}