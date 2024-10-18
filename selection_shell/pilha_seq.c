#include <stdio.h> 
#include <stdlib.h> 
#include "../../alg1/item/item.h"
#include "pilha.h"
#define TAM 1000000

struct pilha {
    ITEM *item[TAM]; //item não é alocado dinamicamente, o que é alocado são os itens 
    int tamanho;
};

PILHA *pilha_criar(void){
    PILHA *p; 
    p = (PILHA*) malloc(sizeof(PILHA));
    if (p != NULL){
        p->tamanho = 0; 
    }
    return p;
}

void pilha_apagar(PILHA** pilha){
    if (*pilha == NULL){
        return; 
    }
    int t = pilha_tamanho(*pilha); //variável com o tamanho da pilha 
    for (int i = 0; i < t; i++){
        item_apagar(&((*pilha)->item[i])); //a função item_apagar faz a desalocação dos itens 
    }
    free(*pilha); 
    *pilha = NULL; 
}

bool pilha_vazia(PILHA* pilha){
    if (pilha != NULL){
        return ((pilha->tamanho == 0) ? true : false); //se tam==0, return true else false 
    }
    return false; 
}

bool pilha_cheia(PILHA* pilha){
    if (pilha != NULL){
        return ((pilha->tamanho == TAM) ? true : false);
    }
    return false; 
}

int pilha_tamanho(PILHA* pilha){
    if (pilha != NULL){
        return pilha->tamanho; 
    }
}

ITEM* pilha_topo(PILHA* pilha){
    if (pilha != NULL && !pilha_vazia(pilha)){
        return (pilha->item[pilha->tamanho-1]);
    }
    return NULL; 
}

bool pilha_empilhar(PILHA* pilha, ITEM* item){
    if (!pilha_cheia(pilha)){ //a pilha não pode estar cheia, pilha_cheia já verifica se a pilha existe
        pilha->item[pilha->tamanho] = item; 
        pilha->tamanho++; 
        return true; 
    }
    return false; 
}

ITEM* pilha_desempilhar(PILHA* pilha){
    ITEM *it; 
    if (!pilha_vazia(pilha)){
        it = pilha_topo(pilha);  
        pilha->item[pilha->tamanho-1] = NULL; /*eu pensei em apagar o item, mas no codigo do rudinei 
        ele apenas tirou da pilha o que é feito com o item é responsabilidade do cliente*/
        pilha->tamanho--;  
        return it; 
    }
    return NULL; 
}