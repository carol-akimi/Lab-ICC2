/* Implementação inicial com vetor de short ints. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct carta_{
    char naipe[4];
    char* valor_carta;
    /* Cada short int do vetor é um dígito correspondente a cada valor da carta na mesma posição. */
    short int *valor_sort;
}Carta;

short int* converte(char naipe[4], char* valores, int n_digitos);
Carta* radixsort(Carta* baralho, int tam, int n_dig);
Carta* counting_sort(Carta* baralho, int tam, int pos);
void print_array(Carta* baralho, int tam);

int main(void){
    /* Declaração do número de cartas k e o número de dígitos dos valores. */
    int k, n_digitos;

    scanf("%d %d", &k, &n_digitos);

    /* Aloca o vetor das cartas. */
    Carta* baralho =(Carta*)malloc(k*sizeof(Carta));

    for(int i=0; i<k; i++){
        /* Aloca espaço para a string do valor da carta. */
        baralho[i].valor_carta = (char*)malloc(n_digitos*sizeof(char));
        /* Lê separadamente naipe e valor. */
        scanf(" %s %s", baralho[i].naipe, baralho[i].valor_carta);
        /* Recebe naipe e valores da carta convertidos para a ordenação. */
        baralho[i].valor_sort = converte(baralho[i].naipe, baralho[i].valor_carta, n_digitos);
    }
    /* Imprime a configuração inicial. */
    print_array(baralho, k);
    
    baralho=radixsort(baralho, k, n_digitos); /* Ordena. */

    /* Imprime o baralho depois do último passo da ordenação. */
    printf("Após ordenar por naipe:\n");
    print_array(baralho, k);

    /* Libera a memória alocada para os campos de cada carta e depois libera 
        o espaço do vetor. */
    for(int i=0; i<k; i++){
        free(baralho[i].valor_carta);
        free(baralho[i].valor_sort);
    }
    free(baralho);

}

/* Função que transforma o naipe e os valores das cartas em algarismos, segundo 
a ordem especificada, para serem manipulados pelos algoritmos de ordenação. */

short int* converte(char naipe[4], char* valores, int n_digitos)
    /* Um vetor de short ints é criado para guardar os dígitos do valor. */
    short int *valor_sort=(short int*)malloc((n_digitos+1)*sizeof(short int));
    /* Relaciona cada naipe a um valor segundo a ordem. */
    if(strcmp(naipe, "♦")==0)
        valor_sort[0]=0;
    else if(strcmp(naipe, "♠")==0)
        valor_sort[0]=1;
    else if(strcmp(naipe, "♥")==0)
        valor_sort[0]=2;
    else if(strcmp(naipe, "♣")==0)
        valor_sort[0]=3;
    /* A cada símbolo da string com o valor é atribuido um algarismo 
    correspondente que mantém a ordem especificada no probolema. */
    for (int i=1; i<=n_digitos; i++){
        switch(valores[i-1]){
            case '4': valor_sort[i]=0; break;
            case '5': valor_sort[i]=1; break;
            case '6': valor_sort[i]=2; break;
            case '7': valor_sort[i]=3; break;
            case 'Q': valor_sort[i]=4; break;
            case 'J': valor_sort[i]=5; break;
            case 'K': valor_sort[i]=6; break;
            case 'A': valor_sort[i]=7; break;
            case '2': valor_sort[i]=8; break;
            case '3': valor_sort[i]=9; break;
        }
    }
    
    return valor_sort; /* Retorna um vetor de short ints. */


Carta* radixsort(Carta* baralho, int tam, int n_dig){
    for(int i=n_dig; i>0; i--){
        baralho=counting_sort(baralho, tam, i);
        printf("Após ordenar o %d° dígito dos valores:\n", i);
        print_array(baralho, tam);
    }
    
    return counting_sort(baralho, tam, 0);
}

Carta* counting_sort(Carta* baralho, int tam, int pos){
    int tipos[10]={0};
    for(int i=0; i<tam; i++){
        tipos[baralho[i].valor_sort[pos]]++;
    }
    for(int i=1; i<10; i++)
        tipos[i]+=tipos[i-1];

    Carta* sorted=malloc(tam*sizeof(Carta));

    for(int i=tam-1; i>=0; i--){
        sorted[tipos[baralho[i].valor_sort[pos]]-1]=baralho[i];
        tipos[baralho[i].valor_sort[pos]]--;
    }

    free(baralho);
    return sorted;
}

void print_array(Carta* baralho, int tam){
    for(int i=0; i<tam; i++){
        printf("%s %s;", baralho[i].naipe, baralho[i].valor_carta);
    }
    printf("\n");
}