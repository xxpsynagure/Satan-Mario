#include <Windows.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Render.h"
// #include "./Render.cpp"
// #include "./Texture.cpp"
#include "Actions.cpp"

//Position of player
int xx = 0;
int yy = 940;

//window resolution
GLint width1, height1;

//Flags
int moveDownFlag = 0;
int goWhereFlag = 1;
int flag = 1;
int level = 0;
int upInAir = 0;
int moveRight = 1, moveLeft = 1;
int gameOverFlag = 0;

// game map size = 1536*1536
//level 1 - 940
//level 2 - 440
//level 3 - 0

GLdouble left=0.0, right= 2000.0, bottom=0.0, top = 1000.0 ;
float deltaTime, oldTime;
Diamonds diamond0, diamond1, diamond2, diamond3, diamond4, diamond5, diamond6, diamond7;
int diamondCollected = 0;
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
    if (yy > 940 && level==1 && upInAir==1)
    {
        yy-=3;
        if (flag == 1) xx ++;
        else xx -= 0.5;
    }
    if (level == 3&& yy>=0)
    {
        yy -= 3;
        xx++;
        if (bottom > 0.0)
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            top -= 3; bottom -= 3;
            gluOrtho2D(left, right, bottom, top);
        }
        if (right < 1536.0 && xx >= 165)
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            left ++; right ++;
            gluOrtho2D(left, right, bottom, top);
        }
    }
    else
        upInAir = 0;
    //std::cout <<"flag: " << flag << std::endl;
    glutTimerFunc(30, fallDown, 0);
    glutPostRedisplay();
}


void specialkey(int key, int x, int y)
{
    switch (key) {

    case GLUT_KEY_LEFT: 
        goWhereFlag = 0;
        if (xx > 0.0 && moveLeft == 1)
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
        
        if (xx < 1526 && moveRight == 1)
        {
            xx += 5;
            if (right < 1536.0 && xx>=165)
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
        if (level!=1 && yy < 1440)
        {
            upInAir = 1;
            yy += 10;
            if (top < 1500)
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
        if (yy > 0 && moveDownFlag!=0 && level != 1)
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
            yy += 102;
            if (flag == 1) xx += 40;
            else xx -= 40;
        }
        std::cout << "JUMP: " << xx << "\t" << yy << std::endl;
    }
    else if (key == 13)
    {
        level = 1;
        left = 0.0, right = 768.0, bottom = 768.0, top = 1536.0;
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(left, right, bottom, top);
        glViewport(0, 0, width1, height1);
    }
    glutPostRedisplay();
}

void checkObjectsCollisions(Human &human, Ladder &ladder, Blocks &block0, Blocks &block1, Blocks &block2, Blocks &block3, Diamonds &diamond0, Diamonds &diamond1, Diamonds &diamond2, Diamonds &diamond3, Diamonds &diamond4, Diamonds &diamond5, Diamonds &diamond6, Thorns &Thorn0);


void display()
{
    deltaTime = clock() - oldTime;
    double fps = (1.0 / deltaTime) * 1000;
    oldTime = clock();
    //std::cout << "Delta Time: " << deltaTime / CLOCKS_PER_SEC << "sec\tFPS: " << fps << std::endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    if (level == 0)
    {
        intro();
    }
    else
    {
        background();
        // drawPlatforms(100, 100, 200, 100);
        // drawPlatforms(400, 550, 500, 550);
        // drawPlatforms(900, 320, 1050, 320);
        // Platforms platform0(350, 1050, 450, 1050);
        Blocks block0(320, 1000);
        Blocks block1(320, 1031);
        Blocks block2(331, 1000);
        Blocks block3(331, 1031);
        // Blocks block4(320, 1031);
        // Platforms platform1(100, 100, 200, 100);
        // Platforms platform2(400, 550, 500, 550);
        // Platforms platform3(900, 320, 1050, 320);
        std::cout << "level " << level << std::endl;
        Ladder ladder(xx, yy);
        ladder.draw();



        Thorns Thorn0(980, 10); // x coordinate value and no of thorns

        if (diamond0.enabled == 1)
        {
            diamond0.draw(400, 1050);
        }
        if (diamond1.enabled == 1)
        {
            diamond1.draw(450, 1050);
        }
        if (diamond2.enabled == 1)
        {
            diamond2.draw(500, 1050);
        }
        if (diamond3.enabled == 1)
        {
            diamond3.draw(500, 800);
        }
        if (diamond4.enabled == 1)
        {
            diamond4.draw(430, 600);
        }
        if (diamond5.enabled == 1)
        {
            diamond5.draw(300, 300);
        }
        if (diamond6.enabled == 1)
        {
            diamond6.draw(500, 400);
        }

        Human human(xx, yy);
        human.draw();
        // std::cout<<xx<<" "<<yy;
        if (gameOverFlag == 1) {
            //glRasterPos2f(980, 100);
            //glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)"Game Over");
            Sleep(1000);
            //std::exit(0);

            left = 0.0, right = 2000.0, bottom = 0.0, top = 1000.0;

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(left, right, bottom, top);
            glViewport(0, 0, width1, height1);
            end();
            std::cout << "Total Diamonds: " << diamondCollected << std::endl;
        }


        checkObjectsCollisions(human, ladder, block0, block1, block2, block3, diamond0, diamond1, diamond2, diamond3, diamond4, diamond5, diamond6, Thorn0);

    }
    
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
    // std::cout<<"diamonds collected : "<<diamondCollected<<std::endl;

}

void checkObjectsCollisions(Human &human, Ladder &ladder, Blocks &block0, Blocks &block1, Blocks &block2, Blocks &block3, Diamonds &diamond0, Diamonds &diamond1, Diamonds &diamond2, Diamonds &diamond3, Diamonds &diamond4, Diamonds &diamond5, Diamonds &diamond6, Thorns &Thorn0)
{
    // platformCollision(human, platform1);
    // platformCollision(human, platform1);
    // platformCollision(human, platform3);
    ladderCollision(human, ladder);
    blockCollision(human, block0);
    blockCollision(human, block1);
    blockCollision(human, block2);
    blockCollision(human, block3);
    diamondCollision(human, diamond0);
    diamondCollision(human, diamond1);
    diamondCollision(human, diamond2);
    diamondCollision(human, diamond3);
    diamondCollision(human, diamond4);
    diamondCollision(human, diamond5);
    diamondCollision(human, diamond6);
    ThornCollision(human, Thorn0);
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

