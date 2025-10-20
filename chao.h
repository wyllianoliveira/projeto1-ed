#ifndef CHAO_H
#define CHAO_H

#include "forma.h"
#include "lista.h"

/**
 * @file chao.h
 * @brief Interface para gerenciamento do "Chao" que contém as formas.
 */

typedef void* Chao;

/**
 * Cria e inicializa um Chao.
 * @return Chao recém-criado, deve ser passado para liberaChao quando não for mais usado.
 */
Chao criaChao(void);

/**
 * Libera a memória associada ao Chao.
 * @param c Chao criado por criaChao
 */
void liberaChao(Chao c);

/**
 * Retorna a lista de formas armazenadas no Chao.
 * Observação: o chamador NÃO deve liberar a lista retornada; ela é propriedade do Chao.
 * Alterações na lista afetam o Chao.
 * @param c Chao
 * @return Ponteiro para Lista com as formas; pode ser NULL se não houver lista.
 */
Lista* getFormas(Chao c);

#endif