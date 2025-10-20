#include <stdlib.h>
#include "chao.h"
#include "lista.h"

typedef struct {
    Lista formas;
} ChaoStruct;

Chao criaChao() {
    ChaoStruct* c = malloc(sizeof(ChaoStruct));
    if (!c) return NULL;

    c->formas = criaLista();
    return c;
}

void liberaChao(Chao c) {
    ChaoStruct* ch = (ChaoStruct*)c;
    if (ch->formas) liberaLista(ch->formas);
    free(ch);
}

Lista* getFormas(Chao c) {
    ChaoStruct* ch = (ChaoStruct*)c;
    return &ch->formas;
}