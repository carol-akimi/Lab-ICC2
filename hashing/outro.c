#include <stdio.h> 
#include <stdlib.h> 


/**
 * versão que o chatpgt fez e passa por todos os testes 
 * ele faz praticamente a mesma coisa só que sem usar funções 
 */
int hash(int dado, int n){
    return ((dado % n)+n) % n;
}

int *iniciaTabela(int n){
    int *Tabela; 
    Tabela = (int*) malloc(sizeof(int)*n*2); 
    for (int i = 0; i < n; i++){
        Tabela[i] = 0; 
    }
    return Tabela; 
}

void inserir(int *Tabela, int valor, int n){
    int indice = hash(valor, n);
    while (Tabela[indice] != 0 && Tabela[indice] != valor){
        indice = hash(indice + 1, n); 
    }
    if (indice < n){
        Tabela[indice] = valor; 
    }

}

int busca(int *Tabela, int n, int chave){
    int indice = hash(chave, n);
    int inicial = indice; 
    while(Tabela[indice] != 0){
        if (Tabela[indice] == chave){
            return indice; 
        }
        indice = hash(indice + 1,n); 
        if (indice == inicial){
            break; 
        }
    }
    return -1; 
}


// Função para encontrar o maior entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para calcular a maior sequência consecutiva (MSC)
int MSC(int *Produtos, int n) {
    // Passo 1: Criar um conjunto (tabela hash) para armazenar os elementos
    int *hashSet = (int *)calloc(n * 2, sizeof(int)); // Tabela hash com tamanho maior para evitar colisões
    int set_size = n * 2;

    // Inicializar o conjunto
    for (int i = 0; i < n * 2; i++) {
        hashSet[i] = 0;
    }

    // Inserir os elementos no conjunto
    for (int i = 0; i < n; i++) {
        int index = Produtos[i] % set_size;
        while (hashSet[index] != 0 && hashSet[index] != Produtos[i]) {
            index = (index + 1) % set_size; // Resolver colisões com encadeamento linear
        }
        hashSet[index] = Produtos[i];
    }

    // Passo 2: Calcular a maior sequência consecutiva
    int longest = 0;
    for (int i = 0; i < n; i++) {
        int num = Produtos[i];

        // Verificar se é o início de uma sequência (num - 1 não está no conjunto)
        int prev = (num - 1) % set_size;
        if (prev < 0) prev += set_size;

        int foundPrev = 0;
        int indexPrev = prev;
        while (hashSet[indexPrev] != 0) {
            if (hashSet[indexPrev] == num - 1) {
                foundPrev = 1;
                break;
            }
            indexPrev = (indexPrev + 1) % set_size;
        }

        // Se não encontrou (num - 1), então é o início de uma sequência
        if (!foundPrev) {
            int currentNum = num;
            int currentLength = 1;

            // Expandir a sequência para frente (num + 1, num + 2, ...)
            while (1) {
                int next = (currentNum + 1) % set_size;
                if (next < 0) next += set_size;

                int foundNext = 0;
                int indexNext = next;
                while (hashSet[indexNext] != 0) {
                    if (hashSet[indexNext] == currentNum + 1) {
                        foundNext = 1;
                        break;
                    }
                    indexNext = (indexNext + 1) % set_size;
                }

                if (foundNext) {
                    currentNum++;
                    currentLength++;
                } else {
                    break;
                }
            }

            // Atualizar o maior comprimento
            longest = max(longest, currentLength);
        }
    }

    // Liberar memória da tabela hash
    free(hashSet);
    return longest;
}

int main(void){

    int n; 
    scanf("%d", &n); 
    int *Produtos; 
    Produtos = (int*) malloc(sizeof(int)*n); 
    for (int i = 0; i < n; i++){
        scanf("%d", &Produtos[i]); 
    }
    int cont = 0; 
    cont = MSC(Produtos, n); 
    printf("%d\n", cont); 
}
