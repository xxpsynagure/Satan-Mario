#include <Windows.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Render.h"
#include "./Render.cpp"
#include "./Texture.cpp"
#include "./Actions.cpp"

//Position of player
int xx = 0;
int yy = 940;
GLint width1, height1;
int moveDownFlag = 1;
int goWhereFlag = 1;
int flag = 1;
int level = 1;
// game map size = 1536*1536
GLdouble left=0.0, right= 768.0, bottom=768.0, top = 1536.0 ;
float deltaTime, oldTime;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
    glViewport(0, 0, width1, height1);

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
    if (yy > 940 && level==1)
    {
        yy-=3;
        if (flag == 1) xx ++;
        else xx -= 0.5;
    }
    //std::cout <<"flag: " << flag << std::endl;
    glutTimerFunc(30, fallDown, 0);
    glutPostRedisplay();
}


void specialkey(int key, int x, int y)
{
    switch (key) {

    case GLUT_KEY_LEFT: 
        goWhereFlag = 0;
        if (xx > 0.0)
        {
            xx -= 5;
            if (left > 0.0 && xx<=1150)
            {
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                left -= 5; right -= 5;
                gluOrtho2D(left, right, bottom, top);
            }
        }
        flag = 0;
        //std::cout << "LEFT: " << xx << "\t" << yy << std::endl;
        break;

    case GLUT_KEY_RIGHT: 
        goWhereFlag = 1;
        if (xx < 1440)
        {
            xx += 5;
            if (right < 1536 && xx >=165)
            {
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                left += 5; right += 5;
                gluOrtho2D(left, right, bottom, top);
            }
        }
        flag = 1;
        //std::cout << "RIGHT: " << xx << "\t" << yy << "\t\t"<< "left: "<<left<<"\tright:"<<right<<std::endl;
        break;

    case GLUT_KEY_UP: 
        if (yy < 1440)
        {
            yy += 10;
            if (top < 1560)
            {
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                top += 10; bottom += 10;
                gluOrtho2D(left, right, bottom, top);
            }
        }
        // std::cout <<"UP: " << xx << "\t" << yy << std::endl;
        break;

    case GLUT_KEY_DOWN: 
        if (yy > 0 && moveDownFlag!=0)
        {
            yy -= 10;
            if (bottom > 0.0)
            {
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                top -= 10; bottom -= 10;
                gluOrtho2D(left, right, bottom, top);
            }
        }
        // std::cout <<"DOWN: " << xx << "\t" << yy << std::endl;
        break;
    }
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    else if (key == 32)
    {
        if (yy == 940)
        {
            yy += 75;
            if (flag == 1) xx += 40;
            else xx -= 40;
        }
        std::cout << "JUMP: " << xx << "\t" << yy << std::endl;
    }
    glutPostRedisplay();
}

void checkObjectsCollisions(Human &human, Platforms &platform1, Platforms &platform2, Platforms &platform3);

void display()
{
    deltaTime = clock() - oldTime;
    double fps = (1.0 / deltaTime) * 1000;
    oldTime = clock();
    //std::cout << "Delta Time: " << deltaTime / CLOCKS_PER_SEC << "sec\tFPS: " << fps << std::endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    background();
    // drawPlatforms(100, 100, 200, 100);
    // drawPlatforms(400, 550, 500, 550);
    // drawPlatforms(900, 320, 1050, 320);
    Platforms platform1(100, 100, 200, 100);
    Platforms platform2(400, 550, 500, 550);
    Platforms platform3(900, 320, 1050, 320);
    
    // human();
    Human human(xx, yy);
    human.draw();
    // std::cout<<"x value of human is "<<human.x;
    checkObjectsCollisions(human, platform1, platform2, platform3);

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();

}

void checkObjectsCollisions(Human &human, Platforms &platform1, Platforms &platform2, Platforms &platform3)
{
    // platformCollision(human, platform1);
    platformCollision(human, platform2);
    // platformCollision(human, platform3);
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
    glutSetCursor(GLUT_CURSOR_NONE);

    init();
    loadtexture();
    oldTime = clock();
    glutDisplayFunc(display);
    glutSpecialFunc(specialkey);
    glutKeyboardFunc(keyPressed);
    //glutReshapeFunc(reshape);
    glutTimerFunc(30, fallDown, 0);
    std::cout << glGetString(GL_VERSION)<<std::endl;
    std::cout << width1 << "  " << height1 << std::endl;
    glutMainLoop();
    return 0;
}

