/* Implementação final com um dígito por vez. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct carta_{
    char* valor; /* String com naipe e valores. */
    /* Dígito que representa o valor na atual posição. Muda a cada etapa da ordenação. */
    short int *valor_converte; 

}Carta;

short int* converte(char* valores, int n_digitos);
Carta* radixsort(Carta* baralho, int tam, int n_dig);
Carta* counting_sort(Carta* baralho, int tam, int pos);
void stooge_full(Carta *baralho, int k, int n_digitos); 
void stooge(Carta *baralho, int ini, int fim, int pos);
void print_array(Carta* baralho, int tam);

int main(void){
    /* Declaração do número de cartas k e o número de dígitos dos valores. */
    int k, n_digitos;

    scanf("%d %d", &k, &n_digitos);

    /* Aloca o vetor das cartas. */
    Carta* baralho=(Carta*)malloc(k*sizeof(Carta));

    for(int i=0; i<k; i++){
        /* Aloca espaço para as strings do naipe e do valor da carta. */
        char* naipe = (char*)malloc(5*sizeof(char));
        char* valor_carta = (char*)malloc(n_digitos*sizeof(char));

        /* Lê separadamente naipe e valor. */
        scanf(" %s %s", naipe, valor_carta);
        naipe[3]=' '; naipe[4]='\0'; /* Ajusta a string do naipe. */
        
        /* Aloca espaço para string unificada. */
        baralho[i].valor= (char*) malloc(strlen(naipe) + strlen(valor_carta));
        strcpy(baralho[i].valor, naipe); /* Copia cada uma para a principal. */
        strcat(baralho[i].valor, valor_carta);

        free(naipe);
        free(valor_carta);
        /* Libera a memória utilizada. */
    }

    clock_t ini1, fim1, ini2, fim2;

    /* Imprime a configuração inicial. */
    // print_array(baralho, k);
    // ini1=clock();
    // baralho=radixsort(baralho, k, n_digitos); /* Ordena. */
    // fim1=clock();
    // /* Imprime o baralho depois do último passo da ordenação. */
    // printf("Após ordenar por naipe:\n");
    // print_array(baralho, k);
    // printf("\nTempo do Radix Sort para %d cartas com %d valores: %lf s\n", k, n_digitos+1, (double)(fim1-ini1)/CLOCKS_PER_SEC);

    ini2 = clock();
    stooge_full(baralho, k, n_digitos); /* Ordena. */
    fim2 = clock(); 
    print_array(baralho, k);
    printf("\nTempo do Stooge Sort para %d cartas com %d valores: %lf s\n", k, n_digitos+1, (double)(fim2-ini2)/CLOCKS_PER_SEC);

    /* Libera a memória alocada para o campo do valor de cada 
    carta e depois libera o espaço do vetor. */
    for(int i=0; i<k; i++)
        free(baralho[i].valor);
    
    free(baralho);

}

/* Função que transforma o valor de uma carta na determinada posição em um algarismo, 
segundo a ordem especificada, para ser manipulado pelos algoritmos de ordenação. */

short int* converte(char* valores, int n_digitos){
    /* Um vetor de short ints é criado para guardar os dígitos do valor. */
    short int *valor_sort=(short int*)malloc((n_digitos+1)*sizeof(short int));
    /* Relaciona cada naipe a um valor segundo a ordem. */
    char naipe[4];
    strncpy(naipe, valores, 3);
    naipe[3]='\0';
    if(strcmp(naipe, "♦") == 0)
        valor_sort[0] = 0;
    else if(strcmp(naipe, "♠") == 0)
        valor_sort[0] = 1;
    else if(strcmp(naipe, "♥") == 0)
        valor_sort[0] = 2;
    else if(strcmp(naipe, "♣") == 0)
        valor_sort[0] = 3;
    /* A cada símbolo da string com o valor é atribuido um algarismo 
    correspondente que mantém a ordem especificada no probolema. */
    for (int i = 0; i <= n_digitos; i++){
        switch(valores[i+3]){
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
}

Carta* radixsort(Carta* baralho, int tam, int n_dig){
    for (int i = 0; i < tam; i++){    
        baralho[i].valor_converte = converte(baralho[i].valor, n_dig+4); 
    }
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
        tipos[baralho[i].valor_converte[pos]]++;
    }
    for(int i=1; i<10; i++)
        tipos[i]+=tipos[i-1];

    Carta* sorted=malloc(tam*sizeof(Carta));

    for(int i=tam-1; i>=0; i--){
        sorted[tipos[baralho[i].valor_converte[pos]]-1]=baralho[i];
        tipos[baralho[i].valor_converte[pos]]--;
    }

    free(baralho);
    return sorted;
}

void stooge_full(Carta *baralho, int k, int n_digitos){
    for (int i = 0; i < k; i++){    
        baralho[i].valor_converte = converte(baralho[i].valor, n_digitos+4); 
    } 

    for (int j = n_digitos; j >= 0; j--){
        stooge(baralho, 0, k-1, j); 
    }
}


void stooge(Carta *baralho, int ini, int fim, int pos){
    if (ini >= fim)
        return; 

    if (baralho[ini].valor_converte[pos] > baralho[fim].valor_converte[pos]){
        Carta aux; 
        aux = baralho[ini]; 
        baralho[ini] = baralho[fim]; 
        baralho[fim] = aux; 
    }
    
    if (baralho[ini].valor_converte[pos] == baralho[fim].valor_converte[pos]){
        int p = pos + 1; 
    
        while (p >= 0 && baralho[ini].valor_converte[p] == baralho[fim].valor_converte[p]) {
            p++;  // Continua verificando os valores anteriores enquanto forem iguais
        }
        // Se encontramos uma diferença em posições anteriores, trocamos
        if (p >= 0 && baralho[ini].valor_converte[p] > baralho[fim].valor_converte[p]) {
            Carta aux; 
            aux = baralho[ini]; 
            baralho[ini] = baralho[fim]; 
            baralho[fim] = aux; 
        }
    } 

    if (fim - ini + 1 > 2){ //tem mais que dois elementos 
        int t = (fim - ini + 1)/3; 
        stooge(baralho, ini, fim - t, pos); 
        stooge(baralho, ini + t, fim, pos); 
        stooge(baralho, ini, fim - t, pos);
    }
    
}

/* Função que imprime as cartas de um baralho. */
void print_array(Carta* baralho, int tam){
    for(int i=0; i<tam; i++){
        printf("%s;", baralho[i].valor);
    }
    printf("\n");
}