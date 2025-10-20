#include <stdlib.h>
#include "lista.h"

typedef struct No {
    Forma forma;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    int tamanho;
} ListaStruct;

Lista criaLista() {
    ListaStruct* l = malloc(sizeof(ListaStruct));
    l->inicio = NULL;
    l->tamanho = 0;
    return (Lista)l; // garante compatibilidade
}

void insereLista(Lista l, Forma f) {
    if (!l) return;
    ListaStruct* lista = (ListaStruct*)l;
    No* novo = malloc(sizeof(No));
    novo->forma = f;
    novo->prox = NULL;

    if (!lista->inicio) {
        lista->inicio = novo;
    } else {
        No* atual = lista->inicio;
        while (atual->prox)
            atual = atual->prox;
        atual->prox = novo;
    }
    lista->tamanho++;
}

void insereListaPos(Lista l, Forma f, int pos) {
    if (!l) return;
    ListaStruct* lista = (ListaStruct*)l;
    No* novo = malloc(sizeof(No));
    novo->forma = f;

    if (pos <= 0 || !lista->inicio) {
        novo->prox = lista->inicio;
        lista->inicio = novo;
    } else {
        No* atual = lista->inicio;
        int i = 0;
        while (atual->prox && i < pos - 1) {
            atual = atual->prox;
            i++;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
    lista->tamanho++;
}

Forma getFormaLista(Lista l, int i) {
    if (!l) return NULL;
    ListaStruct* lista = (ListaStruct*)l;
    if (i < 0 || i >= lista->tamanho) return NULL;

    No* atual = lista->inicio;
    for (int j = 0; j < i; j++)
        atual = atual->prox;

    return atual->forma;
}

void removeFormaLista(Lista l, int i) {
    if (!l) return;
    ListaStruct* lista = (ListaStruct*)l;
    if (i < 0 || i >= lista->tamanho) return;

    No* atual = lista->inicio;
    if (i == 0) {
        lista->inicio = atual->prox;
        free(atual);
    } else {
        for (int j = 0; j < i - 1; j++)
            atual = atual->prox;
        No* temp = atual->prox;
        atual->prox = temp->prox;
        free(temp);
    }
    lista->tamanho--;
}

Forma removeInicioLista(Lista l) {
    if (!l) return NULL;
    ListaStruct* lista = (ListaStruct*)l;
    if (!lista->inicio) return NULL;

    No* temp = lista->inicio;
    Forma f = temp->forma;
    lista->inicio = temp->prox;
    free(temp);
    lista->tamanho--;
    return f;
}

int tamanhoLista(Lista l) {
    if (!l) return 0;
    return ((ListaStruct*)l)->tamanho;
}

bool listaVazia(Lista l) {
    return tamanhoLista(l) == 0;
}

void liberaLista(Lista l) {
    if (!l) return;
    ListaStruct* lista = (ListaStruct*)l;
    No* atual = lista->inicio;
    while (atual) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}