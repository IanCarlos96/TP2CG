#include "Lights.h"

void inicializaSol() {
    GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    GLfloat light_intensity_sun = 1.0f;
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