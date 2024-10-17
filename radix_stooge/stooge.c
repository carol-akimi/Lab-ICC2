/* Implementação final com um dígito por vez. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct carta_{
    char* valor; /* String com naipe e valores. */
    /* Dígito que representa o valor na atual posição. Muda a cada etapa da ordenação. */
    short int digito;
    short int anterior; 

}Carta;

short int converte(char* valores, int pos);
void stooge_full(Carta *baralho, int k, int n_digitos); 
void stooge(Carta *baralho, int ini, int fim);
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
    
    stooge_full(baralho, k, n_digitos); /* Ordena. */

    /* Imprime o baralho depois do último passo da ordenação. */
    //printf("Após ordenar por naipe:\n");
    print_array(baralho, k);

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
        if(strcmp(naipe, "♦") == 0)
            res=0;
        else if(strcmp(naipe, "♠") == 0)
            res=1;
        else if(strcmp(naipe, "♥") == 0)
            res=2;
        else if(strcmp(naipe, "♣") == 0)
            res=3;
    }else{ /* Se a posição não for zero, converte-se um valor em número. */
        /* Acessa o caracter na posição desejada da string. */
        char caracter =* (valores + pos + 3);
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

void stooge_full(Carta *baralho, int k, int n_digitos){
    for (int pos = n_digitos+1; pos > 0; pos--){
        for (int i = 0; i < k; i++){    
            baralho[i].digito = converte(baralho[i].valor, pos); 
        }
        stooge(baralho, 0, k-1); 
    }
    for (int i = 0; i < k; i++){    
        baralho[i].digito = converte(baralho[i].valor, 0); 
        baralho[i].anterior = converte(baralho[i].valor, 1); 
        baralho[i].digito = converte(baralho[i].valor, 0); 
    } 
    stooge(baralho, 0, k-1); 
}


void stooge(Carta *baralho, int ini, int fim){
    if (ini >= fim)
        return; 

    if (baralho[ini].digito > baralho[fim].digito){
        Carta aux; 
        aux = baralho[ini]; 
        baralho[ini] = baralho[fim]; 
        baralho[fim] = aux; 
    }
    if (baralho[ini].digito == baralho[fim].digito){
        if (baralho[ini].anterior > baralho[fim].anterior){
            Carta aux; 
            aux = baralho[ini]; 
            baralho[ini] = baralho[fim]; 
            baralho[fim] = aux; 
        }
    }    
    if (fim - ini + 1 > 2){ //tem mais que dois elementos 
        int t = (fim - ini + 1)/3; 
        stooge(baralho, ini, fim - t); 
        stooge(baralho, ini + t, fim); 
        stooge(baralho, ini, fim - t);
    }
    
}

/* Função que imprime as cartas de um baralho. */
void print_array(Carta* baralho, int tam){
    for(int i=0; i<tam; i++){
        printf("%s;", baralho[i].valor);
    }
    printf("\n");
}