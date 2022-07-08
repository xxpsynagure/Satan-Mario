#include <GL/freeglut.h>
#include <math.h>
#include "Render.h"
extern int yy, xx;

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
//     glVertex2d(xx + 150.0/2, yy + 130.0/2);
//     glVertex2d(xx + 150.0/2, yy + 170.0/2);
//     glEnd();

//     glBegin(GL_LINE_STRIP); // LEGS
//     glVertex2d(xx + 130.0/2, yy + 100.0/2);
//     glVertex2d(xx + 150.0/2, yy + 130.0/2);
//     glVertex2d(xx + 170.0/2, yy + 100.0/2);
//     glEnd();

//     glBegin(GL_LINE_STRIP); // HANDS
//     glVertex2d(xx + 130.0/2, yy + 150.0/2);
//     glVertex2d(xx + 150.0/2, yy + 170.0/2);
//     glVertex2d(xx + 170.0/2, yy + 150.0/2);
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
}

void Human::draw()
{
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON); // FACE
    for (int i = 0; i < 360; i++)
    {
        this->theta = i * 3.14159 / 180;
        glVertex2f(x + 150/2 + cos(this->theta) * 30/2, y + 200/2 + sin(this->theta) * 30/2);
    }
    glEnd();

    glLineWidth(5); // BODY
    glBegin(GL_LINES);
    glVertex2d(x + 150.0/2, y + 130.0/2);
    glVertex2d(x + 150.0/2, y + 170.0/2);
    glEnd();

    glBegin(GL_LINE_STRIP); // LEGS
    glVertex2d(x + 130.0/2, y + 100.0/2);
    glVertex2d(x + 150.0/2, y + 130.0/2);
    glVertex2d(x + 170.0/2, y + 100.0/2);
    glEnd();

    glBegin(GL_LINE_STRIP); // HANDS
    glVertex2d(x + 130.0/2, y + 150.0/2);
    glVertex2d(x + 150.0/2, y + 170.0/2);
    glVertex2d(x + 170.0/2, y + 150.0/2);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5);
    glBegin(GL_POINTS); // EYES
    glVertex2d(x + 135.0/2, y + 210.0/2);
    glVertex2d(x + 165.0/2, y + 210.0/2);
    glEnd();

    // std::cout<<"\nClass method is executed";

}

Platforms::Platforms(int xx1, int yy1, int xx2, int yy2)
{
    this->x1 = xx1;
    this->y1 = yy1;
    this->x2 = xx2;
    this->y2 = yy2;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x2 - 10, y2 + 5);
    glVertex2f(x1 + 10, y1 + 5);
    glEnd();
}