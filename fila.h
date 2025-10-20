#ifndef FILA_H
#define FILA_H

#include "forma.h"

/**
 * @file fila.h
 * @brief Interface para fila de formas disparadas na arena.
 */

typedef void* Fila;

/**
 * Cria uma fila vazia.
 * @return Fila recém-criada
 */
Fila criaFila();

/**
 * Insere uma forma no fim da fila.
 * @param f Fila
 * @param forma Forma a ser inserida
 */
void insereFila(Fila f, Forma forma);

/**
 * Remove e retorna a forma do início da fila.
 * @param f Fila
 * @return Forma removida ou NULL se a fila estiver vazia
 */
Forma desenfileira(Fila f);

/**
 * Verifica se a fila está vazia.
 * @param f Fila
 * @return 1 se vazia, 0 caso contrário
 */
int filaVazia(Fila f);

/**
 * Libera toda a memória alocada pela fila.
 * @param f Fila
 */
void liberaFila(Fila f);

#endif