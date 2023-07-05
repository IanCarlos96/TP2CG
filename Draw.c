#include "Draw.h"
#include "Cams.c"
//#include "Lights.c"

void configuraProjecao() {
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // fovy, aspectRatio, nearZ, farZ
  //gluPerspective(45.0f, razaoAspecto, min_depth, max_depth);
  gluPerspective(45.0f, razaoAspecto, -2, 10);
  //Conferir os valores daqui depois
  //glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
  //glFrustum(min_width, max_width, min_height, max_height, min_depth, max_depth);
  //glOrtho(min_width, max_width, min_height, max_height, min_depth, max_depth);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;
}

void desenhaChao() {

  //Tem só o retângulo aqui. Ainda precisa setar o material, textura, etc
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
      glVertex3f(min_width, min_height, min_depth);
      glVertex3f(min_width, min_height, max_depth);
      glVertex3f(max_width, min_height, max_depth);
      glVertex3f(max_width, min_height, min_depth);
  glEnd();
}

void desenhaCasa() {
  //1 parede
  glColor3f(0.5, 0.5, 0.5);
  glBegin(GL_QUADS);
    glVertex3f(-15, 0, 0);
    glVertex3f(15, 0, 0);
    glVertex3f(15, teto_altura, 0);
    glVertex3f(-15, teto_altura, 0);
  glEnd();

  //2 parede
  glColor3f(0.7, 0.7, 0);
  glBegin(GL_QUADS);
    glVertex3f(-15, 0, 0);
    glVertex3f(-15, teto_altura, 0);
    glVertex3f(-15, teto_altura, 30);
    glVertex3f(-15, 0, 30);
  glEnd();

  //3 parede
  glColor3f(0.2, 0.7, 0);
  glBegin(GL_QUADS);
    glVertex3f(-15, 0, 30);
    glVertex3f(15, 0, 30);
    glVertex3f(15, teto_altura, 30);
    glVertex3f(-15, teto_altura, 30);
  glEnd();

  //4 parede
  // glColor3f(0.7, 0.7, 0);
  // glBegin(GL_QUADS);
  //   glVertex3f(0, 0, 0);
  //   glVertex3f(0, 0, 300);
  //   glVertex3f(300, 0, 300);
  //   glVertex3f(300, 0, 0);
  // glEnd();

  //piso geral
  glColor3f(0.8, 0, 0.2);
  glBegin(GL_QUADS);
    glVertex3f(-15, 0, 0);
    glVertex3f(15, 0, 0);
    glVertex3f(15, 0, 30);
    glVertex3f(-15, 0, 30);
  glEnd();
}

void desenhaCenario(){
    configuraProjecao();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
    gluLookAt(camX, camY, camZ, -camAngleX, -camAngleY, camAngleZ, vectorX, vectorY, vectorZ);
    // gluLookAt(cameraDistance * sin(cameraRotationY * 0.01745f) * cos(cameraRotationX * 0.01745f),
    //           cameraDistance * sin(cameraRotationX * 0.01745f),
    //           cameraDistance * cos(cameraRotationY * 0.01745f) * cos(cameraRotationX * 0.01745f),
    //           0.0f, 0.0f, 0.0f,
    //           0.0f, 1.0f, 0.0f);

    desenhaChao();

    desenhaCasa();
    glColor3f(0,0,0);
    //glutWireTeapot(100);

    glutSwapBuffers();
}