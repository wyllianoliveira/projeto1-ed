  #include <stdbool.h>
  #include <stddef.h>
  #ifndef FORMA_H
  #define FORMA_H



  /**
  * Módulo: forma
  * Responsável pela criação, manipulação e consulta de formas geométricas.
  * Tipos suportados: círculo, retângulo, linha e texto.
  */
  typedef void* Forma;

  /**
    * Criar um círculo.
    * @param id Identificador único
    * @param x Coordenada x do centro
    * @param y Coordenada y do cenrto
    * @param r Raio
    * @param corb Cor da borda
    * @param corp cor do preenchimento
    * @return Ponteiro para a forma criada
    */
  Forma criaCirculo(int id, double x, double y, double r, const char* corb, const char* corp);

  /**
    * Cria um retângulo.
    * @param id Identificador único
    * @param x Coordenada x do canto inferior esquerdo
    * @param y Coordenada y do canto inferior esquerdo
    * @param w Largura
    * @param h Altura
    * @param corb Cor da borda
    * @param corp Cor do preenchimeto
    * @return Ponteiro para a forma criada
    */
  Forma criaRetangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp);

  /**
    * Cria uma linha.
    * @param id Identificador único
    * @param x1 Coordenada x da extremidade inicial
    * @param y1 Coordenada y da extremidade inicial
    * @param x2 Coordenada x da extremidade final
    * @param y2 Coordenada y da extremidade final
    * @param cor Cor da linha
    * @return Ponteiro para a forma criada
    */
  Forma criaLinha(int id, double x1, double y1, double x2, double y2, const char* cor);

    /**
    * Criar um texto.
    * @param id Identificador único
    * @param x Coordenada x da âncora
    * @param y Coordenada y da âncora
    * @param corb Cor da borda
    * @param corp cor do preenchimento
    * @param a Posição da âncora ('i', 'm', 'f')
    * @param texto Conteúdo textual
    * @return Ponteiro para a forma criada
    */
  Forma criaTexto(int id, double x, double y, const char* corb, const char* corp, char ancora, const char* texto);

  // Funções de acesso aos dados da forma

  /**
    * Retorna o tipo da forma ('c', 'r', 'l', 't')
    */
  char getTipoForma(Forma f);

    /**
    * Retorna o identificador da forma
    */
  int getIdForma(Forma f);

  double getX(Forma f);
  double getY(Forma f);
  double getArea(Forma f);
  double getRaio(Forma f);
  double getLargura(Forma f);
  double getAltura(Forma f);
  const char* getCorBorda(Forma f);
  const char* getCorPreenchimento(Forma f);
  const char* getCorLinha(Forma f);
  char getAncora(Forma f);
  const char* getTexto(Forma f);

  void trocaCorBorda(Forma f, const char* novaCor);

  double getArea(Forma f);
  bool temSobreposicao(Forma f1, Forma f2);
  Forma clonaForma(Forma f);

  void liberarForma(Forma f);

  #endif