#include <Windows.h>
#include <GL/freeglut.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "./Texture.h"
#include "./Render.h"


int xx = 0;
int yy = 500;
GLint width1, height1;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0.0, (GLdouble)width1/3, 0.0, (GLdouble)height1/3);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
}

/*
void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}*/

void fallDown(int value)
{
    yy -= 0.5;
    glutTimerFunc(30, fallDown, 0);
    glutPostRedisplay();
}

void specialkey(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP: yy += 10; xx += 5;
        break;
    case GLUT_KEY_DOWN: yy -= 5;
        break;
    case GLUT_KEY_LEFT: xx -= 5;
        break;
    case GLUT_KEY_RIGHT: xx += 5;
        break;
    case 27: exit(0);
    default: yy--;
    }
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    background();
    drawPlatforms(100, 100, 200, 100);
    drawPlatforms(400, 550, 500, 550);
    drawPlatforms(900, 320, 1050, 320);
    
    human();
    glDisable(GL_TEXTURE_2D);
    //glFlush();
    // glutPostRedisplay();
    glutSwapBuffers();

}




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    width1 = glutGet(GLUT_SCREEN_WIDTH);
    height1 = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowSize(width1, height1);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Captain Claw's Quest");
    glutFullScreen();
    init();
    loadtexture();

    glutDisplayFunc(display);
    glutSpecialFunc(specialkey);
    glutKeyboardFunc(keyPressed);
    //glutReshapeFunc(reshape);
    if (yy > 200)
        glutTimerFunc(0, fallDown, 0);

    std::cout << glGetString(GL_VERSION);
    glutMainLoop();
    return 0;
}

