#include <stdlib.h>
#include "pilha.h"

typedef struct No {
    Forma forma;
    struct No* prox;
} No;

typedef struct {
    No* topo;
    int tamanho;
} PilhaStruct;

Pilha criaPilha() {
    PilhaStruct* p = malloc(sizeof(PilhaStruct));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

void empilha(Pilha p, Forma forma) {
    PilhaStruct* pilha = (PilhaStruct*)p;
    No* novo = malloc(sizeof(No));
    novo->forma = forma;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
}

Forma desempilha(Pilha p) {
    PilhaStruct* pilha = (PilhaStruct*)p;
    if (pilha->topo == NULL) return NULL;

    No* temp = pilha->topo;
    Forma f = temp->forma;
    pilha->topo = temp->prox;
    free(temp);
    pilha->tamanho--;
    return f;
}

int pilhaVazia(Pilha p) {
    return ((PilhaStruct*)p)->tamanho == 0;
}

int tamanhoPilha(Pilha p) {
    return ((PilhaStruct*)p)->tamanho;
}

void liberaPilha(Pilha p) {
    PilhaStruct* pilha = (PilhaStruct*)p;
    No* atual = pilha->topo;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(pilha);
}