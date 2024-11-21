#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Hashing(int* Produtos, int n);
int hash(int valor, int tam);
void inserir(int* Tabela, int valor, int tam_tabela);
int busca(int* Tabela, int valor, int tam);

int Ordenacao(int* Produtos, int n);
void QuickSort(int* vet, int inicio, int fim);
int mediana(int a, int b, int c);

int main(void){
    int n;

    scanf("%d", &n);

    int* Produtos = (int*) malloc(n*sizeof(int)); // Aloca o vetor

    for(int i = 0; i < n; i++) // Lê os valores e coloca no vetor
        scanf("%d", &Produtos[i]);

    int maior_seq; clock_t i, f;
    i = clock();
    maior_seq = Hashing(Produtos, n);
    f = clock();

    printf("%d\n", maior_seq);

    printf("\n\nTempo do Hashing para %d valores: %lf s\n", n, (double)(f-i)/CLOCKS_PER_SEC);
    //printf("\n\nTempo do Hashing para %d valores: %lf s\n", n, (double)(f-i)/CLOCKS_PER_SEC);
    return 0;
}

int Hashing(int* Produtos, int n){
    // Inicializa a tabela com zeros
    int* Tabela = (int*)calloc(n+n/2, sizeof(int));
    int tam_tabela = n+n/2; // Tamanho maior para reduzir colisões

    // Produtos são inseridos na tabela
    for(int i = 0; i < n; i++){
        inserir(Tabela, Produtos[i], tam_tabela);
    }

    int maxseq = 1;
    for(int i = 0; i < n; i++){
        int num = Produtos[i];
        // Procura o antecessor de cada elemento
        if(busca(Tabela, num-1, tam_tabela) == -1){
        // Quando acha algum valor que pode iniciar uma sequência, 
        // começa a contar. O laço procura os sucessores.
            int atual = num, cont = 1;
            while(busca(Tabela, atual+1, tam_tabela) != -1){
                atual++;
                cont++;
            } // Atualiza o valor do tamanho da maior sequência.
            if(cont > maxseq){
                maxseq = cont;
            }
        }
    }

    return maxseq;
}

// Função hash
int hash(int valor, int tam){
    return valor % tam;
}

/* Função para a inserção de um elemento do vetor na 
tabela com base na função hash e no método da sondagem 
linear para lidar com as colisões */
void inserir(int* Tabela, int valor, int tam_tabela){
    int indice = hash(valor, tam_tabela);
    while(Tabela[indice] != 0){
        indice = hash(indice + 1, tam_tabela);
    }
    Tabela[indice] = valor;
}

/* Função para buscar valores na tabela a partir da 
função hash e consultando os elementos adjacentes */
int busca(int* Tabela, int valor, int tam){
    int indice = hash(valor, tam),
    inicial = indice;
    while(Tabela[indice] != 0){
        if(Tabela[indice] == valor){
            return indice;
        }
        indice = hash(indice + 1, tam);
        if (indice == inicial){
            break;
        }
    }
    return -1;
    // Retorna -1 se a busca foi mal sucedida
}





int Ordenacao(int* Produtos, int n){
    QuickSort(Produtos, 0, n-1); // Ordena usando o quicksort
    // Variável que conta o tamanho da sequência atual e 
    // outra que guarda o tamanho da maior sequência até então
    int contador = 1, maxseq = 1;
    for(int i = 0; i < n; i++){
    // Itera pelos elementos e incrementa o contador durante uma sequência
        while(Produtos[i+1] == Produtos[i] + 1){
            contador++;
            i++;
        }
        // Atualiza o tamanho máximo se encontrar uma maior
        if(contador > maxseq)
            maxseq = contador;
        contador = 1;
    }

    return maxseq;
}

//Função devove a mediana dados três elementos
int mediana(int a, int b, int c){
    if((a >= b && a <= c)||(a <= b && a >= c))
        return a;
    else if((b>=a && b<=c)||(b<=a && b >= c))
        return b;
    else
        return c;
}

void QuickSort(int* vet, int inicio, int fim){
    int i = inicio; 
    int j = fim; 
    //o pivo é a mediana entre o elemento do inicio, meio e fim
    int pivo = mediana(vet[inicio], vet[(inicio+fim)/2], vet[fim]); 
    do{
        //organiza os elementos de forma que todos a esquerda
        //sejam menores e os da direita, maiores
        while (vet[i] < pivo) i++; 
        while (vet[j] > pivo) j--;  
        if (i <= j){
            //troca os elementos se o da direita é menor que um no lado esquerdo
            int aux = vet[i]; 
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