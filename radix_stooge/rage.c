/* Versao com potência de 10 não terminada*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct carta_{
    char* valor; /* Armazena o valor da carta convertido para inteiros. */
}Carta;

long long int converte_pow(char naipe[4], char* valores, int n_digitos);
Carta* radixsort(Carta* baralho, int tam, int n_dig);
Carta* counting_sort(Carta* baralho, int tam, int pos);
void print_array(Carta* baralho, int tam);
short int converte_cada(char* valor_carta, int pos);

int main(void){
    /* Declaração do número de cartas k e o número de dígitos dos valores. */
    int k, n_digitos;

    scanf("%d %d", &k, &n_digitos);

    /* Aloca o vetor das cartas. */
    Carta* baralho=(Carta*)malloc(k*sizeof(Carta));

    for(int i=0; i<k; i++){
        /* Aloca espaço para a string do valor da carta. */
        char* valor_carta = (char*)malloc(n_digitos*sizeof(char));
        char* naipe=(char*)malloc((5+n_digitos)*sizeof(char));
        /* Lê separadamente naipe e valor. */
        scanf(" %s %s", naipe, valor_carta);
        naipe[3]=' ';
        /* Recebe naipe e valores da carta convertidos para a ordenação. */
        baralho[i].valor = strcat(naipe, valor_carta);
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
        free(baralho[i].valor);
    }
    free(baralho);

}

/* Função que transforma o naipe e os valores das cartas em algarismos, segundo 
a ordem especificada, para serem manipulados pelos algoritmos de ordenação. */

// long long int converte_pow(char naipe[4], char* valores, int n_digitos){
//     /* Um vetor de short ints é criado para guardar os dígitos do valor. */
//     long double soma=0;
//     /* Relaciona cada naipe a um valor segundo a ordem. */
//     if(strcmp(naipe, "♦")==0)
//         soma+=0*pow(10, n_digitos);
//     else if(strcmp(naipe, "♠")==0)
//         soma+=1*pow(10, n_digitos);
//     else if(strcmp(naipe, "♥")==0)
//         soma+=2*pow(10, n_digitos);
//     else if(strcmp(naipe, "♣")==0)
//         soma+=3*pow(10, n_digitos);
//     /* A cada símbolo da string com o valor é atribuido um algarismo 
//     correspondente que mantém a ordem especificada no probolema. */
//     for (int i=n_digitos-1; i>=0; i--){
//         switch(valores[i]){
//             case '4': soma+=0*pow(10, n_digitos-i-1); break;
//             case '5': soma+=1*pow(10, n_digitos-i-1); break;
//             case '6': soma+=2*pow(10, n_digitos-i-1); break;
//             case '7': soma+=3*pow(10, n_digitos-i-1); break;
//             case 'Q': soma+=4*pow(10, n_digitos-i-1); break;
//             case 'J': soma+=5*pow(10, n_digitos-i-1); break;
//             case 'K': soma+=6*pow(10, n_digitos-i-1); break;
//             case 'A': soma+=7*pow(10, n_digitos-i-1); break;
//             case '2': soma+=8*pow(10, n_digitos-i-1); break;
//             case '3': soma+=9*pow(10, n_digitos-i-1); break;
//         }
//     }
    
//     return (long long int)soma; /* Retorna a soma acumulada dos valores. */
// }

short int converte_cada(char* valor_carta, int pos){
    /* Um vetor de short ints é criado para guardar os dígitos do valor. */
    short int res;
    if(pos==0){
        char naipe[3];
        strncpy(naipe, valor_carta, 3);
        /* Relaciona cada naipe a um valor segundo a ordem. */
        if(strcmp(naipe, "♦")==0)
            res=0;
        else if(strcmp(naipe, "♠")==0)
            res=1;
        else if(strcmp(naipe, "♥")==0)
            res=2;
        else if(strcmp(naipe, "♣")==0)
            res=3;
    }else{
        char caracter=*(valor_carta+pos+3);
        /* A cada símbolo da string com o valor é atribuido um algarismo 
        correspondente que mantém a ordem especificada no probolema. */
        
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
    
    return res; /* Retorna a soma acumulada dos valores. */
}

Carta* radixsort(Carta* baralho, int tam, int n_dig){
    for(int i=n_dig-1; i>0; i--){
        baralho=counting_sort(baralho, tam, i);
        printf("Após ordenar o %d° dígito dos valores:\n", i+1);
        print_array(baralho, tam);
    }
    
    return counting_sort(baralho, tam, 0);
}

Carta* counting_sort(Carta* baralho, int tam, int pos){
    short int tipos[10]={0};
    short int* input=(short int*)malloc(tam*sizeof(short int));
    for(int i=0; i<tam; i++){
        short int valor_carta_i=converte_cada(baralho[i].valor, pos);
        tipos[valor_carta_i]++;
        input[i]=valor_carta_i;
    }
    for(int i=1; i<10; i++)
        tipos[i]+=tipos[i-1];

    Carta* sorted=malloc(tam*sizeof(Carta));

    for(int i=tam-1; i>=0; i--){
        sorted[tipos[input[i]]-1]=baralho[i];
        tipos[input[i]]--;
    }

    free(baralho);
    return sorted;
}

void print_array(Carta* baralho, int tam){
    for(int i=0; i<tam; i++){
        printf("%s;", baralho[i].valor);
    }
    printf("\n");
}