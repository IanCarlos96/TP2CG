#include <stdio.h>
#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
    #define M_PI_2 (M_PI/2)
#endif

#ifndef cams_h
#define cams_h

#define raioVisao 100

GLfloat camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ, pitch, yaw;

void inicializaCam();

void controleDeCamera(GLint x, GLint y);

#endif