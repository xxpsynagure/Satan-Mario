#pragma once
//void drawPlatforms(int x1, int y1, int x2, int y2);
//void human();


class Human
{
private:
    /* data */
public:
    GLfloat x=30, y=940, theta;
    struct Position
    {
        GLfloat x, y;
    };
    Position bottomLeft, bottomRight, topRight, topLeft;
    // Human();
    //Human(int, int);
    ~Human(){}
    void init(int,int);
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
    ~Platforms(){}
};

class Ladder{
private:
    /* data */
public:
    struct Position{
        GLfloat x, y;
    };
    Position bottomLeft, bottomRight, topRight, topLeft;

    Ladder(int, int);
    ~Ladder(){}

    void draw();
};

class Blocks
{
private:
    /* data */
public:
    struct Position{
        GLfloat x, y;
    };
    Position bottomLeft;
    
    Blocks(int, int);
    ~Blocks(){}
};

class Thorns{
private:
    /* data */
public:
    GLfloat x, n;
    Thorns(int, int);
    ~Thorns(){}

};

class Thornsinv {
public:
    GLfloat x=0, y=940;
    void init(int,int);
    void draw();
};


class Diamonds{
private:
    /* data */
public:
    struct Position{
        GLfloat x, y;
    };
    Position bottom, right, top, left;
    int enabled = 1;

    void init(int, int);
    void draw();

};


