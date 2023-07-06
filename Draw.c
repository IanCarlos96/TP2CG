#include "Draw.h"
#include "Cams.c"
// #include "Lights.c"

material plasticoAzul, marromFosco;
ladrilho ladrilhos[4];
ponto posicaoDaLuz;

void configuraProjecao()
{
  float razaoAspecto = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Conferir os valores daqui depois
  // glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
  // glFrustum(min_width, max_width, min_height, max_height, min_depth, max_depth);
  //glOrtho(min_width, max_width, min_height, max_height, min_depth, max_depth);
  gluPerspective(45.0f, razaoAspecto, -2, 300);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void desenhaChao()
{

  // Tem só o retângulo aqui. Ainda precisa setar o material, textura, etc
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3f(min_width, min_height, min_depth);
  glVertex3f(min_width, min_height, max_depth);
  glVertex3f(max_width, min_height, max_depth);
  glVertex3f(max_width, min_height, min_depth);
  glEnd();
}

void desenhaCasa()
{

  //Parede 1
  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef(0.0f, 0.0f, 0.0f);
  glScalef(97.0, 97.0, 6.0);
  defMaterialPlastico();
  desenhaCubo();
  glPopMatrix();

  //Parece2
  glPushMatrix();
  defMaterialMadeira();
  glColor3f(0.2, 0.7, 0);
  glTranslatef(100.0f, 0.0f, 100.0f);
  desenhaParedePorta();
  glPopMatrix();

  //Parede3
  glPushMatrix();
  glColor3f(0.2, 0.7, 0);
  glTranslatef(0.0f, 0.0f, 200.0f);
  glScalef(97.0, 97.0, 6.0);
  defMaterialMadeira();
  desenhaCubo();
  glPopMatrix();

  glPushMatrix();
  defMaterialMadeira();
  glColor3f(0.2, 0.7, 0);
  glTranslatef(-100.0f, 0.0f, 100.0f);
  desenhaParedePorta();
  glPopMatrix();

  glPushMatrix();
  defMaterialMadeira();
  glColor3f(0.2, 0.7, 0);
  glTranslatef(-100.0f, 0.0f, 100.0f);
  desenhaArvore();
  glPopMatrix();

  // piso geral
  glColor3f(0, 0, 0);
  glBegin(GL_QUADS);
  glVertex3f(0, 0, 0);
  glVertex3f(300, 0, 0);
  glVertex3f(300, 0, 300);
  glVertex3f(0, 0, 300);
  glEnd();
}

void desenhaCenario()
{
  configuraProjecao();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  camera.x = raioVisao * sin(phi) * cos(teta);  //coordenada x denotada em coordenadas esféricas
  camera.z = raioVisao * sin(phi) * sin(teta); //coordenada z denotada em coordenadas esféricas
  camera.y = raioVisao * cos(phi);          //coordenada y denotada em coordenadas esféricas

  glLoadIdentity();
  //gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
  gluLookAt( xCursor+0, yCursor, zCursor+0, xCursor+camera.x, camera.y, zCursor+camera.z, 0, 1, 0); 

  desenhaChao();

  desenhaCasa();

  glutSwapBuffers();
}

/// Desenha um retângulo que está subdivido em retângulos menores em uma
/// quantidade igual a "subdivisoes" tanto no eixo x, quanto no eixo y.
/// Portanto, o número total de subretângulos é de (subdivisoes^2) e de
/// triângulos é de (subdivisoes^2 * 2).
///
/// O retângulo desenhado é um quadrado com lado igual a 1, centrado na origem.
///
/// Se for chamada com subdivisoes=1, o retângulo é desenhado tendo apenas
/// 1 subretângulo que representa o retângulo inteiro (i.e., 2 triângulos,
/// 4 vértices).
void desenhaRetanguloSubdividido(int subdivisoes, int direcao)
{
  int i, j;
  float alturaDoSubTriangulo = 1.0f / (subdivisoes);
  float larguraDoSubTriangulo = 1.0f / (subdivisoes);
  glPolygonMode(GL_FRONT, GL_FILL);
  glPushMatrix();
  glTranslatef(0, 0, 0);
  // desenha uma quantidade de tiras de triângulos (TRIANGLE_STRIP) igual
  // a "subdivisoes". Por exemplo, para subdivisoes=3:
  //  ___ ___ ___
  // |  /|  /|  /|  - esta é a terceira tira
  // |/__|/__|/__|
  // |  /|  /|  /|  - esta é a segunda tira
  // |/__|/__|/__|
  // |  /|  /|  /|  - esta é a primeira tira
  // |/__|/__|/__|
  for (i = 0; i < subdivisoes; i++)
  {
    glBegin(GL_TRIANGLE_STRIP);
    // define o vetor normal do ladrilho

    glNormal3f(0, 0, 1);
    float yVerticesLinhaDeBaixo = alturaDoSubTriangulo * (i);
    float yVerticesLinhaDeCima = yVerticesLinhaDeBaixo + alturaDoSubTriangulo;

    // veja uma tira de triângulos com subdivisoes=3:
    //
    // v0     v2     v4     v6
    // |    / |    / |    / |
    // |  /   |  /   |  /   |
    // v1     v3     v5     v7
    for (j = 0; j < subdivisoes + 1; j++)
    {
      if (direcao == 0)
      {
        float xVertice = larguraDoSubTriangulo * j;
        glTexCoord2f(xVertice, yVerticesLinhaDeCima);
        glVertex2f(xVertice, yVerticesLinhaDeCima);
        glTexCoord2f(xVertice, yVerticesLinhaDeBaixo);
        glVertex2f(xVertice, yVerticesLinhaDeBaixo);
      }
      else
      {

        float xVertice = larguraDoSubTriangulo * j;

        glTexCoord2f(xVertice, yVerticesLinhaDeBaixo);
        glVertex2f(xVertice, yVerticesLinhaDeBaixo);
        glTexCoord2f(xVertice, yVerticesLinhaDeCima);
        glVertex2f(xVertice, yVerticesLinhaDeCima);
      }
    }
    glEnd();
  }
  glPopMatrix();
}

void desenhaLadrilho(ladrilho l, int direcao)
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, l.mat.ambiente.v);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, l.mat.difusa.v);
  glMaterialfv(GL_FRONT, GL_SPECULAR, l.mat.especular.v);
  glMaterialfv(GL_FRONT, GL_SHININESS, l.mat.brilhosidade);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, l.textura);
  glPushMatrix();
  glTranslatef(l.posicao.x, l.posicao.y, l.posicao.z);
  if (l.dim.espessura == 10)
    glScalef(l.dim.largura, l.dim.altura, 1.0);
  else if (l.dim.largura == 10)
    glScalef(1.0, l.dim.altura, l.dim.espessura);
  desenhaRetanguloSubdividido(QUANT_SUBDIVISOES, direcao);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void inicializaMateriaisParedes(void)
{
  // glEnable(GL_LIGHTING);//Estava comentado no exemplo, não sei o pq
  plasticoAzul.ambiente = (cor){0.25, 0.25, 0.25, 1};
  plasticoAzul.emissiva = (cor){0, 0, 0, 1};
  plasticoAzul.difusa = (cor){0.1, 0.1, 0.4, 1};
  plasticoAzul.especular = (cor){1, 1, 1, 1};
  plasticoAzul.brilhosidade[0] = 100;

  marromFosco.ambiente = (cor){0.1, 0.1, 0.1, 1};
  marromFosco.emissiva = (cor){0, 0, 0, 1};
  marromFosco.difusa = (cor){.49, .22, .02, 1};
  marromFosco.especular = (cor){0, 0, 0, 1};
  marromFosco.brilhosidade[0] = 0;
}

void inicializaTexturas(){

  //texturaPlastico = carregaTextura("plastico.jpg");
  //texturaMadeira = carregaTextura("madeira.jpg");
  texturaPlastico = carregaTextura("a.png");
  texturaMadeira = carregaTextura("b.png");
  

}

GLint carregaTextura(const char *arquivo)
{
    GLuint idTextura = SOIL_load_OGL_texture(
        arquivo,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y);

    if (idTextura == 0)
    {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}

/// TODO: quando for enviar apagar a função abaixo deixei só como exemplo de configurar iluminação
void configuraIluminacao()
{
  // glEnable(GL_LIGHTING);

  posicaoDaLuz = (ponto){0, 0, -1, 1};
  cor corDaLuz = {1.0, 1.0, 1.0, 1.0};
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);

  glLightfv(GL_LIGHT0, GL_POSITION, posicaoDaLuz.v);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, corDaLuz.v);
  glLightfv(GL_LIGHT0, GL_SPECULAR, corDaLuz.v);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

// Desenha uma esfera na origem, com certo raio e subdivisões
// latitudinais e longitudinais
//
// Não podemos usar glutSolidSphere, porque ela não chama
// glTexCoord para os vértices. Logo, se você quer texturizar
// uma esfera, não pode usar glutSolidSphere
void solidSphere(int radius, int stacks, int columns)
{
  // cria uma quádrica
  GLUquadric *quadObj = gluNewQuadric();
  // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
  // ou GLU_POINT
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  // chama 01 glNormal para cada vértice.. poderia ser
  // GLU_FLAT (01 por face) ou GLU_NONE
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  // chama 01 glTexCoord por vértice
  gluQuadricTexture(quadObj, GL_TRUE);
  // cria os vértices de uma esfera
  gluSphere(quadObj, radius, stacks, columns);
  // limpa as variáveis que a GLU usou para criar
  // a esfera
  gluDeleteQuadric(quadObj);
}
void solidCilindro(int radius, int stacks, int columns)
{
  // cria uma quádrica
  GLUquadric *quadObj = gluNewQuadric();
  // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
  // ou GLU_POINT
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  // chama 01 glNormal para cada vértice.. poderia ser
  // GLU_FLAT (01 por face) ou GLU_NONE
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  // chama 01 glTexCoord por vértice
  gluQuadricTexture(quadObj, GL_TRUE);
  // cria os vértices de uma esfera
  gluSphere(quadObj, radius, stacks, columns);
  // limpa as variáveis que a GLU usou para criar
  // a esfera
  gluDeleteQuadric(quadObj);
}
void desenhaEsfera(int textura, int raio)
{

  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textura);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glPolygonMode(GL_FRONT, GL_FILL);
  solidSphere(raio, 50, 50);
  glDisable(GL_TEXTURE_2D);
}
void desenhaCubo()
{
  GLfloat verticesCubo[] = {
      1, 1, 1, -1, 1, 1, -1, -1, 1, // v0-v1-v2 (frente)
      -1, -1, 1, 1, -1, 1, 1, 1, 1, // v2-v3-v0

      1, 1, 1, 1, -1, 1, 1, -1, -1, // v0-v3-v4 (direita)
      1, -1, -1, 1, 1, -1, 1, 1, 1, // v4-v5-v0

      1, 1, 1, 1, 1, -1, -1, 1, -1, // v0-v5-v6 (cima)
      -1, 1, -1, -1, 1, 1, 1, 1, 1, // v6-v1-v0

      -1, 1, 1, -1, 1, -1, -1, -1, -1, // v1-v6-v7 (esquerda)
      -1, -1, -1, -1, -1, 1, -1, 1, 1, // v7-v2-v1

      -1, -1, -1, 1, -1, -1, 1, -1, 1, // v7-v4-v3 (baixo)
      1, -1, 1, -1, -1, 1, -1, -1, -1, // v3-v2-v7

      1, -1, -1, -1, -1, -1, -1, 1, -1, // v4-v7-v6 (trás)
      -1, 1, -1, 1, 1, -1, 1, -1, -1    // v6-v5-v4
  };

  // array com as normais de cada vértice
  GLfloat normaisCubo[] = {
      0, 0, 1, 0, 0, 1, 0, 0, 1, // v0-v1-v2 (frente)
      0, 0, 1, 0, 0, 1, 0, 0, 1, // v2-v3-v0

      1, 0, 0, 1, 0, 0, 1, 0, 0, // v0-v3-v4 (direita)
      1, 0, 0, 1, 0, 0, 1, 0, 0, // v4-v5-v0

      0, 1, 0, 0, 1, 0, 0, 1, 0, // v0-v5-v6 (cima)
      0, 1, 0, 0, 1, 0, 0, 1, 0, // v6-v1-v0

      -1, 0, 0, -1, 0, 0, -1, 0, 0, // v1-v6-v7 (esquerda)
      -1, 0, 0, -1, 0, 0, -1, 0, 0, // v7-v2-v1

      0, -1, 0, 0, -1, 0, 0, -1, 0, // v7-v4-v3 (baixo)
      0, -1, 0, 0, -1, 0, 0, -1, 0, // v3-v2-v7

      0, 0, -1, 0, 0, -1, 0, 0, -1, // v4-v7-v6 (trás)
      0, 0, -1, 0, 0, -1, 0, 0, -1  // v6-v5-v4
  };
  // o cubo tem 36 vértices definidos.
  // cada vértice tem x,y,z, logo, são 108 valores (36 x 3)
  // NUM_VALORES = 108
  const int NUM_VALORES = sizeof(verticesCubo) / sizeof(GLfloat);

  glBegin(GL_TRIANGLES);
  int c;
  for (c = 0; c < NUM_VALORES; c += 3)
  {
    glNormal3f(normaisCubo[c], normaisCubo[c + 1], normaisCubo[c + 2]);
    glVertex3f(verticesCubo[c], verticesCubo[c + 1], verticesCubo[c + 2]);
  }
  glEnd();
}
void defMaterialPlastico()
{
  material materialUtilizado = (plasticoAzul);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialUtilizado.ambiente.v);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialUtilizado.difusa.v);
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialUtilizado.especular.v);
  glMaterialfv(GL_FRONT, GL_SHININESS, materialUtilizado.brilhosidade);
}
void defMaterialMadeira()
{
  material materialUtilizado = (marromFosco);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialUtilizado.ambiente.v);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialUtilizado.difusa.v);
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialUtilizado.especular.v);
  glMaterialfv(GL_FRONT, GL_SHININESS, materialUtilizado.brilhosidade);
}
//Ainda não funciona
void desenhaCuboComTextura(GLint textureID)
{

  GLfloat verticesCubo[] = {
      1, 1, 1, -1, 1, 1, -1, -1, 1, // v0-v1-v2 (frente)
      -1, -1, 1, 1, -1, 1, 1, 1, 1, // v2-v3-v0

      1, 1, 1, 1, -1, 1, 1, -1, -1, // v0-v3-v4 (direita)
      1, -1, -1, 1, 1, -1, 1, 1, 1, // v4-v5-v0

      1, 1, 1, 1, 1, -1, -1, 1, -1, // v0-v5-v6 (cima)
      -1, 1, -1, -1, 1, 1, 1, 1, 1, // v6-v1-v0

      -1, 1, 1, -1, 1, -1, -1, -1, -1, // v1-v6-v7 (esquerda)
      -1, -1, -1, -1, -1, 1, -1, 1, 1, // v7-v2-v1

      -1, -1, -1, 1, -1, -1, 1, -1, 1, // v7-v4-v3 (baixo)
      1, -1, 1, -1, -1, 1, -1, -1, -1, // v3-v2-v7

      1, -1, -1, -1, -1, -1, -1, 1, -1, // v4-v7-v6 (trás)
      -1, 1, -1, 1, 1, -1, 1, -1, -1    // v6-v5-v4
  };

  // array com as normais de cada vértice
  GLfloat normaisCubo[] = {
      0, 0, 1, 0, 0, 1, 0, 0, 1, // v0-v1-v2 (frente)
      0, 0, 1, 0, 0, 1, 0, 0, 1, // v2-v3-v0

      1, 0, 0, 1, 0, 0, 1, 0, 0, // v0-v3-v4 (direita)
      1, 0, 0, 1, 0, 0, 1, 0, 0, // v4-v5-v0

      0, 1, 0, 0, 1, 0, 0, 1, 0, // v0-v5-v6 (cima)
      0, 1, 0, 0, 1, 0, 0, 1, 0, // v6-v1-v0

      -1, 0, 0, -1, 0, 0, -1, 0, 0, // v1-v6-v7 (esquerda)
      -1, 0, 0, -1, 0, 0, -1, 0, 0, // v7-v2-v1

      0, -1, 0, 0, -1, 0, 0, -1, 0, // v7-v4-v3 (baixo)
      0, -1, 0, 0, -1, 0, 0, -1, 0, // v3-v2-v7

      0, 0, -1, 0, 0, -1, 0, 0, -1, // v4-v7-v6 (trás)
      0, 0, -1, 0, 0, -1, 0, 0, -1  // v6-v5-v4
  };

  GLfloat texCoords[] = {
      1, 1, 0, 1, 0, 0, // v0-v1-v2 (frente)
      0, 0, 1, 0, 1, 1, // v2-v3-v0

      0, 1, 1, 1, 1, 0, // v0-v3-v4 (direita)
      1, 0, 0, 0, 0, 1, // v4-v5-v0

      1, 0, 1, 1, 0, 1, // v0-v5-v6 (cima)
      0, 1, 0, 0, 1, 0, // v6-v1-v0

      0, 1, 1, 1, 1, 0, // v1-v6-v7 (esquerda)
      1, 0, 0, 0, 0, 1, // v7-v2-v1

      0, 1, 1, 1, 1, 0, // v7-v4-v3 (baixo)
      1, 0, 0, 0, 0, 1, // v3-v2-v7

      0, 0, 1, 0, 1, 1, // v4-v7-v6 (trás)
      1, 1, 0, 1, 0, 0  // v6-v5-v4
  };
  // o cubo tem 36 vértices definidos.
  // cada vértice tem x,y,z, logo, são 108 valores (36 x 3)
  // NUM_VALORES = 108
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

  const int NUM_VALORES = sizeof(verticesCubo) / sizeof(GLfloat);

  glBegin(GL_TRIANGLES);
  int c;
  for (c = 0; c < NUM_VALORES; c += 3)
  {
    glNormal3f(normaisCubo[c], normaisCubo[c + 1], normaisCubo[c + 2]);
    glVertex3f(verticesCubo[c], verticesCubo[c + 1], verticesCubo[c + 2]);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
}
void desenhaParedePorta(){

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, 56.0f);
    glScalef(6.0, 33.0, 40.0);
    desenhaCubo();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, -56.0f);
    glScalef(6.0, 33.0, 40.0);
    desenhaCubo();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0f, 63.0f, 0.0f);
    glScalef(6.0, 30.0, 97.0);
    desenhaCubo();
  glPopMatrix();

}

void desenhaArvore(void){
  
   desenhaEsfera(texturaMadeira, 50);

}