#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int valor;
    NO *esq, *dir;
};

void insere(NO** raiz, int valor);
void busca_binaria(NO *raiz, int x);

int main(void){
    int n, valores, alvo;

    scanf("%d", &n);

    /* Cria a raíz da árvore */
    NO* raiz=NULL;

    /* Inicializa os elementos e insere */
    for(int i=0; i<n; i++){
        scanf("%d", &valores);
        insere(&raiz, valores);
    }
    scanf("%d", &alvo);

    /* Chama a função de busca */
    busca_binaria(raiz, alvo);
    printf("\n");

    return 0;
}

/* Função que recebe a raíz de uma árvore e cria e insere 
    um nó com o inteiro valor na devida posição de forma que 
    a árvore seja mantida uma árvore binária de busca. */

void insere(NO** raiz, int valor){
    NO* ptr=*raiz;
    NO* pai=NULL;

    while(ptr!=NULL){
        pai=ptr; /* Guarda o nó pai antes de reatribuir ptr a um dos filhos */
        /* Se o valor já estiver na árvore, retorna sem inserir */
        if(valor==ptr->valor)
            return;
        /* Se o valor é menor do que o do nó atual, passa para o da esquerda */
        if(ptr->valor>valor)
            ptr=ptr->esq;
        /* Se o valor é maior, vai para o da direita */
        else
            ptr=ptr->dir;
    }
    /* Sai do loop quando econtrar a posição de inserção, onde ptr é NULL e 
        seu nó pai está guardado na variável */

    /* Aloca memória e inicializa devidamente o novo nó */
    NO* novo=(NO*)malloc(sizeof(NO));
    novo->valor=valor;
    novo->esq=NULL;
    novo->dir=NULL;

    /* Se a raíz é nula, ou seja, a árvore está vazia, então o novo nó 
        será atribuído à raíz */
    if(*raiz==NULL){
        *raiz=novo;
        return;
    }

    /* Decide em qual lado do nó pai o filho será inserido */
    if(valor<pai->valor)
        pai->esq=novo;
    else
        pai->dir=novo;
}


void insere_recursivo(NO** raiz, int valor){
    /* Condição de parada: atingiu um nó nulo, onde se pode 
        fazer a inserção */
    if(*raiz==NULL){
        NO* novo=(NO*)malloc(sizeof(NO));
        novo->valor=valor;
        novo->esq=NULL;
        novo->dir=NULL;
        *raiz=novo;
    }else{
        /* Enquanto não chega em um nó nulo, percorre pela esquerda 
            se o valor for menor do que a raíz atual, e pela direita 
            caso contrário */
        if(valor<(*raiz)->valor)
            insere_recursivo(&(*raiz)->esq, valor);
        else
            insere_recursivo(&(*raiz)->dir, valor);
    }
}

void busca_binaria(NO* raiz, int x){
    if (raiz == NULL){
        printf("-1"); 
        return; 
    }/* Imprime um valor inválido se não encontrar */
    /* Imprime o valor do nó atual */
    printf("%d ", raiz->valor);
    /* Para a recursão se o elemento foi encontrado */
    if(raiz->valor==x){
        return;
    }
    /* Se não, busca pela esquerda se o x for menor do 
        que o valor atual, e pela direita se for maior */
    if(x<raiz->valor)
        busca_binaria(raiz->esq, x);
    else
        busca_binaria(raiz->dir, x);

}

int busca_profundidade(NO *raiz, int x){
    if (raiz != NULL){
        printf("%d ", raiz->valor);
        if (raiz->valor == x){
            return 1; 
        }
        if (busca_profundidade(raiz->esq, x))
            return 1; 
        if (busca_profundidade(raiz->dir, x))
            return 1;
    }
}