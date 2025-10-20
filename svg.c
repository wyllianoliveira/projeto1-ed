#include <string.h>
#include <stdio.h>
#include "forma.h"
#include "lista.h"

void gerarSVG(const char* caminho, Lista formas) {
    FILE* svg = fopen(caminho, "w");
    if (!svg) {
        fprintf(stderr, "Erro ao criar arquivo SVG: %s\n", caminho);
        return;
    }

    fprintf(svg, "<svg xmlns='http://www.w3.org/2000/svg'>\n");

    int total = tamanhoLista(formas);
    printf("Gerando SVG com %d formas...\n", total);

    for (int i = 0; i < total; i++) {
        Forma f = getFormaLista(formas, i);
        if (!f) {
            fprintf(stderr, "Forma nula na posição %d\n", i);
            continue;
        }

        char tipo = getTipoForma(f);
        if (tipo == 'c') {
            double x = getX(f);
            double y = getY(f);
            double r = getRaio(f);
            const char* borda = getCorBorda(f);
            const char* preench = getCorPreenchimento(f);

            fprintf(svg,
                "<circle cx='%.2lf' cy='%.2lf' r='%.2lf' stroke='%s' fill='%s'/>\n",
                x, y, r, borda, preench);
        }
        else if (tipo == 'r') {
            double x = getX(f);
            double y = getY(f);
            double w = getLargura(f);
            double h = getAltura(f);
            const char* borda = getCorBorda(f);
            const char* preench = getCorPreenchimento(f);

            fprintf(svg,
                "<rect x='%.2lf' y='%.2lf' width='%.2lf' height='%.2lf' stroke='%s' fill='%s'/>\n",
                x, y, w, h, borda, preench);
        }
        else {
            fprintf(stderr, "Tipo de forma desconhecido: %c\n", tipo);
        }
    }

    fprintf(svg, "</svg>\n");
    fclose(svg);
}