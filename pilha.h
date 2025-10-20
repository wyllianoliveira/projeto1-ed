#ifndef PILHA_H
#define PILHA_H

#include "forma.h"

/**
 * @file pilha.h
 * @brief Interface para pilhas utilizadas como carregadores dos disparadores.
 */

typedef void* Pilha;

/**
 * Cria uma pilha vazia.
 * @return Ponteiro para a pilha criada
 */
Pilha criaPilha();

/**
 * Insere uma forma no topo da pilha.
 * @param p Pilha
 * @param forma Forma a ser empilhada
 */
void empilha(Pilha p, Forma forma);

/**
 * Remove e retorna a forma do topo da pilha.
 * @param p Pilha
 * @return Forma removida ou NULL se a pilha estiver vazia
 */
Forma desempilha(Pilha p);

/**
 * Verifica se a pilha está vazia.
 * @param p Pilha
 * @return 1 se vazia, 0 caso contrário
 */
int pilhaVazia(Pilha p);

/**
 * Retorna o número de elementos na pilha.
 * @param p Pilha
 * @return Quantidade de formas empilhadas
 */
int tamanhoPilha(Pilha p);

/**
 * Libera toda a memória alocada pela pilha.
 * @param p Pilha
 */
void liberaPilha(Pilha p);

#endif