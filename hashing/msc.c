#include <stdio.h>
#include <stdlib.h>

void Ordenacao(int n);
void QuickSort(long int* vet, int inicio, int fim);
int mediana(long int a, long int b, long int c);

int main(void){
    int n;

    scanf("%d", &n);

    Ordenacao(n);    

    return 0;
}

void MSC(int n){
    long int* Produtos = (long int*) malloc(n*sizeof(long int));
    long int elemento;
    short int* contagem = (short int*) calloc(n*sizeof(short int));

    int j, contador; char novaseq = 1;
    for(int i = 0; i < n; i++)
        scanf("%ld", &Produtos[i]);
        
}


void Ordenacao(int n){
    long int* Produtos = (long int*) malloc(n*sizeof(long int));

    for(int i = 0; i < n; i++)
        scanf("%ld", &Produtos[i]);
    
    QuickSort(Produtos, 0, n-1);

    int contador = 1, maxseq = 1;

    int j;
    for(int i = 0; i < n; i++){
        for(j = i; Produtos[j+1] == Produtos[j] + 1; j++)
            contador++;
        if(contador > maxseq)
            maxseq = contador;
        contador = 1;
        i = j;
    }

    printf("%d\n", maxseq);
}

//Função devove a mediana dados três elementos
int mediana(long int a, long int b, long int c){
    if((a >= b && a <= c)||(a <= b && a >= c))
        return a;
    else if((b>=a && b<=c)||(b<=a && b >= c))
        return b;
    else
        return c;
}

void QuickSort(long int* vet, int inicio, int fim){
    int i = inicio; 
    int j = fim; 
    //o pivo é a mediana entre o elemento do inicio, meio e fim
    long int pivo = mediana(vet[inicio], vet[(inicio+fim)/2], vet[fim]); 
    do{
        //organiza os elementos de forma que todos a esquerda
        //sejam menores e os da direita, maiores
        while (vet[i] < pivo) i++; 
        while (vet[j] > pivo) j--;  
        if (i <= j){
            //troca os elementos se o da direita é menor que um no lado esquerdo
            long int aux = vet[i]; 
            vet[i] = vet[j]; 
            vet[j] = aux; 
            i++; 
            j--; 
        }
    //para a iteração quando i e j se "cruzam"
    //chama recursivamente a função para cada metade do vetor
    }while (i < j); 
    if (j > inicio)
        QuickSort(vet, inicio, j); 
    if (i < fim)
        QuickSort(vet, i, fim);
}