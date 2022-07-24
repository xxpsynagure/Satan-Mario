#include <GL/freeglut.h>
#include <math.h>
#include "Render.h"
extern int yy, xx, goWhereFlag;

void Human::init(int xx, int yy)
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

Ladder::Ladder(int x, int y)
{
    if (x > 780)
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
    if (x < 780)
    {
        this->bottomLeft.x = 50;
        this->bottomLeft.y = 58;
        this->bottomRight.x = 90;
        this->bottomRight.y = 58;
        this->topRight.x = 90;
        this->topRight.y = 480;//480
        this->topLeft.x = 50;
        this->topLeft.y = 480;//480
    }
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

Thorns::Thorns(int xs, int ns)
{ 
    this->x = xs;
    this->n = ns;
    glColor3f(0.50, 0.50, 0.50);
    for(int i=0; i<n; i++)
    {
        glBegin(GL_TRIANGLES);
        glVertex2f(x, 0);
        glVertex2f(x-8, 55);
        glVertex2f(x-16, 0);
        glEnd();
        x -= 16;
    }  
}

void Diamonds::init(int x, int y)
{
    this->bottom.x = x;
    this->bottom.y = y;
    this->right.x = x + 10;
    this->right.y = y + 18;
    this->top.x = x;
    this->top.y = y + 36;
    this->left.x = x - 10;
    this->left.y = y + 18;
}
void Diamonds::draw()
{
    glColor3f(0.392, 0.584, 0.929); 
    glBegin(GL_QUADS);
    glVertex2f(bottom.x, bottom.y);
    glVertex2f(right.x, right.y);
    glVertex2f(top.x, top.y);
    glVertex2f(left.x, left.y);
    glEnd();

}


void Thornsinv::init(int xs, int ys = 940)
{
    this->x = xs;
    this->y = ys;
}
void Thornsinv::draw()
{
    glColor3f(0.50, 0.50, 0.50);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + 8, y-55);
    glVertex2f(x + 16, y);
    glEnd();
}