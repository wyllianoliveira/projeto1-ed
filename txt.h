#ifndef TXT_H
#define TXT_H

#include <stdio.h>
#include "forma.h"

/**
 * @file txt.h
 * @brief Interface para geração de relatórios textuais (.txt) com dados das formas e estatísticas.
 */

/**
 * Escreve os dados de uma forma no arquivo .txt
 * @param txt Arquivo de saída
 * @param f Forma a ser registrada
 */
void escreveFormaTXT(FILE* txt, Forma f);

/**
 * Escreve estatísticas finais no arquivo .txt
 * @param txt Arquivo de saída
 * @param totalInstr Total de instruções executadas
 * @param totalDisparos Total de formas disparadas
 * @param totalEsmagadas Total de formas esmagadas
 * @param totalClonadas Total de formas clonadas
 * @param pontuacao Pontuação final calculada
 */
void escreveEstatisticasTXT(FILE* txt, int totalInstr, int totalDisparos, int totalEsmagadas, int totalClonadas, double pontuacao);

#endif