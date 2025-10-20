#ifndef QRY_H
#define QRY_H

#include "fila.h"
#include "chao.h"

/**
 * Processa os comandos do arquivo .qry
 * @param caminhoQry Caminho completo do arquivo .qry
 * @param chao Fila com as formas no chao
 * @param svgSaida Caminho completo do arquivo .svg gerado após o processamento
 * @param txtSaida Caminho completo do arquivo .txt com o relatório textual das operações
 */
void processarQry(const char* caminhoQry, Fila chao, const char* svgSaida, const char* txtSaida);

#endif