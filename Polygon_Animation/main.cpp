#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include "Shape.h"
#include "Location.h"
#include "RGBColor.h"
using namespace std;

static bool spinning = true; //animated or not 
static const int FPS = 60; //frames to render 
Location origin(25, 25); // point coordinate 
RGBColor currentColor(0.9, 0.1, 0.1); // color 
Location* vertices; // array of vertices for the shape 
Shape myShape(6, currentColor, origin, GL_POLYGON); // create a new shape 
static GLfloat currentAngleOfRotation = 0.0; // rotation angle

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
    myShape.setVertices(25);
    vertices = myShape.getVertices();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); //setup 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(currentAngleOfRotation, 0.0, 0.0, 1.0); // rotate the shape 
    myShape.setVertices(25); // set the vertices of the shape
    myShape.setOrigin(origin); // set the origin of the shape 
    vertices = myShape.getVertices(); // put the vertices in an array 
    glBegin(GL_POLYGON); // and draw it 
    glColor3f(currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
    for (int i = 0; i < myShape.getSides(); i++) {
        glVertex2f(vertices[i].getX(), vertices[i].getY());
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}

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
    case 'r': currentColor.setColors(1.0, 0.0, 0.0); break;
    case 'b': currentColor.setColors(0.0, 0.0, 1.0); break;
    case 'g': currentColor.setColors(0.0, 1.0, 0.0);
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
    case GLUT_KEY_F3: glutIconifyWindow(); break;
    }
}

/*********************************
function: main() purpose: sets up the window and assigns keyboard and mouse listeners, sets the frame rate for animation, and shape aspect ratio
Author: Cooper
Date: 2/21/2020
*********************************/
int main(int argc, char** argv) {
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Spinning Shape");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMouseFunc(mouse); glutMainLoop();
}

