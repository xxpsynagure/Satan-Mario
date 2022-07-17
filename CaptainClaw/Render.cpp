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

    glBegin(GL_TRIANGLES); // HORNS
    glVertex2f(x - 15, y + 115);
    glVertex2f(x - 12.5, y + 130);
    glVertex2f(x - 10, y + 115);
    glEnd();
    glBegin(GL_TRIANGLES); // HORNS
    glVertex2f(x + 15, y + 115);
    glVertex2f(x + 12.5, y + 130);
    glVertex2f(x + 10, y + 115);
    glEnd();

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

Ladder::Ladder(int x, int y)
{
    this->bottomLeft.x = 1460;
    this->bottomLeft.y = 560;
    this->bottomRight.x = 1500;
    this->bottomRight.y = 560;
    this->topRight.x = 1500;
    this->topRight.y = 980;
    this->topLeft.x = 1460;
    this->topLeft.y = 980;
}

void Ladder::draw()
{
    // std::cout<<"i am drawing ladder";
    glLineWidth(5.0);
    glColor3f(0.5, 0.35, 0.05);
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y);
    glVertex2d(bottomLeft.x, bottomLeft.y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topRight.x, topRight.y);
    glVertex2d(bottomRight.x, bottomRight.y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-40);
    glVertex2d(topRight.x, topRight.y-40);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-80);
    glVertex2d(topRight.x, topRight.y-80);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-120);
    glVertex2d(topRight.x, topRight.y-120);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-160);
    glVertex2d(topRight.x, topRight.y-160);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-200);
    glVertex2d(topRight.x, topRight.y-200);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-240);
    glVertex2d(topRight.x, topRight.y-240);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-280);
    glVertex2d(topRight.x, topRight.y-280);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-320);
    glVertex2d(topRight.x, topRight.y-320);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-360);
    glVertex2d(topRight.x, topRight.y-360);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(topLeft.x, topLeft.y-400);
    glVertex2d(topRight.x, topRight.y-400);
    glEnd();
}

Blocks::Blocks(int x, int y)
{
    this->bottomLeft.x = x;
    this->bottomLeft.y = y;

    glColor3f(0.360, 0.235, 0.003);
    glBegin(GL_QUADS);
    glVertex2f(bottomLeft.x, bottomLeft.y);
    glVertex2f(bottomLeft.x+20, bottomLeft.y);
    glVertex2f(bottomLeft.x+20, bottomLeft.y+30);
    glVertex2f(bottomLeft.x, bottomLeft.y+30);
    glEnd();
    
}
