#include "Cams.h"
#include "Lights.h"

void inicializa(){

    xCursor = 0.0;
    yCursor = 50.0; 
    zCursor = 550.0;

    inicializaSol();
    inicializaLuzesInternas();

}

void controleDeCamera(GLint x, GLint y){
    
    // variáveis que guardam o vetor 2D de movimento do mouse na tela
    // xMouse e yMouse são os valores de x e y no frame anterior
    float xChange = x - xMouse;
    float yChange = y - yMouse;

    // este exemplo usa coordenadas esféricas para controlar a câmera...
    // teta e phi guardam a conversão do vetor 2D para um espaço 3D
    // com coordenada esférica
    teta = (teta + xChange/150);
    phi = (phi - yChange/150);

    if(phi >= 180){
      //limite de 180 para o phi
      phi = 180;
    }

    // guarda o x e y do mouse para usar na comparação do próximo frame
    xMouse = x;
    yMouse = y;

    glutPostRedisplay();
}