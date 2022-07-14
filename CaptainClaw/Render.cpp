#include <GL/freeglut.h>
#include <math.h>
#include "Render.h"
extern int yy, xx, goWhereFlag;

// void drawPlatforms(int x1, int y1, int x2, int y2)
// {
//     glColor3f(1.0, 1.0, 1.0);
//     glBegin(GL_QUADS);
//     glVertex2f(x1, y1);
//     glVertex2f(x2, y2);
//     glVertex2f(x2 - 10, y2 + 5);
//     glVertex2f(x1 + 10, y1 + 5);
//     glEnd();
// }

// void human()
// {
//     glColor3f(1.0, 0.0, 0.0);

//     float theta;
//     glBegin(GL_POLYGON); // FACE
//     for (int i = 0; i < 360; i++)
//     {
//         theta = i * 3.14159 / 180;
//         glVertex2f(xx + 150/2 + cos(theta) * 30/2, yy + 200/2 + sin(theta) * 30/2);
//     }
//     glEnd();

//     glLineWidth(5); // BODY
//     glBegin(GL_LINES);
//     glVertex2d(xx + 75.0, yy + 65.0);
//     glVertex2d(xx + 75.0, yy + 85.0);
//     glEnd();

//     glBegin(GL_LINE_STRIP); // LEGS
//     glVertex2d(xx + 65.0, yy + 50.0);
//     glVertex2d(xx + 75.0, yy + 65.0);
//     glVertex2d(xx + 85.0, yy + 50.0);
//     glEnd();

//     glBegin(GL_LINE_STRIP); // HANDS
//     glVertex2d(xx + 65.0, yy + 75.0);
//     glVertex2d(xx + 75.0, yy + 85.0);
//     glVertex2d(xx + 85.0, yy + 75.0);
//     glEnd();

//     glColor3f(0.0, 0.0, 0.0);
//     glPointSize(5);
//     glBegin(GL_POINTS); // EYES
//     glVertex2d(xx + 135.0/2, yy + 210.0/2);
//     glVertex2d(xx + 165.0/2, yy + 210.0/2);
//     glEnd();

// }

Human::Human(int xx, int yy)
{
    this->x = xx;
    this->y = yy;
    // Below is the boundary box around the human.
    this->bottomLeft.x = xx - 10;
    this->bottomLeft.y = yy + 50;
    this->bottomRight.x = xx + 10;
    this->bottomRight.y = yy + 50;
    this->topRight.x = xx + 15;
    this->topRight.y = yy + 115;
    this->topLeft.x = xx - 15;
    this->topLeft.y = yy + 115;
}

void Human::draw()
{
    // Below is the boundary box around the human.
    // glLineWidth(1.5);
    // glColor3f(1.0, 1.0, 1.0);
    // glBegin(GL_LINE_LOOP);
    // glVertex2d(bottomLeft.x, bottomLeft.y);
    // glVertex2d(bottomRight.x, bottomRight.y);
    // glVertex2d(topRight.x, topRight.y);
    // glVertex2d(topLeft.x, topLeft.y);
    // glEnd();

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON); // FACE
    for (int i = 0; i < 360; i++)
    {
        this->theta = i * 3.14159 / 180;
        glVertex2f(x + cos(this->theta) * 15, y + 100 + sin(this->theta) * 15);
    }
    glEnd();

    glLineWidth(5); // BODY
    glBegin(GL_LINES);
    glVertex2d(x , y + 65.0);
    glVertex2d(x , y + 85.0);
    glEnd();

    glBegin(GL_LINE_STRIP); // LEGS
    glVertex2d(x - 10.0, y + 50.0);
    glVertex2d(x , y + 65.0);
    glVertex2d(x + 10.0, y + 50.0);
    glEnd();

    glBegin(GL_LINE_STRIP); // HANDS
    glVertex2d(x - 10.0, y + 75.0);
    glVertex2d(x , y + 85.0);
    glVertex2d(x + 10.0, y + 75.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glPointSize(5);
    glBegin(GL_POINTS); // EYES
    if(goWhereFlag == 1)
    {
        glVertex2d(x + 6.5, y + 105.0);
        glVertex2d(x + 12.0, y + 105.0);
    }
    else
    {
        glVertex2d(x - 6.5, y + 105.0);
        glVertex2d(x - 12.0, y + 105.0);
    }
    glEnd();

    // std::cout<<"\nClass method is executed";

}

Platforms::Platforms(int xx1, int yy1, int xx2, int yy2)
{
    this->bottomLeft.x = xx1;
    this->bottomLeft.y = yy1;
    this->bottomRight.x = xx2;
    this->bottomRight.y = yy2;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(this->bottomLeft.x, this->bottomLeft.y);
    glVertex2f(this->bottomRight.x, this->bottomRight.y);
    glVertex2f(this->bottomRight.x - 10, this->bottomRight.y + 5);
    glVertex2f(this->bottomLeft.x + 10, this->bottomLeft.y + 5);
    glEnd();
}