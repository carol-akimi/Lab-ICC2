#include <stdio.h> 
#include <stdlib.h> 

/**
 * não roda nos últimos três casos do runcodes 
 */

int hash(int dado, int n){
    return dado % n;
}

int *iniciaTabela(int n){
    int *Tabela; 
    Tabela = (int*) malloc(sizeof(int)*n); 
    for (int i = 0; i < n; i++){
        Tabela[i] = 0; 
    }
    return Tabela; 
}

void inserir(int *Tabela, int valor, int n){
    int indice = hash(valor, n);
    while (Tabela[indice] != 0){
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

int MSC(int *Produtos, int n){
    int *Tabela; 
    Tabela = iniciaTabela(n); 
    for (int i = 0; i < n; i++){
        inserir(Tabela, Produtos[i], n); 
    }
    int cont = 0; 
    for (int i = 0; i < n; i++){
        int num = Produtos[i]; 
        if (busca(Tabela, n, num-1) == -1){ //o elemento antes desse não existe
            int atual = num; 
            int cont_atual = 1;  
        
            while (busca(Tabela, n, atual+1) != -1){
                atual++; 
                cont_atual++; 
            }
            if (cont_atual > cont)
                cont = cont_atual; 
        }
    }
    free(Tabela); 
    Tabela = NULL; 
    return cont; 
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
