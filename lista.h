#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "forma.h"

/**
 * @file lista.h
 * @brief Interface para lista de formas geométricas.
 */

typedef void* Lista;

/**
 * Cria uma lista vazia.
 * @return Lista recém-criada
 */
Lista criaLista();

/**
 * Insere uma forma no fim da lista.
 * @param l Lista
 * @param f Forma a ser inserida
 */
void insereLista(Lista l, Forma f);

/**
 * Insere uma forma na posição especificada.
 * @param l Lista
 * @param f Forma a ser inserida
 * @param pos Posição (0-based)
 */
void insereListaPos(Lista l, Forma f, int pos);

/**
 * Retorna a forma na posição i.
 * @param l Lista
 * @param i Índice da forma
 * @return Forma na posição i
 */
Forma getFormaLista(Lista l, int i);

/**
 * Remove a forma da posição i.
 * @param l Lista
 * @param i Índice da forma a ser removida
 */
void removeFormaLista(Lista l, int i);

/**
 * Remove e retorna a forma do início da lista.
 * @param l Lista
 * @return Forma removida
 */
Forma removeInicioLista(Lista l);

/**
 * Retorna o número de formas na lista.
 * @param l Lista
 * @return Tamanho da lista
 */
int tamanhoLista(Lista l);

/**
 * Verifica se a lista está vazia.
 * @param l Lista
 * @return true se vazia, false caso contrário
 */
bool listaVazia(Lista l);

/**
 * Libera toda a memória alocada pela lista.
 * @param l Lista
 */
void liberaLista(Lista l);

#endif