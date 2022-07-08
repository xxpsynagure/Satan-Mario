#include <Windows.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Render.h"
// #include "./Render.cpp"
// #include "./Texture.cpp"

//Position of player
int xx = -50;
int yy = 940;
GLint width1, height1;
int moveDownFlag = 1;

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
    yy -= 0.5;
    glutTimerFunc(30, fallDown, 0);
    glutPostRedisplay();
}

bool collisionDetection(Human &human, Platforms &platform)
{
    if(abs(human.x - platform.x1) < 70 && abs(human.y - platform.y1) < 2)
    {
        std::cout<<"COLLISION DETECTED!!----------\n";
        moveDownFlag = 0;
    }
    else
        moveDownFlag = 1;
    std::cout<<"human x : "<<human.x<<"\t platform x : "<<platform.x1<<"\n";
    std::cout<<"human y : "<<human.y<<"\t platform y : "<<platform.y1<<"\n";
}

void specialkey(int key, int x, int y)
{
    switch (key) {

    case GLUT_KEY_LEFT: 
        if (xx > -50.0)
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
        
        //std::cout << "LEFT: " << xx << "\t" << yy << std::endl;
        break;

    case GLUT_KEY_RIGHT: 
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
}

void display()
{
    // deltaTime = clock() - oldTime;
    // double fps = (1.0 / deltaTime) * 1000;
    // oldTime = clock();
    // std::cout << "Delta Time: " << deltaTime / CLOCKS_PER_SEC << "sec\tFPS: " << fps << std::endl;

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
    collisionDetection(human, platform1);
    glDisable(GL_TEXTURE_2D);
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
    glutSetCursor(GLUT_CURSOR_NONE);

    init();
    loadtexture();
    oldTime = clock();
    glutDisplayFunc(display);
    glutSpecialFunc(specialkey);
    glutKeyboardFunc(keyPressed);
    //glutReshapeFunc(reshape);
    //if (yy > 200)
        //glutTimerFunc(0, fallDown, 0);

    std::cout << glGetString(GL_VERSION)<<std::endl;
    std::cout << width1 << "  " << height1 << std::endl;
    glutMainLoop();
    return 0;
}

