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

void desenhaCenario();

void desenhaChao();

void desenhaCasa();

#endif