#include <stdio.h>
#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include "SOIL/SOIL.h"

#ifndef draw_h
#define draw_h

#define min_depth -500
#define max_depth 500
#define min_width -500
#define max_width 500
#define max_height 500
#define min_height -1

#define QUANT_SUBDIVISOES 20 

typedef struct coords {
  union {
      float v[4];
      struct {
          float x, y, z, w;
      };
      struct {
          float r, g, b, a;
      };
  };
} ponto, vetor, cor;

typedef struct {
    float largura, altura, espessura;
} dimensoes;

typedef struct material {
    cor ambiente;
    cor emissiva;
    cor difusa;
    cor especular;
    float brilhosidade[1];
} material;

typedef struct ladrilho {
    ponto posicao;
    dimensoes dim;
    material mat;
    int textura;
} ladrilho;

void desenhaCenario();

void desenhaChao();

void desenhaCasa();

void desenhaLadrilho(ladrilho parede, int direcao);
void desenhaRetanguloSubdividido(int subdivisoes, int direcao);
void carregaTextura(int *textura, char* nomeDoArquivo);
void inicializaMateriaisParedes(void);
void desenhaCubo(void);
void defMaterialMadeira();
void defMaterialPlastico();
void desenhaCuboComTextura(GLint textureID);
void desenhaParedePorta();
#endif