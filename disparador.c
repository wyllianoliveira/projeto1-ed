#include <stdlib.h>
#include "disparador.h"

typedef struct {
    int id;
    double x, y;
    Pilha esq, dir;
    Forma disparo;
} DisparadorStruct;

Disparador criaDisparador(int id, double x, double y) {
    DisparadorStruct* d = malloc(sizeof(DisparadorStruct));
    d->id = id; d->x = x; d->y = y;
    d->esq = criaPilha();
    d->dir = criaPilha();
    d->disparo = NULL;
    return d;
}

void encaixaCarregadores(Disparador d, Pilha esq, Pilha dir) {
    DisparadorStruct* disp = (DisparadorStruct*)d;
    disp->esq = esq;
    disp->dir = dir;
}

void shft(Disparador d, char lado) {
    DisparadorStruct* disp = (DisparadorStruct*)d;
    if (lado == 'e' && !pilhaVazia(disp->esq))
        disp->disparo = desempilha(disp->esq);
    else if (lado == 'd' && !pilhaVazia(disp->dir))
        disp->disparo = desempilha(disp->dir);
}

Forma getDisparo(Disparador d) {
    return ((DisparadorStruct*)d)->disparo;
}

void setDisparo(Disparador d, Forma f) {
    ((DisparadorStruct*)d)->disparo = f;
}

double getXDisparador(Disparador d) {
    return ((DisparadorStruct*)d)->x;
}

double getYDisparador(Disparador d) {
    return ((DisparadorStruct*)d)->y;
}

Pilha getCarregadorEsq(Disparador d) {
    return ((DisparadorStruct*)d)->esq;
}

Pilha getCarregadorDir(Disparador d) {
    return ((DisparadorStruct*)d)->dir;
}

void liberaDisparador(Disparador d) {
    DisparadorStruct* disp = (DisparadorStruct*)d;
    liberaPilha(disp->esq);
    liberaPilha(disp->dir);
    free(disp);
}