#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "pilha.h"
#include "forma.h"

/**
 * @file disparador.h
 * @brief Interface para gerenciamento de disparadores e seus carregadores.
 */

typedef void* Disparador;

/**
 * Cria um novo disparador com ID e posição (x, y).
 */
Disparador criaDisparador(int id, double x, double y);

/**
 * Encaixa dois carregadores (esquerdo e direito) no disparador.
 */
void encaixaCarregadores(Disparador d, Pilha esq, Pilha dir);

/**
 * Move uma forma do carregador para a posição de disparo.
 * @param lado 'e' para esquerdo, 'd' para direito
 */
void shft(Disparador d, char lado);

/**
 * Retorna a forma atualmente posicionada para disparo.
 */
Forma getDisparo(Disparador d);

/**
 * Define a forma posicionada para disparo.
 */
void setDisparo(Disparador d, Forma f);

/**
 * Retorna a coordenada X do disparador.
 */
double getXDisparador(Disparador d);

/**
 * Retorna a coordenada Y do disparador.
 */
double getYDisparador(Disparador d);

/**
 * Retorna o carregador esquerdo do disparador.
 */
Pilha getCarregadorEsq(Disparador d);

/**
 * Retorna o carregador direito do disparador.
 */
Pilha getCarregadorDir(Disparador d);

/**
 * Libera a memória associada ao disparador.
 */
void liberaDisparador(Disparador d);

#endif