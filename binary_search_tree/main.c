#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no NO;
struct no{
    int valor;
    NO *esq, *dir;
};

void insert(NO** raiz, int valor);
void insercao(NO** raiz, int valor);
void busca_binaria(NO *raiz, int x);
int busca_profundidade(NO *raiz, int x);

int main(void){
    int n, valores, alvo;

    scanf("%d", &n);

    NO* raiz=NULL;

    //clock_t s, e;
    //s=clock();
    for(int i=0; i<n; i++){
        scanf("%d", &valores);
        insert(&raiz, valores);
    }
    scanf("%d", &alvo);
    //busca_binaria(raiz, alvo);
    busca_profundidade(raiz, alvo); 
    printf("\n");

    return 0;
}

/* Aparentemente é mais rápido que o recursivo */
void insert(NO** raiz, int valor){
    NO* ptr=*raiz;
    NO* pai=NULL;

    while(ptr!=NULL){
        pai=ptr;
        if(valor==ptr->valor)
            return;
        if(ptr->valor>valor)
            ptr=ptr->esq;
        else
            ptr=ptr->dir;
    }

    NO* novo=(NO*)malloc(sizeof(NO));
    novo->valor=valor;
    novo->esq=NULL;
    novo->dir=NULL;

    if(*raiz==NULL){
        *raiz=novo;
        return;
    }

    if(valor<pai->valor)
        pai->esq=novo;
    else
        pai->dir=novo;
}


void insercao(NO** raiz, int valor){
    if(*raiz==NULL){
        NO* novo=(NO*)malloc(sizeof(NO));
        novo->valor=valor;
        novo->esq=NULL;
        novo->dir=NULL;
        *raiz=novo;
    }else{
        if(valor<(*raiz)->valor)
            insercao(&(*raiz)->esq, valor);
        else
            insercao(&(*raiz)->dir, valor);
    }
}

void busca_binaria(NO* raiz, int x){
    if (raiz == NULL){
        printf("-1"); 
        return; 
    }
    printf("%d ", raiz->valor);
    if(raiz->valor == x)
        return;
    if(x < raiz->valor)
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
    return 0; 
}