#include "Draw.h"
#include "Cams.c"
// #include "Lights.c"

material materialAzul, materialVermelho, materialBranco, materialVerde;
ladrilho ladrilhos[4];
ponto posicaoDaLuz;
GLfloat intensidadeFog = 0;
GLint texturaPlastico, texturaMadeira, texturaBola;

void configuraProjecao()
{
  float razaoAspecto = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Conferir os valores daqui depois
  // glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
  // glFrustum(min_width, max_width, min_height, max_height, min_depth, max_depth);
  //glOrtho(min_width, max_width, min_height, max_height, min_depth, max_depth);
  //gluPerspective(90.0f, razaoAspecto, -100, 400);
  gluPerspective(45.0f, razaoAspecto, 400, -1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void desenhaChao()
{

  // Tem só o retângulo aqui. Ainda precisa setar o material, textura, etc
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texturaGrama);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(min_width, min_height, min_depth);
  glTexCoord2f(1, 0);
  glVertex3f(min_width, min_height, max_depth);
  glTexCoord2f(1, 1);
  glVertex3f(max_width, min_height, max_depth);
  glTexCoord2f(0, 1);
  glVertex3f(max_width, min_height, min_depth);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void desenhaCasa()
{
  glColor3f(1.0f, 0.0f, 0.0f);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  defMaterialVermelho();
  desenhaComodoTipo1();
  glPopMatrix();

  glColor3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
  glTranslatef(212.0, 0.0, 0.0);
  defMaterialVerde();
  desenhaComodoTipo1();
  glPopMatrix();

  glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glTranslatef(424.0, 0.0, 0.0);
  defMaterialAzul();
  desenhaComodoTipo1();
  glPopMatrix();

  glColor3f(1.0f, 1.0f, 1.0f);
  glPushMatrix();
  glTranslatef(636.0, 0.0, 0.0);
  defMaterialBranco();
  desenhaComodoTipo1();
  glPopMatrix();

  // piso geral
  // glColor3f(0, 0, 0);
  // glBegin(GL_QUADS);
  // glVertex3f(0, -79, 0);
  // glVertex3f(300, -79, 0);
  // glVertex3f(300, -79, 300);
  // glVertex3f(0,-79, 300);
  // glEnd();
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

  glPushMatrix();
  glTranslatef(0, -50, 0);
  desenhaChao();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -40.0, 0);
  desenhaCasa();
  glPopMatrix();

  
  glPushMatrix();
  glTranslatef(0.0, 100.0, 0.0);
  glScalef(10.0, 10.0, 10.0);
  glTranslatef(-8.0, 0.0, -12.0);

  glPushMatrix();
  glTranslatef(0, -10, 0);
  desenhaArvore();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-12, -10, -15);
  desenhaArvore();
  glPopMatrix();
  
  
  glTranslatef(9.0, -12.0, 4.0);
  glPushMatrix();
  glTranslatef(0, -10, 0);
  desenhaMesa();
  glPopMatrix();
  
  
  
  
  glPopMatrix();


  glPushMatrix();
  glTranslatef(-250.0f, 200.0f, 100.0f);
  desenhaMoinho();
  glPopMatrix();
  
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
      float xVertice = larguraDoSubTriangulo * j;
      switch (direcao)
      {

      case 1:
        glTexCoord2f(xVertice, yVerticesLinhaDeCima);
        glVertex2f(xVertice, yVerticesLinhaDeCima);
        glTexCoord2f(xVertice, yVerticesLinhaDeBaixo);
        glVertex2f(xVertice, yVerticesLinhaDeBaixo);
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
  desenhaRetanguloSubdividido(QUANT_SUBDIVISOES, direcao);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void inicializaMateriaisParedes(void)
{
  // glEnable(GL_LIGHTING);//Estava comentado no exemplo, não sei o pq
  materialAzul.ambiente = (cor){0.25, 0.25, 0.25, 1};
  materialAzul.emissiva = (cor){0, 0, 0, 1};
  materialAzul.difusa = (cor){0.1, 0.1, 0.4, 1};
  materialAzul.especular = (cor){1, 1, 1, 1};
  materialAzul.brilhosidade[0] = 100;

  materialVermelho.ambiente = (cor){0.1, 0.1, 0.1, 1};
  materialVermelho.emissiva = (cor){0, 0, 0, 1};
  materialVermelho.difusa = (cor){.49, .22, .02, 1};
  materialVermelho.especular = (cor){0, 0, 0, 1};
  materialVermelho.brilhosidade[0] = 0;

  materialBranco.ambiente = (cor){0.1, 0.1, 0.1, 1};
  materialBranco.emissiva = (cor){0, 0, 0, 1};
  materialBranco.difusa = (cor){.49, .22, .02, 1};
  materialBranco.especular = (cor){0, 0, 0, 1};
  materialBranco.brilhosidade[0] = 0;

  materialVermelho.ambiente = (cor){0.1, 0.1, 0.1, 1};
  materialVermelho.emissiva = (cor){0, 0, 0, 1};
  materialVermelho.difusa = (cor){.49, .22, .02, 1};
  materialVermelho.especular = (cor){0, 0, 0, 1};
  materialVermelho.brilhosidade[0] = 0;
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
  inicializaSol();
  inicializaLuzesInternas();
  /*
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
  */
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
void solidCilindro(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint stacks, GLint columns)
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
  // cria os vértices de uma cilindro
  gluCylinder(quadObj, baseRadius, topRadius, height, stacks, columns);
  // limpa as variáveis que a GLU usou para criar
  // a esfera

  gluDeleteQuadric(quadObj);
}
void solidDisco(GLdouble innerRadius, GLdouble outerRadius, GLint stacks, GLint columns)
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
  // cria os vértices de uma cilindro
  gluDisk(quadObj, innerRadius, outerRadius, stacks, columns);
  // limpa as variáveis que a GLU usou para criar
  // a esfera

  gluDeleteQuadric(quadObj);
}
void solidPartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle)
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
  // cria os vértices de uma cilindro
  gluPartialDisk(quadObj, innerRadius, outerRadius, 50.0, 50.0, startAngle, sweepAngle);
  // limpa as variáveis que a GLU usou para criar
  // a esfera

  gluDeleteQuadric(quadObj);
}
void solidCone(GLdouble baseRadius, GLdouble height, GLint slices, GLint stacks)
{
  // Cria uma quádrica
  GLUquadric *quadObj = gluNewQuadric();
  // Define o estilo de renderização para preenchido
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  // Define as normais suavizadas para os vértices
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  // Define as coordenadas de textura
  gluQuadricTexture(quadObj, GL_TRUE);
  // Cria os vértices do cone
  gluCylinder(quadObj, baseRadius, 0.0, height, slices, stacks);
  // Limpa as variáveis que a GLU usou para criar o cone
  gluDeleteQuadric(quadObj);
}

void desenhaCilindro(GLint textura, GLdouble baseRadius, GLdouble topRadius, GLdouble height)
{
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textura);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glPolygonMode(GL_FRONT, GL_FILL);
  solidCilindro(baseRadius, topRadius, height, 50, 50);
  glDisable(GL_TEXTURE_2D);
}
void desenhaEsfera(GLint textura, GLint raio)
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

void desenhaDisco(GLint textura, GLdouble innerRadius, GLdouble outerRadius)
{
  
  glColor3f(1, 1, 1);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, textura);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glPolygonMode(GL_FRONT, GL_FILL);
  solidDisco(innerRadius, outerRadius, 50.0, 50.0);
  glDisable(GL_BLEND);

  glDisable(GL_TEXTURE_2D);
}

void desenhaDiscoParcial(GLint textura, GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle)
{
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textura);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glPolygonMode(GL_FRONT, GL_FILL);
  solidPartialDisk(innerRadius, outerRadius, 50.0, 50.0);
  glDisable(GL_TEXTURE_2D);
}

void desenhaCilindroSemTXT(GLdouble baseRadius, GLdouble topRadius, GLdouble height)
{
  glPolygonMode(GL_FRONT, GL_FILL);
  solidCilindro(baseRadius, topRadius, height, 50, 50);
}
void desenhaEsferaSemTXT(GLint raio)
{
  glPolygonMode(GL_FRONT, GL_FILL);
  solidSphere(raio, 50, 50);
}

void desenhaDiscoSemTXT(GLdouble innerRadius, GLdouble outerRadius)
{

  glPolygonMode(GL_FRONT, GL_FILL);
  solidDisco(innerRadius, outerRadius, 50.0, 50.0);
}

void desenhaDiscoParcialSemTXT(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle)
{
  glPolygonMode(GL_FRONT, GL_FILL);
  solidPartialDisk(innerRadius, outerRadius, 50.0, 50.0);
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
void defMaterialAzul()
{
  material materialUtilizado = (materialAzul);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialUtilizado.ambiente.v);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialUtilizado.difusa.v);
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialUtilizado.especular.v);
  glMaterialfv(GL_FRONT, GL_SHININESS, materialUtilizado.brilhosidade);
}
void defMaterialVermelho()
{
  material materialUtilizado = (materialVermelho);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialUtilizado.ambiente.v);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialUtilizado.difusa.v);
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialUtilizado.especular.v);
  glMaterialfv(GL_FRONT, GL_SHININESS, materialUtilizado.brilhosidade);
}
void defMaterialBranco()
{
  material materialUtilizado = (materialBranco);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialUtilizado.ambiente.v);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialUtilizado.difusa.v);
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialUtilizado.especular.v);
  glMaterialfv(GL_FRONT, GL_SHININESS, materialUtilizado.brilhosidade);
}
void defMaterialVerde()
{
  material materialUtilizado = (materialVerde);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialUtilizado.ambiente.v);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialUtilizado.difusa.v);
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialUtilizado.especular.v);
  glMaterialfv(GL_FRONT, GL_SHININESS, materialUtilizado.brilhosidade);
}
// Ainda não funciona
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
void desenhaParedePorta()
{

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

void desenhaArvore(void)
{
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  desenhaCilindro(texturaMadeira, 1.0, 2.0, 10.0);
  glColor3f(0.0f, 0.8f, 0.0f);
  glPushMatrix();
  glTranslatef(0.0, 0.0, -5.0);
  desenhaEsferaSemTXT(1);
  glTranslatef(0.0, 0.0, 2.8);
  desenhaEsferaSemTXT(2);
  glTranslatef(0.0, 0.0, 4.0);
  desenhaEsferaSemTXT(3);
  glPopMatrix();
  glPopMatrix();
}

void desenhaMesa(void)
{
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glTranslatef(0, 0, -5.0);
  desenhaCilindro(texturaMadeira, 0.5, 0.5, 3.0);
  glColor3f(0.0f, 0.8f, 0.0f);
  
  glColor3f(0,0,0);
  glPushMatrix();
  glScalef(3.0, 3.0, 0.2);
  desenhaCubo();
  glPopMatrix();

  glColor3f(0,0,0);
  glPushMatrix();
  glTranslatef(0, -6, 3);
  glScalef(3.0, 0.6, 1);
  desenhaCubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -6.9, 3);
  glScalef(3.0, 0.5, 2);
  desenhaCubo();
  glPopMatrix();

  glPopMatrix();
}

void desenhaComodoTipo1()
{
  // Parede 1
  glPushMatrix();

  glTranslatef(0.0f, 0.0f, 0.0f);
  glScalef(97.0, 97.0, 6.0);
  desenhaCubo();
  glPopMatrix();

  // Parece2
  glPushMatrix();
  glTranslatef(100.0f, 0.0f, 100.0f);
  desenhaParedePorta();
  glPopMatrix();

  // Parede3
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 200.0f);
  glScalef(97.0, 97.0, 6.0);
  desenhaCubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-100.0f, 0.0f, 100.0f);
  desenhaParedePorta();
  glPopMatrix();

  // Desenha teto
  glPushMatrix();
  glTranslatef(0.0f, 98.0f, 100.0f);
  glScalef(97.0, 6.0, 97.0);
  desenhaCubo();
  glPopMatrix();
}

void inicializaFog(void)
{
  GLfloat cor[] = {0.5f, 0.5f, 0.5f};
  glClearColor(cor[0], cor[1], cor[2], 1.0f);

  glFogi(GL_FOG_MODE, GL_EXP);       // Linear, exp. ou exp²
  glFogfv(GL_FOG_COLOR, cor);        // Cor
  glFogf(GL_FOG_DENSITY, 0.0f);      // Densidade
  glHint(GL_FOG_HINT, GL_DONT_CARE); // Não aplicar se não puder
  glFogf(GL_FOG_START, 1.0f);        // Profundidade inicial
  glFogf(GL_FOG_END, 5.0f);          // Profundidade final
  glEnable(GL_FOG);
  // Liga GL_FOG
}

void atualizaFog()
{

  GLfloat densidade = intensidadeFog * 0.1f;
  glFogf(GL_FOG_DENSITY, densidade);
}

void desenhaChuveiro()
{
  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  glPushMatrix();
  glScalef(1.0, 1.0, 1.0);
  desenhaCubo();
  glPopMatrix();
  glTranslatef(0.0, 1.0, 0.0);
  desenhaCilindroSemTXT(0.3, 0.3, 10.0);
  glPopMatrix();
  glColor3f(1.0, 1.0, 1.0);
}

void desenhaBola(){

   glPushMatrix();
   glTranslatef(-400.0f, -70.0f, 100.0f);
   glRotated(180, 0, 1, 0);
  desenhaEsfera(texturaBola, 20);
  glPopMatrix();
   
}

void desenhaMoinho()
{

  const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  const double a = t * 90.0;

  // desenhaPaMoinho();
  glRotated(a, 0, 0, 1);
  desenhaDisco(texturaMoinho, 10.0, 100.0);
  glPushMatrix();
  glRotated(180, 0, 1, 0);
  glRotated(-a, 0, 0, 1);
  //desenhaDisco(texturaMoinho, 10.0, 100.0);
  glPopMatrix();

  glPopMatrix();

  // Desenhe o corpo do moinho com textura
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 2.0f);
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(-250.0f, -135.0f, 100.0f);
  glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
  glScalef(50.0f, 50.0f, 50.0f);
  desenhaCone(texturaMadeira, 1.0f, 7.0f, 20, 20);
}

void desenhaCone(GLint textura, GLdouble baseRadius, GLdouble height, GLint slices, GLint stacks)
{
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textura);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glPolygonMode(GL_FRONT, GL_FILL);
  solidCone(baseRadius, height, slices, stacks);
  glDisable(GL_TEXTURE_2D);
}

void inicializaTextura()
{
  texturaPlastico = carregaTextura("Imagens/plastico.jpg");
  texturaMadeira = carregaTextura("Imagens/madeira.jpg");
  texturaGrama = carregaTextura("Imagens/grama.png");
  texturaMoinho = carregaTextura("Imagens/moinho.png");
}