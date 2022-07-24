#include <Windows.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Render.h"
//#include "./Render.cpp"
//#include "./Texture.cpp"
#include "Actions.cpp"
#include "Threads.cpp"

//Position of player
int xx = 30;
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
int youWinFlag = 0;
int allThornDown = 0;


// game map size = 1536*1536
//level 1 - 940
//level 2 - 430
//level 3 - 0

GLdouble left=0.0, right= 2000.0, bottom=0.0, top = 1000.0 ;
float deltaTime, oldTime;
Diamonds diamond0, diamond1, diamond2, diamond3, diamond4, diamond5, diamond6, diamond7;
int diamondCollected = 0;

Thornsinv Thorn[100];
Diamonds diamond_lvl1[15];
Diamonds diamond_lvl2[15];
Diamonds diamond_lvl3[20];
Human human;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
    glViewport(0, 0, width1, height1);
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
        if (level==3 && yy <= 430)
        {
            upInAir = 1;
            yy += 10;
            if (top < 1536 && yy>=175)
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
        if (yy >= 430 && moveDownFlag==1 && level == 2 || yy < 440 && moveDownFlag != 0 && xx<90)
        {
            yy -= 10;
            if (bottom > 0.0 && yy <= 1150)
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
    if (key == 27) //escape key
    {
        exit(0);
    }
        
    else if (key == 32 && yy == 940) //space key
    {
        yy += 102;
        if (flag == 1) xx += 40;
        else xx -= 40;
        //std::cout << "JUMP: " << xx << "\t" << yy << std::endl;
    }
    else if (key == 13 && level == 0) //enter key
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
    /*
    deltaTime = clock() - oldTime;
    double fps = (1.0 / deltaTime) * 1000;
    oldTime = clock();
    std::cout << "Delta Time: " << deltaTime / CLOCKS_PER_SEC << "sec\tFPS: " << fps << std::endl;
    */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    if (level == 0)
    {
        intro();
    }
    else if (level == 3 && yy < 440 && yy >= 0 && xx >= 1526)
    {
        left = 0.0, right = 2000.0, bottom = 0.0, top = 1000.0; 
        //Sleep(1000);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(left, right, bottom, top);
        glViewport(0, 0, width1, height1);
        win();
    }
    else
    {
        background();
        Blocks block0(320, 1000);
        Blocks block1(320, 1031);
        Blocks block2(331, 1000);
        Blocks block3(331, 1031);
        
        human.init(xx, yy);
        //std::cout << "level " << level << std::endl;
        Ladder ladder(xx, yy);
        ladder.draw();

        Thorns Thorn0(1536, 100); // x coordinate value and no of thorns
        int count = 0;
        for (int i = 0; i < 15; i++)
        {
            if (diamond_lvl1[i].enabled == 1) {
                diamond_lvl1[i].draw();
                diamondCollision(human, diamond_lvl1[i]);
            }
            else count++;

            if (diamond_lvl2[i].enabled == 1) {
                diamond_lvl2[i].draw();
                diamondCollision(human, diamond_lvl2[i]);
            }
            else count++;

            if (diamond_lvl3[i].enabled == 1) {
                diamond_lvl3[i].draw();
                diamondCollision(human, diamond_lvl3[i]);
            }
            else count++;
        }
        diamondCollected = count;
        human.draw();
        //std::cout<<xx<<" "<<yy<<std::endl;
        Pit pit;
        for (int i = 0; i < 90; i++)
        {
            Thorn[i].draw();
        }

        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(left + 20, top - 50);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"SCORE: ");
        glRasterPos2f(left + 75, top-50);
        std::string str = std::to_string(diamondCollected);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)str.c_str());
        
        if (gameOverFlag == 1) {
            Sleep(1000);
            left = 0.0, right = 2000.0, bottom = 0.0, top = 1000.0;

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(left, right, bottom, top);
            glViewport(0, 0, width1, height1);
            end();
        }

        checkObjectsCollisions(human, ladder, block0, block1, block2, block3, diamond0, diamond1, diamond2, diamond3, diamond4, diamond5, diamond6, Thorn0);
    }
    
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
    //std::cout<<"diamonds collected : "<<diamondCollected<<std::endl;

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
    //ThornCollision(human, Thorn1);
}

int main(int argc, char** argv)
{
    for (int i = 0, x = 0; i < 90; i++)
    {
        Thorn[i].init(x, 940);
        x += 16;
    }
    //std::thread kill(dokill);
    for (int i = 0, x = rand()%1536, y = 20 + rand()%380; i < 15; i++, x = rand() % 1536, y = 20 + rand() % 380)
    {
        diamond_lvl1[i].init(x, 1080);
        diamond_lvl2[i].init(x, 500);
        diamond_lvl3[i].init(x, y);
    }

    glutInit(&argc, argv);
    width1 = glutGet(GLUT_SCREEN_WIDTH);
    height1 = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowSize(width1, height1);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Satan Mario");
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
    //std::cout << glGetString(GL_VERSION)<<std::endl;
    //std::cout << width1 << "  " << height1 << std::endl;
    glutMainLoop();
    return 0;
}

