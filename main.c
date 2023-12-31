#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include "Draw.c"
#include "Lights.c"


void redimensiona(int width, int height)
{
    glViewport(0, 0, width, height);
    configuraProjecao();
}


static void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :     // Tecla 'ESC
            exit(0);
            break;

        case '+':
            alteraIntensidadeSol(intensity_UP);
            break;
        case '-':
            alteraIntensidadeSol(intensity_DOWN);
            break;

        case 49:        // tecla 1
            changeLightState(GL_LIGHT1);
            break;
        case 50:        // tecla 2
            changeLightState(GL_LIGHT2);
            break;
        case 51:        // tecla 3
            changeLightState(GL_LIGHT3);
            break;
        case 52:        // tecla 4
            changeLightState(GL_LIGHT4);
            break;
        case 53:        // tecla 5
            changeLightState(GL_LIGHT0);
            break;
            //camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ
        case 'w':
        case 'W':
            xCursor-=2;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n", camera.x, camera.y, camera.z, xCursor+camera.x, yCursor+camera.y, zCursor+camera.z);
            break;
        case 'S':
        case 's':
            xCursor+=2;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n", camera.x, camera.y, camera.z, xCursor+camera.x, yCursor+camera.y, zCursor+camera.z);
            break;
        case 'A':
        case 'a':
            zCursor+=2;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n", camera.x, camera.y, camera.z, xCursor+camera.x, yCursor+camera.y, zCursor+camera.z);
            break;
        case 'D':
        case 'd':
            zCursor-=2;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n", camera.x, camera.y, camera.z, xCursor+camera.x, yCursor+camera.y, zCursor+camera.z);
            break;
        case 'o'://aumenta fog
            if(intensidadeFog<1)
                intensidadeFog+=0.1;
                printf("Intensidade fog: %f",intensidadeFog);
                atualizaFog();
            break;
        case 'p'://diminui fog
            if(intensidadeFog > 0.1)
                intensidadeFog -= 0.1;
                if(intensidadeFog == 0){
                    glDisable(GL_FOG);
                }
                printf("Intensidade fog: %f",intensidadeFog);
                atualizaFog();
            break;
    }

    glutPostRedisplay();
}

static void atoa(void)
{
    glutPostRedisplay();
}


// configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
// GLfloat light_ambient[]  = { 1.0f, 0.0f, 0.0f, 1.0f };
// GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
// GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
// GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

// configura alguns parâmetros do modelo de iluminação: MATERIAL
GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat high_shininess[] = { 100.0f };



int main(int argc, char *argv[])
{
    inicializa();

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Era uma casa muito engracada...");

    //glutWarpPointer(320, 240);
    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenhaCenario);
    glutKeyboardFunc(teclado);
    glutPassiveMotionFunc(controleDeCamera);
    glutIdleFunc(atoa);

    glClearColor(1,1,1,1);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //Sol
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, light_attenuation_constant);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    inicializaMateriaisParedes();
    configuraIluminacao();
    inicializaTextura();
    inicializaFog();
    xMouse = glutGet(GLUT_WINDOW_WIDTH)/2;
    yMouse = glutGet(GLUT_WINDOW_HEIGHT)/2;
    glutMainLoop();

    return EXIT_SUCCESS;
}
