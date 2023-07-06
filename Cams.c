#include "Cams.h"
#include "Lights.h"

void inicializa(){

    yaw = 0.0;

    // camX = 150.0;
    // camY = 10.0; 
    // camZ = -150.0;
    // centerX = 150.0;
    // centerY = 10.0; 
    // centerZ = 0.0;
    // vectorX = 0.0;
    // vectorY = 1.0;
    // vectorZ = 0.0;

    // camX = 0.0;
    // camY = 1.0; 
    // camZ = 00.0;
    // centerX = 0.0;
    // centerY = 0.0; 
    // centerZ = 0.0;
    // vectorX = 0.0;
    // vectorY = 1.0;
    // vectorZ = 0.0;

    // camX = 0.0;
    // camY = 50.0; 
    // camZ = 100.0;
    // centerX = 0.0;
    // centerY = 0.0; 
    // centerZ = 0.0;
    // vectorX = 0.0;
    // vectorY = 50.0;
    // vectorZ = 0.0;

    camX = 222.0;
    camY = 50.0; 
    camZ = 550.0;
    centerX = 0.0;
    centerY = 0.0; 
    centerZ = 100.0;
    vectorX = 0.0;
    vectorY = 50.0;
    vectorZ = 0.0;

    inicializaSol();
    inicializaLuzes();
}

void controleDeCamera(GLint x, GLint y){
    //GLfloat mouseDisplacementX = x - (glutGet(GLUT_WINDOW_WIDTH)/2); // (float)glutGet(GLUT_WINDOW_HEIGHT);
    //GLfloat mouseDisplacementY = y - (glutGet(GLUT_WINDOW_HEIGHT)/2); // (float)glutGet(GLUT_WINDOW_HEIGHT);

    //Meia tela = 180°
    // displacement = x°
    //

    GLfloat teste = (glutGet(GLUT_WINDOW_WIDTH));
    //yaw = M_PI * mouseDisplacementX / teste;
    yaw = M_PI * x / teste;
    //pitch = M_PI * mouseDisplacementY / (glutGet(GLUT_WINDOW_HEIGHT)/2);

    centerX = -cos(yaw) * raioVisao;
    centerZ = -sin(yaw) * raioVisao;

    //printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);

    glutPostRedisplay();
}