#ifndef GEO_H
#define GEO_H

#include "chao.h"

/**
 * @file geo.h
 * @brief Interface para processamento do arquivo .geo, que define as formas iniciais no chão.
 */

/**
 * Processa os comandos do arquivo .geo e insere as formas no chão.
 * @param caminhoGeo Caminho completo do arquivo .geo
 * @param chao Estrutura que representa o chão onde as formas serão inseridas
 */
void processarGeo(const char* caminhoGeo, Chao chao);

#endif