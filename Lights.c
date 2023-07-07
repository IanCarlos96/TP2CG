#include "Lights.h"

void inicializaSol() {
    GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 202.0f, 5.0f, 0.0f };

    GLfloat light_intensity_sun = 1.0f;
}

void inicializaLuzesInternas(){
    //Definir componentes e posições depois. Tbm verificar a situação do último vetor de position (Luz direcional ou posicional)
    //luz 1
    GLfloat light_ambient_1[]  = { 0.8f, 0.6f, 0.8f, 1.0f };
    GLfloat light_diffuse_1[]  = { 0.8f, 0.8f, 0.6f, 1.0f };
    GLfloat light_specular_1[] = { 0.8f, 0.8f, 0.6f, 1.0f };
    GLfloat light_position_1[] = { 97.0f, lights_height_intern, 97.0, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient_1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse_1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular_1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);

    //luz 2
    GLfloat light_ambient_2[]  = { 0.4f, 1.0f, 1.0f, 1.0f };
    GLfloat light_diffuse_2[]  = { 0.4f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular_2[] = { 0.4f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position_2[] = { 309.0f, lights_height_intern, 97.0f, 1.0f };
    glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient_2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse_2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular_2);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position_2);

    //luz 3
    GLfloat light_ambient_3[]  = { 0.2f, 1.0f, 0.0f, 1.0f };
    GLfloat light_diffuse_3[]  = { 0.2f, 1.0f, 0.0f, 1.0f };
    GLfloat light_specular_3[] = { 0.2f, 1.0f, 0.0f, 1.0f };
    GLfloat light_position_3[] = { 521.0f, lights_height_intern, 97.0f, 1.0f };
    glLightfv(GL_LIGHT3, GL_AMBIENT,  light_ambient_3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  light_diffuse_3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular_3);
    glLightfv(GL_LIGHT3, GL_POSITION, light_position_3);

    //luz 4
    GLfloat light_ambient_4[]  = { 0.0f, 0.5f, 1.0f, 0.5f };
    GLfloat light_diffuse_4[]  = { 0.0f, 0.5f, 1.0f, 1.0f };
    GLfloat light_specular_4[] = { 0.0f, 0.5f, 1.0f, 0.5f };
    GLfloat light_position_4[] = { 733.0f, lights_height_intern, 97.0f, 1.0f };
    glLightfv(GL_LIGHT4, GL_AMBIENT,  light_ambient_4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE,  light_diffuse_4);
    glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular_4);
    glLightfv(GL_LIGHT4, GL_POSITION, light_position_4);
}

void alteraIntensidadeSol(GLint change) {
    if (change == intensity_UP) {
        if(light_intensity_sun < 1.0) {
            light_intensity_sun += 0.1;
            light_ambient[0] = light_intensity_sun;
            light_ambient[1] = light_intensity_sun;
            light_ambient[2] = light_intensity_sun;
            light_diffuse[0] = light_intensity_sun;
            light_diffuse[1] = light_intensity_sun;
            light_diffuse[2] = light_intensity_sun;
            light_specular[0] = light_intensity_sun;
            light_specular[1] = light_intensity_sun;
            light_specular[2] = light_intensity_sun;
        }
    } else if (change == intensity_DOWN) {
        if(light_intensity_sun > 0.1) {
            light_intensity_sun -= 0.1;
            light_ambient[0] = light_intensity_sun;
            light_ambient[1] = light_intensity_sun;
            light_ambient[2] = light_intensity_sun;
            light_diffuse[0] = light_intensity_sun;
            light_diffuse[1] = light_intensity_sun;
            light_diffuse[2] = light_intensity_sun;
            light_specular[0] = light_intensity_sun;
            light_specular[1] = light_intensity_sun;
            light_specular[2] = light_intensity_sun;
        }
    }

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    printf("light attenuation constant = %f \n", light_intensity_sun);
}

void changeLightState(GLint lightNum){
    printf ("%d \n", lightNum);
    if(glIsEnabled(lightNum)){
        glDisable(lightNum);
    } else {
        glEnable(lightNum);
    }

}