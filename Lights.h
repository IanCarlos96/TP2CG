#include <stdio.h>
#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef LightsH
#define LightsH

#define intensity_UP 1
#define intensity_DOWN 0

#define lights_height_intern 99

GLfloat light_intensity_sun;

GLfloat light_ambient[4];
GLfloat light_diffuse[4];
GLfloat light_specular[4];
GLfloat light_position[4];


void inicializaSol();
void inicializaLuzesInternas();
void alteraIntensidadeSol(GLint change);

void configuraProjecao();

void changeLightState(GLint lightNum);

#endif