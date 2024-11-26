#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct de um local contém seu nome e o id do destino
typedef struct{
    char* nomeLocal;
    int destino;
} local;

// Função hash para acesso a uma cidade a partir do nome
int hash(char* palavra, int tam_tabela){
    int indice = 0, tam = strlen(palavra);
    for(int i = 0; i < tam; i++) {
        indice *= palavra[i];
    }
    return indice % tam_tabela;
}

int main(void){
    int n, k;

    scanf("%d %d", &n, &k);

    // Vetor de structs 'local'. Locais[i] é o local cujo id é i+1
    local* Locais = (local*) malloc(n * sizeof(local));
    // Tabela que usa a função hash sobre o nome de um local para localizar o seu id.
    int* Tabela = (int*) calloc((n + n/3),sizeof(int));
    int tam_tabela = n + n/3; // Tamanho maior para reduzir colisões

    // Laço que preenche o vetor de Locais com os locais e a Tabela com os ids
    for(int i = 0; i < n; i++){
        char lugar[20]; int destino;
        scanf("%s %d", lugar, &destino);
        int indice = hash(lugar, tam_tabela);
        while(Tabela[indice] != 0) // Sondagem linear para lidar com colisões
            indice = (indice + 1) % tam_tabela;
        Tabela[indice] = i + 1; // De 1 a n para reconhecer "0" como vazio
        Locais[i].nomeLocal = strdup(lugar); // Aloca o nome;
        Locais[i].destino = destino; // Atribui o destino
    }

    // Laço que lê um passeio, executa e imprime o local final
    for(int i = 0; i< k; i++){
        char locInicial[20];
        int passos;
        scanf("%s %d", locInicial, &passos);

        // Recupera o índice associado ao nome do lugar de início
        int indice = hash(locInicial, tam_tabela);
        // Percorre a tabela linearmente em caso de colisão
        while(strcmp(Locais[Tabela[indice] - 1].nomeLocal, locInicial))
            indice = (indice + 1) % tam_tabela;    

        // Local atual é Locais[x], onde x é o id guardado por Tabela[indice]
        local locAtual  = Locais[Tabela[indice] - 1];
        // O local atual passa a ser Locais[id do destino do local atual -1], já que o vetor é zero-indexado
        // Assim, o local atual é constantemente atualizado para o seu destino a cada passo
        for(int j = passos; j > 0; j--){
            locAtual = Locais[locAtual.destino - 1];
        }

        // Ao final dos passos, imprime o nome do local atual
        printf("%s\n", locAtual.nomeLocal);
    }

    // Libera a memória das strings alocadas por strdup()
    for(int i = 0; i < n; i++){
        free(Locais[i].nomeLocal);
    }
    // Desaloca o vetor de locais e a tabela
    free(Tabela);
    free(Locais);

    return 0;
}