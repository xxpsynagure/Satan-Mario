#pragma once
//void drawPlatforms(int x1, int y1, int x2, int y2);
//void human();


class Human
{
private:
    /* data */
public:
    GLfloat x, y, theta;
    Human(int, int);
    // ~Human();
    void draw();
};

class Platforms
{
private:
    /* data */
public:
    GLint x1, y1, x2, y2;
    Platforms(int, int , int , int);
    // ~Platforms();
};


