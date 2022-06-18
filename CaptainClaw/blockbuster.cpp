/*
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<GL/glut.h>
#include<random>
#include<vector>
#include<thread>
#include<chrono>
#include<string>
#include<conio.h>
#include "stb_image.h"
//#include<irrKlang.h>

//using namespace irrklang;
using std::vector;
unsigned char* data;
#define GL_NORMAL_MAP 0x8511
#define GL_EYE_LINEAR 0x2400
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_CLAMP_TO_EDGE                        0x812F
#define GL_CLAMP                                0x2900
#define GL_CLAMP_TO_BORDER                      0x812D
int count = 1;
int score = 0;
unsigned int texture;
unsigned int bg;
unsigned int mbg;
bool startGenObs = false;
unsigned int ID;
short int dir = 0;
float rang = 0.0;
float th = 0;
float xShip = 0.0;
int BeamVecPoin = 0;
int obsVecPoin = 0;
const int maxObstacals = 15;
float obsSpeedFac = 13.5;
float beamSpeedFac = 7.0;
float rof = 1.0;
int playerHealth = 2;
bool firebeams;
bool shipcollision = false;
int shipnorenderframe = 10;
int shipnorenderframetime = 3;
const int maxExplosions = 15;
bool menuMusicPlaying = false;

float x, y;
int flag = 0;
float temp;
float xtemp, ytemp;

//irrklang::ISoundEngine* menumusic = irrklang::createIrrKlangDevice();
//irrklang::ISoundEngine* gamemusic = irrklang::createIrrKlangDevice();
//irrklang::ISoundEngine* beammusic = irrklang::createIrrKlangDevice();

enum state {
    start, quit, menu, highscore
}; // to define state of our game

typedef struct polygon
{
    bool over; 
    float x1, y1, x2, y2; 
    int xmin, xmax, ymin, ymax; 
} polygon;


state CurrentState = menu;


polygon polygons[4];
long selectedMenu = -1;


struct beam {
    float xBeam = 0.0;
    float yBeam = -565.00;
    float xhalsize = 4.8;
    float yhalsize = 12.0;
    bool renderBeam = false;
};

struct obstacal {
    float xObs = 0.0;
    float yObs = 610.0;
    float obsSize = 0.0;
    float obsRadius = 0.0;
    float x1 = 0.0;
    float x2 = 0.0;
    float eX = 0.0;
    float eY = 0.0;
    bool renderObs = false;
    bool state = true;
    int id;
};

struct explosionsXY {
    float expX = 0;
    float expY = 0;
};

std::vector<beam> Beams;
obstacal obs[maxObstacals];
explosionsXY explosions[maxExplosions];

void plasmaBeam(float xBeam, float yBeam);

void background() {
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, bg);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex2f(-1000.0, -680.0f);
    glTexCoord2f(0.0f, 1.0f);   glVertex2f(-1000.0, 680.0f);
    glTexCoord2f(1.0f, 1.0f);   glVertex2f(1000, 680.0f);
    glTexCoord2f(1.0f, 0.0f);   glVertex2f(1000, -680.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void menubackground() {
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, mbg);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex2f(-1000.0, -680.0f);
    glTexCoord2f(0.0f, 1.0f);   glVertex2f(-1000.0, 680.0f);
    glTexCoord2f(1.0f, 1.0f);   glVertex2f(1000, 680.0f);
    glTexCoord2f(1.0f, 0.0f);   glVertex2f(1000, -680.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void pick_polygon(long x, long y)
{
    int i;
    for (i = 0; i < 2; i++)
    {



        if ((y >= polygons[i].ymin) && (y < polygons[i].ymax) && (x >= polygons[i].xmin) && (x <= polygons[i].xmax))
        {
            selectedMenu = i;
            polygons[i].over = 1;
            break;

        }
        else
        {
            selectedMenu = -1;
            polygons[i].over = 0;
        }
    }

}

void myMouseAct() {

    if (selectedMenu == 0 & polygons[0].over == 1)
    {
        printf("start selected");
        CurrentState = start;
    }
    else if (selectedMenu == 1 & polygons[1].over == 1)
    {
        printf("restart selected");
        CurrentState = quit;
        exit(0);
    }

    //  std::cout << selectedMenu << std::endl;
    //  std::cout << polygons[0].over << std::endl;


}

void MouseMove(int x, int y)
{
    pick_polygon(x, y);
}

void InitMenu()
{


    polygons[0].xmin = 400;
    polygons[0].xmax = 570;
    polygons[0].ymin = 245;
    polygons[0].ymax = 300;

    polygons[1].xmin = 400;
    polygons[1].xmax = 570;
    polygons[1].ymin = 338;
    polygons[1].ymax = 393;

    polygons[0].x1 = -1;
    polygons[0].x2 = 2;
    polygons[0].y1 = 0;
    polygons[0].y2 = 0.75;

    polygons[1].x1 = -1;
    polygons[1].x2 = 2;
    polygons[1].y1 = -1.25;
    polygons[1].y2 = -0.5;


}

void DrawText(float x, float y, std::string text)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1, 1, 1);

    for (unsigned i = 0; i < text.length(); ++i)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text.at(i));
    }
    glPopMatrix();
}

void Menu()
{

    glPushMatrix();
    glScalef(0.75, 0.75, 0.75);
    std::string start = "Start";
    std::string qut = "Exit";
    glutPassiveMotionFunc(MouseMove);
    InitMenu();
    glColor3f(1.0, 1.0, 1.0);
    DrawText(-160, 180, start);
    DrawText(-160, -90, qut);
    glPopMatrix();
    if (!menuMusicPlaying) {
        //menumusic->play2D("menumusic.wav", true);
        menuMusicPlaying = true;
    }
}

void init(void)
{
    glClearColor(0.2, 0.0, 0.6, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0, 1000.0, -680.0, 680.0, -2000, 2000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void vaporize() {
    for (auto& it : Beams) {
        if (it.yBeam >= 620.00) {
            it.renderBeam = false;
        }
    }
    for (int i = 0; i < maxObstacals; i++) {
        if (obs[i].yObs <= -750.00) {
            obs[i].renderObs = false;
        }
    }
}

void firebeam() {
    while (firebeams) {
        //beammusic->play2D("beam.wav");
        if (BeamVecPoin == 99) BeamVecPoin = 0;
        Beams[BeamVecPoin].renderBeam = true;
        Beams[BeamVecPoin].xBeam = xShip;
        Beams[BeamVecPoin++].yBeam = -565.00;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void mouse(int button, int state, int x, int y) {

    if (CurrentState == menu) {
        if (state == GLUT_DOWN) {
            std::cout << "Mouse 1 pressed\n" << std::endl;

            if (button == GLUT_LEFT_BUTTON) {
                myMouseAct();
            }
        }
    }
    else {
        if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN and CurrentState != highscore) {
            firebeams = true;
            std::thread th_fb(firebeam);
            th_fb.detach();
        }
        else if (button == GLUT_LEFT_BUTTON and state == GLUT_UP)
        {
            firebeams = false;
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27)
    {
        playerHealth = 2;
        score = 0;
        CurrentState = menu;
    }
    if (key == 's')
    {
        printf("S key");
    }
    if (key == 'a' && xShip >= -995) {
        xShip -= 15;
        dir = -1;
    }
    if (key == 'd' && xShip <= 995) {
        xShip += 15;
        dir = 1;
    }

}

void keyboardUp(unsigned char key, int x, int y) {
    if (key == 'a') {
        dir = 0;
    }
    if (key == 'd') {
        dir = 0;
    }
}

void plasmaBeam(float xBeam, float yBeam) {

    glColor3f(1.0, 0.2, 0.3);
    glPushMatrix();
    glTranslatef(xBeam, yBeam, 0.0);
    glScalef(0.8, 2.0, 0.2);
    glutSolidSphere(6, 25, 25);
    yBeam += 1.0 * beamSpeedFac;
    glPopMatrix();
}

void fighter_ship(int dir) {//combine rotate into single if else block
    if (dir == 0)
    {
        if (rang > 0.0 && rang != 0.0) {
            rang -= 0.5;
        }
        else if (rang < 0.0 && rang != 0.0) {
            rang += 0.5;
        }
        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glTranslatef(xShip, -627.0, 20.0);
        glRotatef(rang, 0.0, 1.0, 0.0);
        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0, 0.0, 0.0);
        glScalef(2.0, 4.0, 1.0);
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidCube(20);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1.5, 2.0, 0.5);
        glTranslatef(0.0, -8.0, 27.0);
        glutSolidCube(15);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        //glColor3f(0.1, 0.0, 0.1);
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        //glColor3f(0.1, 0.0, 0.1);
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(-50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPopMatrix();
    }
    else if (dir == 1) {
        if (rang <= 30) rang += 0.5;
        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glTranslatef(xShip, -627.0, 20.0);
        glRotatef(rang, 0.0, 1.0, 0.0);
        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0, 0.0, 0.0);
        glScalef(2.0, 4.0, 1.0);
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidCube(20);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1.5, 2.0, 0.5);
        glTranslatef(0.0, -8.0, 27.0);
        glutSolidCube(15);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        //glColor3f(0.1, 0.0, 0.1);
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        //glColor3f(0.1, 0.0, 0.1);
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(-50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPopMatrix();
    }
    else if (dir == -1) {
        if (rang >= -30) rang -= 0.5;
        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glTranslatef(xShip, -627.0, 20.0);
        glRotatef(rang, 0.0, 1.0, 0.0);
        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0, 0.0, 0.0);
        glScalef(2.0, 4.0, 1.0);
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidCube(20);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1.5, 2.0, 0.5);
        glTranslatef(0.0, -8.0, 27.0);
        glutSolidCube(15);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        //glColor3f(0.1, 0.0, 0.1);
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        //glColor3f(0.1, 0.0, 0.1);
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(-50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPopMatrix();
    }
}

void obstacals(float xObs, float yObs, float obsSize) {
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture);
    glTranslatef(xObs, yObs, 0);
    // GLUquadricObj* sphere = gluNewQuadric();
    // gluSphere(sphere, 2.0 * obsSize, 25, 25);
    glutSolidSphere(2 * obsSize, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void explosion(float x, float y, int i) {
    glColor3f(0.5, 0.5, 0.5);
    glPointSize(10);
    if (y == obs[i].obsSize * 2.0) {
        obs[i].state = true;
        explosions[i].expX = 0;
        explosions[i].expY = 0;
    }
    glBegin(GL_POINTS);
    glVertex3f(obs[i].eX + (1.0 * x), obs[i].eY + (1.0 * y), 0.0);
    glVertex3f(obs[i].eX + (1.5 * x), obs[i].eY + (1.2 * y), 0.0);
    glVertex3f(obs[i].eX + (1.2 * x), obs[i].eY + (0.7 * y), 0.0);
    glVertex3f(obs[i].eX + (0.4 * x), obs[i].eY + (0.2 * y), 0.0);
    glVertex3f(obs[i].eX + (1.1 * x), obs[i].eY + (0.3 * y), 0.0);
    glVertex3f(obs[i].eX + (0.3 * x), obs[i].eY + (1.6 * y), 0.0);
    glVertex3f(obs[i].eX + (0.5 * x), obs[i].eY + (0.7 * y), 0.0);
    glVertex3f(obs[i].eX + (0.64 * x), obs[i].eY + (0.4 * y), 0.0);

    glVertex3f(obs[i].eX + (1.3 * x), obs[i].eY - (1.0 * y), 0.0);
    glVertex3f(obs[i].eX + (0.3 * x), obs[i].eY - (0.2 * y), 0.0);
    glVertex3f(obs[i].eX + (0.5 * x), obs[i].eY - (1.3 * y), 0.0);
    glVertex3f(obs[i].eX + (0.9 * x), obs[i].eY - (0.5 * y), 0.0);
    glVertex3f(obs[i].eX + (1.1 * x), obs[i].eY - (0.8 * y), 0.0);

    glVertex3f(obs[i].eX - (0.8 * x), obs[i].eY - (1.0 * y), 0.0);
    glVertex3f(obs[i].eX - (1.3 * x), obs[i].eY - (0.1 * y), 0.0);
    glVertex3f(obs[i].eX - (1.1 * x), obs[i].eY - (0.6 * y), 0.0);

    glVertex3f(obs[i].eX - (1.0 * x), obs[i].eY + (0.6 * y), 0.0);
    glVertex3f(obs[i].eX - (0.6 * x), obs[i].eY + (0.3 * y), 0.0);
    glVertex3f(obs[i].eX - (1.1 * x), obs[i].eY + (0.2 * y), 0.0);
    glVertex3f(obs[i].eX - (0.35 * x), obs[i].eY + (0.4 * y), 0.0);
    glVertex3f(obs[i].eX - (0.5 * x), obs[i].eY + (1.3 * y), 0.0);
    glEnd();
}

void generate_obs() {
    while (true) {
        if (CurrentState != start) {
            continue;
        }
        if ((!obs[obsVecPoin].renderObs) || obs[obsVecPoin].yObs < -750.0) {
            float xObsChoice[8] = { 0.0,240.0,560.0,-567.0,-100.0,-330.0,-800.0,760.0 };
            float obsSizeChoice[5] = { 20.0,10.0,40.0,30.0,25.0 };
            obs[obsVecPoin].xObs = xObsChoice[rand() % 12];
            obs[obsVecPoin].obsSize = obsSizeChoice[rand() % 5];
            obs[obsVecPoin].renderObs = true;
            obs[obsVecPoin].state = true;
            obs[obsVecPoin].id = obsVecPoin;
            obs[obsVecPoin].obsRadius = 2 * obs[obsVecPoin].obsSize;
            obs[obsVecPoin].x1 = obs[obsVecPoin].xObs - obs[obsVecPoin].obsRadius;
            obs[obsVecPoin].x2 = obs[obsVecPoin].xObs + obs[obsVecPoin].obsRadius;
            obs[obsVecPoin++].yObs = 610.0;
            if (obsVecPoin == maxObstacals) obsVecPoin = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else {
            obsVecPoin++;
            if (obsVecPoin == maxObstacals) obsVecPoin = 0;
            continue;

        }
    }
}

void update() {
    auto obsup = []() {
        for (int x = 0; x < maxObstacals; x++) {
            if (obs[x].renderObs) {
                obs[x].yObs -= (0.09 * obsSpeedFac);
            }
        }
    };
    auto expup = []() {
        for (int x = 0; x < maxExplosions; x++) {
            if (!obs[x].state) {
                explosions[x].expX += 0.5;
                explosions[x].expY += 0.5;
            }
        }
    };
    auto bemup = []() {
        for (int x = 0; x < Beams.size(); x++) {
            if (Beams[x].renderBeam == false)continue;
            if (Beams.size() > x) {
                Beams[x].yBeam += 1.0 * beamSpeedFac;
            }
        }
    };
    std::thread th_obs(obsup);
    std::thread th_exp(expup);
    std::thread th_bm(bemup);
    th_obs.join();
    th_exp.join();
    th_bm.join();
}

void collisiondetection_beam_obs() {
    for (int i = 0; i < maxObstacals; i++) {
        for (auto& it : Beams) {
            if ((obs[i].yObs - obs[i].obsRadius) < (it.yBeam + it.yhalsize) && it.renderBeam && obs[i].renderObs) {
                if ((obs[i].x1 < it.xBeam) && (obs[i].x2 > it.xBeam)) {
                    obs[i].renderObs = false;
                    obs[i].state = false;
                    obs[i].eX = obs[i].xObs;
                    obs[i].eY = obs[i].yObs;
                    it.renderBeam = false;
                    it.yBeam = -100000;
                    score++;
                    break;
                }
            }
        }
    }
}

void collisiondetection_ship() {
    for (int i = 0; i < maxObstacals; i++) {
        if ((obs[i].yObs - obs[i].obsRadius) < -585 && ((obs[i].yObs + obs[i].obsRadius) > -672) && obs[i].renderObs) {
            if ((68.0 + obs[i].obsRadius) > abs(xShip - obs[i].xObs)) {
                obs[i].renderObs = false;
                playerHealth--;
                if (playerHealth == 0)
                {
                    CurrentState = highscore;
                }
                shipcollision = true;
            }
        }
    }
}

void game()
{

    if (shipcollision) {
        if (shipnorenderframetime > 0) {
            if (shipnorenderframe > 0) {
                shipnorenderframe--;
            }
            else if (shipnorenderframe > -5) {
                fighter_ship(dir);
                shipnorenderframe--;
            }
            else {
                shipnorenderframe = 5;
                shipnorenderframetime--;
            }
        }
        else {
            shipcollision = false;
            shipnorenderframe = 10;
            shipnorenderframetime = 3;
        }
    }
    else {
        fighter_ship(dir);
    }


    for (int x = 0; x < maxObstacals; x++) {
        if (obs[x].renderObs) {
            obstacals(obs[x].xObs, obs[x].yObs, obs[x].obsSize);
        }
        if (!obs[x].state) {
            explosion(explosions[x].expX, explosions[x].expY, x);
        }
    }

    for (int x = 0; x < Beams.size(); x++) {
        if (Beams.size() > x && Beams[x].renderBeam) {
            plasmaBeam(Beams[x].xBeam, Beams[x].yBeam);
        }
    }

    collisiondetection_beam_obs();
    collisiondetection_ship();
    update();


    if (Beams.size() > 1) {
        std::thread th_vp(vaporize);
        th_vp.detach();
    }
    background();
    glDisable(GL_TEXTURE_2D);
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    if (CurrentState == menu)
    {
        Menu();
        menubackground();
        glDisable(GL_TEXTURE_2D);

    }
    else if (CurrentState == start)
    {
        if (menuMusicPlaying) {
            //menumusic->stopAllSounds();
            //gamemusic->play2D("gamemusic.ogg", true);
            menuMusicPlaying = false;
        }
        game();

    }
    else if (CurrentState == highscore)
    {
        if (!menuMusicPlaying) {
            //menumusic->play2D("menumusic.wav", true);
            //gamemusic->stopAllSounds();
            //menuMusicPlaying = true;
        }
        glPushMatrix();
        glScalef(0.75, 0.75, 0.75);
        std::string HIGH = "Score:";
        std::string points = std::to_string(score);
        glColor3f(1.0, 1.0, 1.0);
        DrawText(-250, 0, HIGH);
        DrawText(150, 0, points);
        glPopMatrix();
        menubackground();
        glDisable(GL_TEXTURE_2D);

    }

    glutSwapBuffers();
    glutPostRedisplay();


}

void LoadTexture()
{

    //BmpLoader bl(filename);
    //makeCheckImage();
    //glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &mbg);
    int width, height, nrChannels;
    unsigned char* data2 = stbi_load("Res/Textures/level1_background.png", &width, &height, &nrChannels, 0);
    glBindTexture(GL_TEXTURE_2D, mbg);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load menu background" << std::endl;
    }

    stbi_image_free(data2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    unsigned char* data = stbi_load("Res/Textures/level1_background.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &bg);
    unsigned char* data1 = stbi_load("Res/Textures/level1_background.png", &width, &height, &nrChannels, 0);
    glBindTexture(GL_TEXTURE_2D, bg);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load background" << std::endl;
    }

    stbi_image_free(data1);



}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 680);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("BlockBuster");
    init();
    LoadTexture();
    std::thread th_genObs(generate_obs);
    th_genObs.detach();
    Beams.resize(100);
    std::cout << glGetString(GL_VERSION);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}

*/
