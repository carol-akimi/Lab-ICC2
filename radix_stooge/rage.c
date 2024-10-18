/* Implementação final com um dígito por vez. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct carta_{
    char* valor; /* String com naipe e valores. */
    /* Dígito que representa o valor na atual posição.
        Muda a cada etapa da ordenação. */
    short int digito;
} Carta;

short int converte(char* valores, int pos);
Carta* radixsort(Carta* baralho, int tam, int n_dig);
Carta* counting_sort(Carta* baralho, int tam, int pos);
void print_array(Carta* baralho, int tam);

int main(void){
    /* Declaração do número de cartas k e o número de dígitos dos valores. */
    int k, n_digitos;

    scanf("%d %d", &k, &n_digitos);

    /* Aloca o vetor das cartas. */
    Carta* baralho=(Carta*)malloc(k*sizeof(Carta));

    for(int i=0; i<k; i++){
        /* Aloca espaço para as strings do naipe e do valor da carta. */
        char* naipe=(char*)malloc(5*sizeof(char));
        char* valor_carta = (char*)malloc(n_digitos*sizeof(char));
        /* Lê separadamente naipe e valor. */
        scanf(" %s %s", naipe, valor_carta);
        naipe[3]=' '; naipe[4]='\0'; /* Ajusta a string do naipe. */
        
        /* Aloca espaço para string unificada. */
        baralho[i].valor=(char*)malloc(strlen(naipe)+strlen(valor_carta));
        strcpy(baralho[i].valor, naipe); /* Copia cada uma para a principal. */
        strcat(baralho[i].valor, valor_carta);

        free(naipe);
        free(valor_carta);
        /* Libera a memória utilizada. */
    }
    /* Imprime a configuração inicial. */
    print_array(baralho, k);
    
    clock_t i, f;
    i=clock();
    baralho=radixsort(baralho, k, n_digitos); /* Ordena. */
    f=clock();

    /* Imprime o baralho depois do último passo da ordenação. */
    printf("Após ordenar por naipe:\n");
    print_array(baralho, k);

    printf("\nTempo do Radix Sort para %d cartas com %d valores: %lf\n", k, n_digitos+1, (double)(f-i)/CLOCKS_PER_SEC);

    /* Libera a memória alocada para o campo do valor de cada 
    carta e depois libera o espaço do vetor. */
    for(int i=0; i<k; i++)
        free(baralho[i].valor);
    
    free(baralho);

}

/* Função que transforma o valor de uma carta na determinada posição em um algarismo, 
segundo a ordem especificada, para ser manipulado pelos algoritmos de ordenação. */

short int converte(char* valores, int pos){
    short int res; /* Dígito resultante da conversão. */
    if(pos==0){ /* Se a posição é a primeira, deve-se converter o naipe. */
        /* Copia da string de valor a parte do naipe. */
        char naipe[4];
        strncpy(naipe, valores, 3);
        naipe[3]='\0';
        /* Relaciona cada naipe a um valor segundo a ordem. */
        if(strcmp(naipe, "♦")==0)
            res=0;
        else if(strcmp(naipe, "♠")==0)
            res=1;
        else if(strcmp(naipe, "♥")==0)
            res=2;
        else if(strcmp(naipe, "♣")==0)
            res=3;
    }else{ /* Se a posição não for zero, converte-se um valor em número. */
        /* Acessa o caracter na posição desejada da string. */
        char caracter=*(valores+pos+3);
        /* Designa um algarismo ao valor. */
        switch(caracter){
            case '4': res=0; break;
            case '5': res=1; break;
            case '6': res=2; break;
            case '7': res=3; break;
            case 'Q': res=4; break;
            case 'J': res=5; break;
            case 'K': res=6; break;
            case 'A': res=7; break;
            case '2': res=8; break;
            case '3': res=9; break;
        }
    }
    /* Retorna o dígito correspondente ao valor daquela posição. */
    return res;
}

/* Função que chama o counting_sort para cada conjunto de dígitos 
na posição i. */
Carta* radixsort(Carta* baralho, int tam, int n_dig){
    /* Começa ordenando pelo último dígito, até o primeiro (posição i=1). */
    for(int i=n_dig; i>0; i--){
        baralho=counting_sort(baralho, tam, i);
        printf("Após ordenar o %d° dígito dos valores:\n", i);
        print_array(baralho, tam);
    }
    /* Por fim, ordena os valores na posição 0, os naipes. */
    return counting_sort(baralho, tam, 0);
}

Carta* counting_sort(Carta* baralho, int tam, int pos){
    /* Vetor que guarda quantas ocorrências de cada dígito existem. */
    int tipos[10]={0};
    for(int i=0; i<tam; i++){
        /* Campo 'digito' da carta recebe o número correspondente ao 
            valor da carta na posição que está sendo avaliada. */
        baralho[i].digito=converte(baralho[i].valor, pos);
        tipos[baralho[i].digito]++; /* Incrementa o vetor de ocorrência de tipos. */
    }
    /* Acerta o vetor de ocorrências. */
    for(int i=1; i<10; i++)
        tipos[i]+=tipos[i-1];

    /* Aloca o vetor substituto. */
    Carta* sorted=malloc(tam*sizeof(Carta));

    /* Percorre o vetor original, acessa o vetor de tipos para o dígito do elemento i 
    e atribui o elemento ao vetor substituto na posição indicada por tipos[].*/
    for(int i=tam-1; i>=0; i--){
        /* Por padrão, o vetor é percorrido na ordem inversa a fim de manter a 
        estabilidade, mesmo que não seja um fator relevante para esse exercício. */
        sorted[tipos[baralho[i].digito]-1]=baralho[i];
        tipos[baralho[i].digito]--; /* Atualiza o vetor de ocorrências. */
    }

    /* Libera a memória do vetor original e retorna o ordenado. */
    free(baralho);
    return sorted;
}

/* Função que imprime as cartas de um baralho. */
void print_array(Carta* baralho, int tam){
    for(int i=0; i<tam; i++){
        printf("%s;", baralho[i].valor);
    }
    printf("\n");
}