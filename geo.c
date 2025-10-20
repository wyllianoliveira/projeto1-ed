#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "forma.h"
#include "lista.h"

void processarGeo(const char* caminhoGeo, Chao chao) {
    FILE* geo = fopen(caminhoGeo, "r");
    if (!geo) {
        fprintf(stderr, "Erro ao abrir arquivo .geo: %s\n", caminhoGeo);
        return;
    }

    Lista* formas = getFormas(chao); 

    char tipo;
    while (fscanf(geo, " %c", &tipo) == 1) {
        if (tipo == 'c') {
            int id; double x, y, r; char corb[30], corp[30];
            fscanf(geo, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
            Forma f = criaCirculo(id, x, y, r, corb, corp);
            insereLista(*getFormas(chao), f);
            if (f == NULL){
                printf("Erro ao criar forma do tipo %c\n", tipo);
            } else {
                 insereLista(*formas, f);
                printf("Forma %c criada e inserida\n", tipo);
            }

        } else if (tipo == 'r') {
            int id; double x, y, w, h; char corb[30], corp[30];
            fscanf(geo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            Forma f = criaRetangulo(id, x, y, w, h, corb, corp);
            insereLista(*getFormas(chao), f);
            if (f == NULL){
                printf("Erro ao criar forma do tipo %c\n", tipo);
            } else {
                 insereLista(*formas, f);
                printf("Forma %c criada e inserida\n", tipo);
            }

        } else if (tipo == 'l') {
            int id; double x1, y1, x2, y2; char cor[30];
            fscanf(geo, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);
            Forma f = criaLinha(id, x1, y1, x2, y2, cor);
            insereLista(*getFormas(chao), f);
            if (f == NULL){
                printf("Erro ao criar forma do tipo %c\n", tipo);
            } else {
                 insereLista(*formas, f);
                printf("Forma %c criada e inserida\n", tipo);
            }

        } else if (tipo == 't') {
            int id; double x, y; char corb[30], corp[30], ancora; char texto[200];
            fscanf(geo, "%d %lf %lf %s %s %c", &id, &x, &y, corb, corp, &ancora);
            fgets(texto, sizeof(texto), geo);
            texto[strcspn(texto, "\n")] = '\0';
            Forma f = criaTexto(id, x, y, corb, corp, ancora, texto);
            insereLista(*getFormas(chao), f);
            if (f == NULL){
                printf("Erro ao criar forma do tipo %c\n", tipo);
            } else {
                 insereLista(*formas, f);
                printf("Forma %c criada e inserida\n", tipo);
            }

        } else {
            char linha[256];
            fgets(linha, sizeof(linha), geo); 
        }
    }

    printf("Total de formas inseridas: %d\n", tamanhoLista(*formas));
    fclose(geo);
}