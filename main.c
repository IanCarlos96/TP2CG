#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include "Draw.c"
#include "Lights.c"

static int slices = 160;
static int stacks = 160;

GLfloat camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ;

char projection = 'p';  // pode ser 'o' também

// void inicializa(){
//     camX = 0.0;
//     camY = 0.0; 
//     camZ = -1.0;
//     centerX = 0.0;
//     centerY = 0.0; 
//     centerZ = 0.0;
//     vectorX = 0.0;
//     vectorY = 1.0;
//     vectorZ = 0.0;

//     inicializaSol();
// }

// void configuraProjecao() {
//   float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);

//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   switch (projection) {
//   case 'p':
//       glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
//       break;
//   case 'o':
//       glOrtho(-3*razaoAspecto, 3*razaoAspecto, -3, 3, -100, 100);
//       break;
//   }

//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity() ;
// }

void redimensiona(int width, int height)
{
    glViewport(0, 0, width, height);
    configuraProjecao();
}

void desenha()
{
    configuraProjecao();
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);

    glColor3d(1,0,0);

    // ESFERA sólida
    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    // CONE sólido
    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    // CUBO sólido
    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(a,0,0,1);
        glutSolidCube(1);
    glPopMatrix();

    // ESFERA em modelo de arame
    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    // CONE em modelo de arame
    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    // CUBO em modelo de arame
    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(a,0,0,1);
        glutWireCube(1);
    glPopMatrix();

    //Desenhando um quadrado pro chão
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(min_width, min_height, min_depth);
        glVertex3f(min_width, min_height, max_depth);
        glVertex3f(max_width, min_height, max_depth);
        glVertex3f(max_width, min_height, min_depth);
    glEnd();

    glutSwapBuffers();
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
        case 'x':
            camX++;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'X':
            camX--;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'y':
            camY++;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'Y':
            camY--;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'z':
            camZ++;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'Z':
            camZ--;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'c':
            centerX++;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'C':
            centerX--;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'v':
            centerY++;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'V':
            centerY--;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'b':
            centerZ++;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
            break;
        case 'B':
            centerZ--;
            printf("[%f %f %f]Cam\n[%f %f %f]Center\n[%f %f %f]Vector\n", camX, camY, camZ, centerX, centerY, centerZ, vectorX, vectorY, vectorZ);
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

    glutCreateWindow("Ortho vs Frustum");

    glutReshapeFunc(redimensiona);
    //glutDisplayFunc(desenha);
    glutDisplayFunc(desenhaCenario);
    glutKeyboardFunc(teclado);
    glutIdleFunc(atoa);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    //GLLIGHT 0 FICAVA AQUI ANTES
    // glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    // glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, light_attenuation_constant);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
   inicializaMateriaisParedes();
   inicializaTexturas();
    //configuraIluminacao();
    glutMainLoop();

    return EXIT_SUCCESS;
}
