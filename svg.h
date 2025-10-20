#ifndef SVG_H
#define SVG_H

#include "fila.h"

/**
 * @file svg.h
 * @brief Interface para geração de arquivos SVG com formas geométricas.
 */

/**
 * Gera um arquivo SVG com as formas contidas na fila.
 * @param caminho Caminho completo do arquivo de saída
 * @param f Fila contendo as formas a serem desenhadas
 */
void gerarSVG(const char* caminho, Fila f);

#endif