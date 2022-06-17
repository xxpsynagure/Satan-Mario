#include <Windows.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>

int xx = 0;
int yy = 800;
GLint width1, height1;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0.0, (GLdouble)width1, 0.0, (GLdouble)height1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}
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


void fallDown(int value)
{
    yy -= 0.0005;
    glutTimerFunc(30, fallDown, 0);
    glutPostRedisplay();
}

void specialkey(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP: yy += 20;
        break;
    case GLUT_KEY_DOWN: yy -= 5;
        break;
    case GLUT_KEY_LEFT: xx -= 5;
        break;
    case GLUT_KEY_RIGHT: xx += 5;
        break;
    case 27: exit(0);
    default: yy--;
    }
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlatforms(100, 100, 300, 100);
    drawPlatforms(400, 550, 600, 550);
    drawPlatforms(900, 320, 1150, 320);

    human();

    glFlush();
    // glutPostRedisplay();
    glutSwapBuffers();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    width1 = glutGet(GLUT_SCREEN_WIDTH);
    height1 = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowSize(width1, height1);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Captain's Claw's Quest");
    glutFullScreen();
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialkey);
    glutKeyboardFunc(keyPressed);
    glutReshapeFunc(reshape);
    if (yy > 200)
        glutTimerFunc(0, fallDown, 0);
    glutMainLoop();
    return 0;
}

