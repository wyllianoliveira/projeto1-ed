#include <stdlib.h>
#include <stdbool.h>
#include "forma.h"
#include "fila.h"

typedef struct No {
    Forma forma;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
} FilaStruct;

Fila criaFila() {
    FilaStruct* f = malloc(sizeof(FilaStruct));
    f->inicio = f->fim = NULL;
    return f;
}

void insereFila(Fila f, Forma forma) {
    FilaStruct* fila = (FilaStruct*)f;
    No* novo = malloc(sizeof(No));
    novo->forma = forma;
    novo->prox = NULL;

    if (fila->fim == NULL) {
        fila->inicio = fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

Forma desenfileira(Fila f) {
    FilaStruct* fila = (FilaStruct*)f;
    if (fila->inicio == NULL) return NULL;

    No* temp = fila->inicio;
    Forma forma = temp->forma;
    fila->inicio = temp->prox;
    if (fila->inicio == NULL)
        fila->fim = NULL;
    free(temp);
    return forma;
}

int filaVazia(Fila f) {
    return ((FilaStruct*)f)->inicio == NULL;
}

void liberaFila(Fila f) {
    FilaStruct* fila = (FilaStruct*)f;
    No* atual = fila->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(fila);
}