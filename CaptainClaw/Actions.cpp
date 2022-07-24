#include "Render.h"
extern int level, allThornDown;

extern int moveDownFlag, level, upInAir, moveRight, moveLeft, gameOverFlag, xx,yy,flag,youWinFlag;
extern GLdouble top, bottom, left, right;

void fallDown(int value)
{
    if (yy > 940 && level == 1 && upInAir == 1)
    {
        yy -= 3;
        if (flag == 1) xx++;
        else xx -= 0.5;
    }
    if (level == 2 && yy < 940 && yy>430)
    {
        yy -= 10;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        top -= 10; bottom -= 10;
        gluOrtho2D(left, right, bottom, top);
    }
    if (level == 3 && yy >= 0 && yy <= 430 && xx < 1526)
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
            left++; right++;
            gluOrtho2D(left, right, bottom, top);
        }
    }
    else
        upInAir = 0;
    //std::cout <<"flag: " << flag << std::endl;
    if (youWinFlag == 1)
        glutTimerFunc(3, NULL, 0);
    else
        glutTimerFunc(30, fallDown, 0);
    glutPostRedisplay();
}


void ladderCollision(Human &human , Ladder &ladder)
{
    bool collideX = ( human.bottomRight.x >= ladder.bottomLeft.x && human.bottomLeft.x <= ladder.bottomRight.x ); 
    bool collideY = ( human.bottomLeft.y >= ladder.bottomLeft.y && ladder.topLeft.y >= human.bottomRight.y - 10);
    bool collided = collideX && collideY;

    /*
    if(collideX && human.bottomLeft.y > 900|| human.bottomLeft.y < 940 && human.bottomLeft.y > 430)
    {
        moveDownFlag = 1;
        level = 2;
    }
    if (collideX && human.bottomLeft.y < 430 || human.bottomLeft.y <= 430 && human.bottomLeft.y >= 0)
    {
        moveDownFlag = 2;
        level = 3;
    }
    else
    {
        moveDownFlag = 0;
        level = 1;
    } 
    */
    if (collided && level == 1 && human.bottomLeft.y > 900 || human.bottomLeft.y < 900 && human.bottomLeft.y > 400)
    {
        moveDownFlag = 1;
        level = 2;
    }
    if (collided && level == 2 && human.bottomLeft.y < 470 || human.bottomLeft.y < 430 && human.bottomLeft.y >= 0)
    {
        moveDownFlag = 2;
        level = 3;
    }
    if(!collided && human.bottomLeft.y > 900)
    {
        moveDownFlag = 0;
        level = 1;
    }
}

void blockCollision(Human &human, Blocks &block)
{
    bool collideX = human.bottomRight.x >= block.bottomLeft.x && block.bottomLeft.x+10 >= human.bottomLeft.x;
    bool collideY = human.bottomRight.y >= block.bottomLeft.y && block.bottomLeft.y+30 >= human.bottomLeft.y;

    if(collideX & collideY){
        upInAir = 0;
    }
    else{
        upInAir = 1;
    }
}

void diamondCollision(Human &human, Diamonds &diamond0)
{
    bool collideX = human.bottomRight.x >= diamond0.left.x && human.bottomLeft.x <= diamond0.right.x;
    bool collideY = human.topRight.y >= diamond0.bottom.y && human.bottomLeft.y <= diamond0.top.y;

    if(collideX & collideY){
        // std::cout<<"diamond is destroyed";
        diamond0.enabled = 0;
    }
}

void ThornCollision(Human &human, Thorns &Thorn)
{
    //bool collideX = human.bottomLeft.x <= 980 && human.bottomLeft.x >= 800;
    bool collideY = human.bottomLeft.y <= 50;
    //bool collided = collideX && collideY;
    if(collideY)
    {
        std::cout<<"You died";
        gameOverFlag = 1;
    }
    if(level == 3 && allThornDown ==  1)
    {
        if(human.topLeft.y >= 420)
        {
            std::cout<<"You died";
            gameOverFlag = 1;
        }
    }
}