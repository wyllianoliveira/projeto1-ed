#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "forma.h"
#include "fila.h"
#include "pilha.h"
#include "disparador.h"
#include "svg.h"
#include "txt.h"
#include "chao.h"
#include "lista.h"

#define MAX_DISP 100
#define MAX_CARGA 100

static Disparador disparadores[MAX_DISP];
static Pilha carregadores[MAX_CARGA];

void processarQry(const char* caminhoQry, Fila chao, const char* svgSaida, const char* txtSaida) {
    FILE* qry = fopen(caminhoQry, "r");
    FILE* txt = fopen(txtSaida, "w");
    if (!qry || !txt) {
        printf("Erro ao abrir .qry ou .txt\n");
        return;
    }

    int totalInstr = 0, totalDisparos = 0, totalEsmagadas = 0, totalClonadas = 0;
    double pontuacao = 0.0;

    char linha[256];
    while (fgets(linha, 256, qry)) {
        totalInstr++;
        fprintf(txt, "[*] %s", linha);
        printf("Lendo linha: %s", linha);

        char* cmd = strtok(linha, " \r\n");
        if (!cmd) continue;

        if (strcmp(cmd, "pd") == 0) {
            int id; double x, y;
            sscanf(linha, "pd %d %lf %lf", &id, &x, &y);
            disparadores[id] = criaDisparador(id, x, y);
        }
        else if (strcmp(cmd, "lc") == 0) {
            int cid, n;
            sscanf(linha, "lc %d %d", &cid, &n);
            Pilha p = criaPilha();
            for (int i = 0; i < n && !filaVazia(chao); i++) {
                Forma f = desenfileira(chao);
                empilha(p, f);
                fprintf(txt, "Forma %d carregada\n", getIdForma(f));
            }
            carregadores[cid] = p;
        }
        else if (strcmp(cmd, "atch") == 0) {
            int d, esq, dir;
            sscanf(linha, "atch %d %d %d", &d, &esq, &dir);
            encaixaCarregadores(disparadores[d], carregadores[esq], carregadores[dir]);
        }
        else if (strcmp(cmd, "shft") == 0) {
            int d, n; char lado;
            sscanf(linha, "shft %d %c %d", &d, &lado, &n);
            for (int i = 0; i < n; i++) shft(disparadores[d], lado);
            Forma f = getDisparo(disparadores[d]);
            if (f) fprintf(txt, "Forma %d em posição de disparo\n", getIdForma(f));
        }
        else if (strcmp(cmd, "dsp") == 0) {
            int d; double dx, dy;
            sscanf(linha, "dsp %d %lf %lf", &d, &dx, &dy);
            Disparador disp = disparadores[d];
            Forma f = getDisparo(disp);
            if (f) {
                double x = getXDisparador(disp) + dx;
                double y = getYDisparador(disp) + dy;
                setDisparo(disp, NULL);
                static int proximoId = 10000;
                Forma novo = criaCirculo(proximoId++, x, y, getRaio(f), getCorBorda(f), getCorPreenchimento(f));
                insereFila(chao, novo);
                totalDisparos++;
                fprintf(txt, "Forma %d disparada para (%.2lf, %.2lf)\n", getIdForma(novo), x, y);
            }
        }
        else if (strcmp(cmd, "rjd") == 0) {
            int d; char lado;
            double dx, dy, ix, iy;
            sscanf(linha, "rjd %d %c %lf %lf %lf %lf", &d, &lado, &dx, &dy, &ix, &iy);
            Disparador disp = disparadores[d];
            Pilha carga = (lado == 'e') ? getCarregadorEsq(disp) : getCarregadorDir(disp);
            int disparos = tamanhoPilha(carga);
            for (int i = 0; i < disparos; i++) {
                shft(disp, lado);
                Forma f = getDisparo(disp);
                if (f) {
                    double x = getXDisparador(disp) + dx + i * ix;
                    double y = getYDisparador(disp) + dy + i * iy;
                    setDisparo(disp, NULL);
                    static int proximoId = 10000;
                    Forma novo = criaCirculo(proximoId++, x, y, getRaio(f), getCorBorda(f), getCorPreenchimento(f));
                    insereFila(chao, novo);
                    totalDisparos++;
                    fprintf(txt, "Forma %d disparada para (%.2lf, %.2lf)\n", getIdForma(novo), x, y);
                }
            }
        }
        else if (strcmp(cmd, "clr") == 0) {
            int d;
            sscanf(linha, "clr %d", &d);
            Disparador disp = disparadores[d];
            while (!pilhaVazia(getCarregadorEsq(disp))) desempilha(getCarregadorEsq(disp));
            while (!pilhaVazia(getCarregadorDir(disp))) desempilha(getCarregadorDir(disp));
            fprintf(txt, "Carregadores do disparador %d esvaziados\n", d);
        }
        else if (strcmp(cmd, "calc") == 0) {
            Lista arena = criaLista();
            while (!filaVazia(chao)) {
                insereLista(arena, desenfileira(chao));
            }

            int limite = tamanhoLista(arena);
            for (int i = 0; i < limite - 1; i++) {
                Forma f1 = getFormaLista(arena, i);
                Forma f2 = getFormaLista(arena, i + 1);

                if (temSobreposicao(f1, f2)) {
                    double a1 = getArea(f1);
                    double a2 = getArea(f2);

                    if (a1 < a2) {
                        pontuacao += a1;
                        totalEsmagadas++;
                        fprintf(txt, "Forma %d esmagada por %d\n", getIdForma(f1), getIdForma(f2));
                        removeFormaLista(arena, i);
                        i--;
                        limite--;
                    } else {
                        trocaCorBorda(f2, getCorPreenchimento(f1));
                        Forma clone = clonaForma(f1);
                        insereListaPos(arena, clone, i + 2);
                        totalClonadas++;
                        fprintf(txt, "Forma %d modificou borda de %d e foi clonada\n", getIdForma(f1), getIdForma(f2));
                    }
                }
            }

            fprintf(txt, "Pontuação final: %.2lf\n", pontuacao);
            escreveEstatisticasTXT(txt, totalInstr, totalDisparos, totalEsmagadas, totalClonadas, pontuacao);

            while (!listaVazia(arena)) {
                insereFila(chao, removeInicioLista(arena));
            }
            liberaLista(arena);
        }
    }

    Lista listaFinal = criaLista();
    while (!filaVazia(chao)) {
        insereLista(listaFinal, desenfileira(chao));
    }

    printf("SVG final será gerado com %d formas\n", tamanhoLista(listaFinal));
    gerarSVG(svgSaida, listaFinal);

    while (!listaVazia(listaFinal)) {
        insereFila(chao, removeInicioLista(listaFinal));
    }
    liberaLista(listaFinal);

    fclose(qry);
    fclose(txt);
}