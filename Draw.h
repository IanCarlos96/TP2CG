#include <stdio.h>
#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include "SOIL/SOIL.h"

#ifndef draw_h
#define draw_h

#define min_depth -5000
#define max_depth 5000
#define min_width -5000
#define max_width 5000
#define max_height 500
#define min_height -80

#define QUANT_SUBDIVISOES 20 

int texturaPlastico, texturaMadeira,texturaGrama, texturaMoinho;
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


float intensidadeFog;

void desenhaCenario();

void desenhaChao();

void desenhaCasa();

void desenhaArvore();
void desenhaLadrilho(ladrilho parede, int direcao);
void desenhaRetanguloSubdividido(int subdivisoes, int direcao);
GLint carregaTextura(const char* nomeDoArquivo);
void inicializaMateriaisParedes(void);
void desenhaCubo(void);
void defMaterialMadeira();
void defMaterialPlastico();
void desenhaCuboComTextura(GLint textureID);
void desenhaParedePorta();
void desenhaComodoTipo1();
void inicializaTextura();

/*Criar sólidos primitivos com textura*/
//Pensando em criar um arquivo só para isso
void solidSphere(int radius, int stacks, int columns);
void solidCilindro(GLdouble baseRadius, GLdouble topRadius,GLdouble height, GLint stacks, GLint columns);
void solidDisco(GLdouble innerRadius,GLdouble outerRadius, GLint stacks, GLint columns);
void solidPartialDisk(GLdouble innerRadius, GLdouble outerRadius,GLdouble startAngle,GLdouble sweepAngle);

//Com textura
void desenhaCilindro(GLint textura, GLdouble baseRadius, GLdouble topRadius,GLdouble height);
void desenhaEsfera(GLint textura, GLint raio);
void desenhaDisco(GLint textura, GLdouble innerRadius,GLdouble outerRadius);
void desenhaDiscoParcial(GLint textura, GLdouble innerRadius, GLdouble outerRadius,GLdouble startAngle,GLdouble sweepAngle);
void desenhaCone(GLint textura, GLdouble baseRadius, GLdouble height, GLint slices, GLint stacks);
//Sem Textura
void desenhaCilindroSemTXT(GLdouble baseRadius, GLdouble topRadius,GLdouble height);
void desenhaEsferaSemTXT(GLint raio);
void desenhaDiscoSemTXT(GLdouble innerRadius,GLdouble outerRadius);
void desenhaDiscoParcialSemTXT(GLdouble innerRadius, GLdouble outerRadius,GLdouble startAngle,GLdouble sweepAngle);


//Objeto do lado de fora
void desenhaArvore(void);
void desenhaMoinho(void);
//Objeto lado de dentro
void desenhaChuveiro();
void desenhaMesa(void);
//Neblina
void atualizaFog();
void inicializaFog();
#endif