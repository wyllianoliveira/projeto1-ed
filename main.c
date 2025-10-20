#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "forma.h"
#include "pilha.h"
#include "disparador.h"
#include "qry.h"
#include "svg.h"
#include "txt.h"
#include "lista.h"
#include "chao.h"
#include "geo.h"

int main(int argc, char* argv[]) {
    char dirEntrada[256] = ".", dirSaida[256] = ".", arqGeo[100] = "", arqQry[100] = "";
    int temQry = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) strcpy(dirEntrada, argv[++i]);
        else if (!strcmp(argv[i], "-f")) strcpy(arqGeo, argv[++i]);
        else if (!strcmp(argv[i], "-q")) { strcpy(arqQry, argv[++i]); temQry = 1; }
        else if (!strcmp(argv[i], "-o")) strcpy(dirSaida, argv[++i]);
    }

    mkdir(dirSaida);

    char nomeBase[100];
    strcpy(nomeBase, arqGeo);
    char* ponto = strrchr(nomeBase, '.');
    if (ponto) *ponto = '\0';

    char caminhoGeo[300], caminhoQry[300];
    sprintf(caminhoGeo, "%s/%s", dirEntrada, arqGeo);
    if (temQry) sprintf(caminhoQry, "%s/%s", dirEntrada, arqQry);

    Chao chao = criaChao();

    processarGeo(caminhoGeo, chao);

    int total = tamanhoLista(*getFormas(chao));
    printf("Formas carregadas: %d\n", total);

    char saidaGeo[300];
    sprintf(saidaGeo, "%s/%s.svg", dirSaida, nomeBase);
    gerarSVG(saidaGeo, *getFormas(chao));

    if (temQry) {
        char saidaSvgFinal[300], saidaTxtFinal[300];

     
        char* nomeQry = strrchr(arqQry, '/');
        if (nomeQry) nomeQry++;
        else nomeQry = arqQry;

        sprintf(saidaSvgFinal, "%s/%s-%s.svg", dirSaida, nomeBase, nomeQry);
        sprintf(saidaTxtFinal, "%s/%s-%s.txt", dirSaida, nomeBase, nomeQry);

        processarQry(caminhoQry, *getFormas(chao), saidaSvgFinal, saidaTxtFinal);
    }

    liberaChao(chao);
    return 0;
}