#ifndef _PILHA_H
    #define _PILHA_H

    #include "../../alg1/item/item.h"
    #include <stdbool.h>

    #define TAM 1000000

    typedef struct pilha PILHA;

    PILHA* pilha_criar(void);
    void pilha_apagar(PILHA** pilha);
    bool pilha_vazia(PILHA* pilha);
    bool pilha_cheia(PILHA* pilha);
    int pilha_tamanho(PILHA* pilha);
    ITEM* pilha_topo(PILHA* pilha);
    bool pilha_empilhar(PILHA* pilha, ITEM* item);
    ITEM* pilha_desempilhar(PILHA* pilha);

#endif