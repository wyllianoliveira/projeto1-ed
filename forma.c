#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "forma.h"

#define M_PI 3.141592653589793

typedef struct {
    int id;
    char tipo; // 'c', 'r', 'l', 't'
    double x, y;
    double w, h, r;
    char corb[30], corp[30];
    char cor[30];
    char ancora;
    char texto[100];
} FormaStruct;

Forma criaCirculo(int id, double x, double y, double r, const char* corb, const char* corp) {
    FormaStruct* f = malloc(sizeof(FormaStruct));
    f->id = id; f->tipo = 'c'; f->x = x; f->y = y; f->r = r;
    strcpy(f->corb, corb); strcpy(f->corp, corp);
    return f;
}

Forma criaRetangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp) {
    FormaStruct* f = malloc(sizeof(FormaStruct));
    f->id = id; f->tipo = 'r'; f->x = x; f->y = y; f->w = w; f->h = h;
    strcpy(f->corb, corb); strcpy(f->corp, corp);
    return f;
}

Forma criaLinha(int id, double x1, double y1, double x2, double y2, const char* cor) {
    FormaStruct* f = malloc(sizeof(FormaStruct));
    f->id = id; f->tipo = 'l'; f->x = x1; f->y = y1; f->w = x2; f->h = y2;
    strcpy(f->cor, cor);
    return f;
}

Forma criaTexto(int id, double x, double y, const char* corb, const char* corp, char ancora, const char* texto) {
    FormaStruct* f = malloc(sizeof(FormaStruct));
    f->id = id; f->tipo = 't'; f->x = x; f->y = y; f->ancora = ancora;
    strcpy(f->corb, corb); strcpy(f->corp, corp); strcpy(f->texto, texto);
    return f;
}

char getTipoForma(Forma f) { return ((FormaStruct*)f)->tipo; }
int getIdForma(Forma f) { return ((FormaStruct*)f)->id; }
double getX(Forma f) { return ((FormaStruct*)f)->x; }
double getY(Forma f) { return ((FormaStruct*)f)->y; }
double getRaio(Forma f) { return ((FormaStruct*)f)->r; }
double getLargura(Forma f) { return ((FormaStruct*)f)->w; }
double getAltura(Forma f) { return ((FormaStruct*)f)->h; }
const char* getCorBorda(Forma f) { return ((FormaStruct*)f)->corb; }
const char* getCorPreenchimento(Forma f) { return ((FormaStruct*)f)->corp; }
const char* getCorLinha(Forma f) { return ((FormaStruct*)f)->cor; }
char getAncora(Forma f) { return ((FormaStruct*)f)->ancora; }
const char* getTexto(Forma f) { return ((FormaStruct*)f)->texto; }

void trocaCorBorda(Forma f, const char* novaCor) {
    strcpy(((FormaStruct*)f)->corb, novaCor);
}

void trocaCorPreenchimento(Forma f, const char* novaCor) {
    strcpy(((FormaStruct*)f)->corp, novaCor);
}

void liberarForma(Forma f) {
    free(f);
}

double getArea(Forma f) {
    FormaStruct* fs = (FormaStruct*)f;
    switch (fs->tipo) {
        case 'c': return M_PI * fs->r * fs->r;
        case 'r': return fs->w * fs->h;
        case 'l': {
            double dx = fs->w - fs->x;
            double dy = fs->h - fs->y;
            return 2.0 * sqrt(dx * dx + dy * dy);
        }
        case 't': return 20.0 * strlen(fs->texto);
        default: return 0.0;
    }
}

Forma clonaForma(Forma f) {
    static int proximoId = 10000;
    FormaStruct* fs = (FormaStruct*)f;

    switch (fs->tipo) {
        case 'c':
            return criaCirculo(proximoId++, fs->x, fs->y, fs->r, fs->corp, fs->corb);
        case 'r':
            return criaRetangulo(proximoId++, fs->x, fs->y, fs->w, fs->h, fs->corp, fs->corb);
        case 'l':
            return criaLinha(proximoId++, fs->x, fs->y, fs->w, fs->h, fs->cor);
        case 't':
            return criaTexto(proximoId++, fs->x, fs->y, fs->corb, fs->corp, fs->ancora, fs->texto);
        default:
            return NULL;
    }
}

bool temSobreposicao(Forma f1, Forma f2) {
    if (!f1 || !f2) return false;

    FormaStruct* a = (FormaStruct*)f1;
    FormaStruct* b = (FormaStruct*)f2;

    double ax1, ax2, ay1, ay2;
    double bx1, bx2, by1, by2;

    switch (a->tipo) {
        case 'c':
            ax1 = a->x - a->r; ax2 = a->x + a->r;
            ay1 = a->y - a->r; ay2 = a->y + a->r;
            break;
        case 'r':
            ax1 = a->x; ax2 = a->x + a->w;
            ay1 = a->y; ay2 = a->y + a->h;
            break;
        case 'l':
            ax1 = fmin(a->x, a->w); ax2 = fmax(a->x, a->w);
            ay1 = fmin(a->y, a->h); ay2 = fmax(a->y, a->h);
            break;
        case 't': {
            int len = strlen(a->texto);
            if (a->ancora == 'i') {
                ax1 = a->x; ax2 = a->x + 10.0 * len;
            } else if (a->ancora == 'f') {
                ax1 = a->x - 10.0 * len; ax2 = a->x;
            } else {
                ax1 = a->x - 5.0 * len; ax2 = a->x + 5.0 * len;
            }
            ay1 = ay2 = a->y;
            break;
        }
        default: return false;
    }

    switch (b->tipo) {
        case 'c':
            bx1 = b->x - b->r; bx2 = b->x + b->r;
            by1 = b->y - b->r; by2 = b->y + b->r;
            break;
        case 'r':
            bx1 = b->x; bx2 = b->x + b->w;
            by1 = b->y; by2 = b->y + b->h;
            break;
        case 'l':
            bx1 = fmin(b->x, b->w); bx2 = fmax(b->x, b->w);
            by1 = fmin(b->y, b->h); by2 = fmax(b->y, b->h);
            break;
        case 't': {
            int len = strlen(b->texto);
            if (b->ancora == 'i') {
                bx1 = b->x; bx2 = b->x + 10.0 * len;
            } else if (b->ancora == 'f') {
                bx1 = b->x - 10.0 * len; bx2 = b->x;
            } else {
                bx1 = b->x - 5.0 * len; bx2 = b->x + 5.0 * len;
            }
            by1 = by2 = b->y;
            break;
        }
        default: return false;
    }

    return !(ax2 < bx1 || bx2 < ax1 || ay2 < by1 || by2 < ay1);
}