#include <stdio.h>
#include <stdlib.h>

typedef struct carta_{
    char naipe[5];
    char* valor_carta;
    short int *valor_sort;
}Carta;

short int* decode(char* str, int n_digitos);
void countingsort();
void radixsort();
void stoogesort();

int main(void){
    /* Declaração do número de cartas k e o número de dígitos dos valores. */
    int k, n_digitos;

    scanf("%d %d", &k, &n_digitos);

    /* Aloca o vetor das cartas. */
    Carta* baralho=(Carta*)malloc(k*sizeof(Carta));

    for(int i=0; i<k; i++){
        /* Aloca espaço para a string do valor da carta. */
        baralho[i].valor_carta = (char*)malloc(n_digitos*sizeof(char));
        /* Lê separadamente naipe e valor. */
        scanf(" %s %s", baralho[i].naipe, baralho[i].valor_carta);
        /* Recebe os valores da carta decodificados para a ordenação. */
        baralho[i].valor_sort = decode(baralho[i].valor_carta, n_digitos);
    }
        

}

/* Função que transforma a hierarquia dos valores em algarismos para serem 
manipulados pelos algoritmos de ordenação. */

short int* decode(char* valores, int n_digitos){
    /* Um vetor de short ints pe criado para guardar os dígitos do valor. */
    short int *decoded=(short int*)malloc(n_digitos*sizeof(short int));
    /* A cada símbolo da string com o valor é atribuido um algarismo 
    correspondente que mantém a ordem especificada no probolema. */
    for(int i=0; i<n_digitos; i++){
        switch(valores[i]){
            case '4': decoded[i]=0; break;
            case '5': decoded[i]=1; break;
            case '6': decoded[i]=2; break;
            case '7': decoded[i]=3; break;
            case 'Q': decoded[i]=4; break;
            case 'J': decoded[i]=5; break;
            case 'K': decoded[i]=6; break;
            case 'A': decoded[i]=7; break;
            case '2': decoded[i]=8; break;
            case '3': decoded[i]=9; break;
        }
    }
    
    return decoded;
}