#pragma once
//void drawPlatforms(int x1, int y1, int x2, int y2);
//void human();


class Human
{
private:
    /* data */
public:
    GLfloat x, y, theta;
    struct Position
    {
        GLfloat x, y;
    };
    Position bottomLeft, bottomRight, topRight, topLeft;
    // Human();
    Human(int, int);
    // ~Human();
    void draw();
};

class Platforms
{
private:
    /* data */
public:
    struct Position{
        GLfloat x, y;
    };
    Position bottomLeft, bottomRight, topRight, topLeft;

    // Platforms();
    Platforms(int, int , int , int);
    // ~Platforms();
};




