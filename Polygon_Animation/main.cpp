#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <iostream>
#include <cmath>
#include <array>
#include "Shape.h"
#include "Location.h"
#include "RGBColor.h"
using namespace std;

static bool spinning = true; //animated or not 
static const int FPS = 60; //frames to render 
static GLfloat currentAngleOfRotation = 0.0; // rotation angle
Location origin(25, 25); // point coordinate 
RGBColor currentColor(0.9, 0.1, 0.1); // color 
vector<Location> vertices; // array of vertices for the shape 
Shape myShape(6, currentColor, origin, GL_POLYGON); // create a new shape 

int vp_width = 800;
int vp_height = 800;

array<int, 2> currentPt;
vector<array<int, 2>> pts;
bool closed = false;

void draw_polygon(int button, int state, int x, int y)
{
    currentPt = array<int, 2>{x, vp_height - y};

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (closed) pts.clear(); // restart if last action was close
        closed = false; // continue drawing polygon
        pts.push_back(currentPt); // store position of the mouse clicks into pts
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        // When you want to stop drawing the polygon, right click
        closed = true;
}

void mouse_move(int x, int y)
{
    currentPt = std::array<int, 2>{x, vp_height - y};
    glutPostRedisplay();
}

void display(void)
{
    //glClearColor(0.1, 0.1, 0.1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (!pts.empty())
    {
        glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        for (array<int, 2>& pt : pts) {
            glVertex2f((double)pt[0], (double)pt[1]);
        }
        // store the position of the next mouse click
        array<int, 2> endPt;
        if (closed) endPt = pts.front();
        else endPt = currentPt;
        glVertex2f((double)endPt[0], (double)endPt[1]);
        glEnd();
    }
    glRotatef(currentAngleOfRotation, 0.0, 0.0, 1.0); // rotate the shape 

    glFlush();
    glutSwapBuffers();
}


/********************************
Function: reshape
Purpose: maintain aspect ratio
Author: Cooper 
Date: 2/21/2020
*******************************/
void reshape(GLint width, GLint height) {
    glViewport(0, 0, width, height);
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width <= height) glOrtho(-50.0, 50.0, -50.0 / aspect, 50.0 / aspect, -1.0, 1.0);
    else glOrtho(-50.0 * aspect, 50.0 * aspect, -50.0, 50.0, -1.0, 1.0);
}

/********************************
function: init()
purpose: initialize the shape to be drawn and calculates the vertices of the shape
Author: Cooper
Date: 2/21/2020
**********************************/
void init() {
    myShape.setVertices(25); // set the vertices of the shape
    myShape.setOrigin(origin); // set the origin of the shape
    vertices = myShape.getVertices(); // put the vertices in an array 
}

//void display() {
//    glClear(GL_COLOR_BUFFER_BIT); //setup 
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glRotatef(currentAngleOfRotation, 0.0, 0.0, 1.0); // rotate the shape 
//    init();
//    // Arrange vertices to their right positions to form a polygon
//    double pi = 3.1415926535897932;
//    for (int i = 0; i < vertices.size(); i++) {
//        double angle = 2 * pi / vertices.size();
//        vertices[i].setX(origin.getX() + radius * sin(i * angle));
//        vertices[i].setY(origin.getY() + radius * sin(i * angle));
//    }
//    glBegin(GL_LINE_LOOP); // and draw it 
//    glColor3f(currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
//    for (int i = 0; i < myShape.getSides(); i++) {
//        glVertex2f(vertices[i].getX(), vertices[i].getY());
//    }
//    glEnd();
//    glFlush();
//    glutSwapBuffers();
//}

/*********************************
function: timer()
purpose: controls the refresh rate
Author: Cooper
Date: 2/21/2020
*********************************/
void timer(int v) {
    if (spinning) {
        currentAngleOfRotation += 1.0;
        if (currentAngleOfRotation > 360.0) {
            currentAngleOfRotation -= 360.0; // reset to zero every revolution 
        }
        glutPostRedisplay();
    }
    glutTimerFunc(1000 / FPS, timer, v);
}

/*********************************
function: mouse()
purpose: controls mouse behavior left click starts the image rotating right click pauses the rotation
Author: Cooper
Date: 2/21/2020
*********************************/
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        spinning = true;
        glutSetCursor(GLUT_CURSOR_DESTROY);
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        spinning = false;
        glutSetCursor(GLUT_CURSOR_WAIT);
    }
}

/*********************************
function: keyboard()
purpose: controls keyboard behavior number key 3-8 control number of sides keys r,g,b control shape color
Author: Cooper
Date: 2/21/2020
 *********************************/
void keyboard(unsigned char Key, int x, int y) {
    switch (Key) {
    case '3': myShape.setSides(3); break;
    case '4': myShape.setSides(4); break;
    case '5': myShape.setSides(5); break;
    case '6': myShape.setSides(6); break;
    case '7': myShape.setSides(7); break;
    case '8': myShape.setSides(8); break;
    case 's': spinning = true; break;
    case 'u': spinning = false; break;
    case 'r': currentColor.setColors(1.0, 0.0, 0.0); break;
    case 'b': currentColor.setColors(0.0, 0.0, 1.0); break;
    case 'g': currentColor.setColors(0.0, 1.0, 0.0); break;
    }
}

/*********************************
function: SpecialKeys()
purpose: controls non alphanumeric keys arrow keys up/down/left/right change window size
Author: Cooper
Date: 2/21/2020
*********************************/
void SpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH) - 1, glutGet(GLUT_WINDOW_HEIGHT)); break;
    case GLUT_KEY_RIGHT: glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH) + 1, glutGet(GLUT_WINDOW_HEIGHT)); break;
    case GLUT_KEY_UP: glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) + 1); break;
    case GLUT_KEY_DOWN:glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) - 1); break;
    case GLUT_KEY_F1: glutFullScreen(); break;
    case GLUT_KEY_F2: glutReshapeWindow(800, 800); break;
    case GLUT_KEY_F3: glutIconifyWindow(); break; // Hide the window 
    }
}

/*********************************
function: main() purpose: sets up the window and assigns keyboard and mouse listeners, sets the frame rate for animation, and shape aspect ratio
Author: Cooper
Date: 2/21/2020
*********************************/
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(vp_width, vp_height);
    glutCreateWindow("Group 6 - Polygon animation");
    //glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse_move);
    glutMouseFunc(draw_polygon);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0f, (float)vp_width, 0.0f, (float)vp_height, -1.0, 1.0);
    glutMainLoop();
}

