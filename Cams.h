#include <stdio.h>
#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef cams_h
#define cams_h

#define raioVisao 100

GLint xMouse = 0, yMouse = 0;     //variáveis globais que serão usadas na função posicionaCamera
GLint xCursor, yCursor, zCursor;  //guarda o centro do cursor
GLfloat phi = 90, teta = 0;       //ângulos das coordenadas esféricas

struct {
  float x, y, z;
  float targetX, targetY, targetZ;
} camera;

void inicializaCam();

void controleDeCamera(GLint x, GLint y);

#endif