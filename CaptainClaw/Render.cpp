#include <GL/freeglut.h>
#include <math.h>
extern int yy, xx;

void drawPlatforms(int x1, int y1, int x2, int y2)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x2 - 10, y2 + 5);
    glVertex2f(x1 + 10, y1 + 5);
    glEnd();
}

void human()
{
    glColor3f(1.0, 0.0, 0.0);

    float theta;
    glBegin(GL_POLYGON); // FACE
    for (int i = 0; i < 360; i++)
    {
        theta = i * 3.14159 / 180;
        glVertex2f(xx + 150 + cos(theta) * 30, yy + 200 + sin(theta) * 30);
    }
    glEnd();

    glLineWidth(5.0); // BODY
    glBegin(GL_LINES);
    glVertex2d(xx + 150.0, yy + 130.0);
    glVertex2d(xx + 150.0, yy + 170.0);
    glEnd();

    glBegin(GL_LINE_STRIP); // LEGS
    glVertex2d(xx + 130.0, yy + 100.0);
    glVertex2d(xx + 150.0, yy + 130.0);
    glVertex2d(xx + 170.0, yy + 100.0);
    glEnd();

    glBegin(GL_LINE_STRIP); // HANDS
    glVertex2d(xx + 130.0, yy + 150.0);
    glVertex2d(xx + 150.0, yy + 170.0);
    glVertex2d(xx + 170.0, yy + 150.0);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS); // EYES
    glVertex2d(xx + 135.0, yy + 210.0);
    glVertex2d(xx + 165.0, yy + 210.0);
    glEnd();

}