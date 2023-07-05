#include <stdio.h>
#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef cams_h
#define cams_h

GLfloat camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ;

GLfloat camAngleX, camAngleY, camAngleZ;

GLint lastMouseX;
GLint lastMouseY;

GLfloat cameraDistance = 100.0f;
GLfloat cameraRotationX = 0.0f;
GLfloat cameraRotationY = 0.0f;

void inicializaCam();

#endif