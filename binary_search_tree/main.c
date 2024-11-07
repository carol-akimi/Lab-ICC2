#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int valor;
    NO *esq, *dir;
};

void insert(NO* raiz, int valor);

int main(void){
    int n, valores, alvo;

    scanf("%d", &n);

    NO* raiz=NULL;

    for (int i=0; i<n; i++){
        scanf("%d", &valores);
        insert(raiz, valores);
    }

    scanf("%d", &alvo);

    printf("%d\n", raiz->valor);

    return 0;
}

/* dando seg fault, provavelmente tá mal feito */
void insert(NO* raiz, int valor){
    NO* ptr=raiz;
    while(ptr!=NULL){
        printf("%d\n", ptr->valor);
        if(ptr->valor==valor)
            return;
        if(ptr->valor<valor){
            if(ptr->dir==NULL)
                break;
            ptr=ptr->dir;
        }
        else{
            if(ptr->esq==NULL)
                break;
            ptr=ptr->esq;
        }
    }

    NO* novo = (NO*)malloc(sizeof(NO));
    novo->valor=valor;
    novo->esq=NULL;
    novo->dir=NULL;

    if(ptr!=NULL){
        if(valor<ptr->valor)
            ptr->esq=novo;
        else
            ptr->dir=novo;
    }
    
}