#include <stdio.h>
#include "txt.h"
#include "forma.h"

void escreveFormaTXT(FILE* txt, Forma f) {
    char tipo = getTipoForma(f);
    fprintf(txt, "ID: %d | Tipo: %c | Pos: (%.2lf, %.2lf) | Área: %.2lf\n",
        getIdForma(f), tipo, getX(f), getY(f), getArea(f));
}

void escreveEstatisticasTXT(FILE* txt, int totalInstr, int totalDisparos, int totalEsmagadas, int totalClonadas, double pontuacao) {
    fprintf(txt, "\n--- Estatísticas Finais ---\n");
    fprintf(txt, "Instruções executadas: %d\n", totalInstr);
    fprintf(txt, "Disparos realizados: %d\n", totalDisparos);
    fprintf(txt, "Formas esmagadas: %d\n", totalEsmagadas);
    fprintf(txt, "Formas clonadas: %d\n", totalClonadas);
    fprintf(txt, "Pontuação total: %.2lf\n", pontuacao);
}