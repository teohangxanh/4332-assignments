#include "Surface.h"
#include "RGBColor.h"


/*************************************************************************
Class:		Surface class implementation
Purpose:	Provide floor and wall
Author      Ted, using https://cs.lmu.edu/~ray/notes/openglexamples/ as an inital base
Date:	    04/03/2020

Note:       Implementation uses existing Location, RGBColor classes rather than primitives
************************************************************************/

//Constructors.  For the moment, only the default constructor is used
Surface::Surface() { width = 20, length = 20, depth = 20; displayListId = 0; }
Surface::Surface(GLint w, GLint l, GLint d) { width = w; length = l; depth = d; displayListId = 0; }

//get the center of the board for the camera
double Surface::centerx() { return width / 2; }
double Surface::centery() { return length / 2; }
double Surface::centerz() { return depth / 2; }

//  construct the surface
void Surface::create() {
    RGBColor yellow(1, 1, 0);
    RGBColor black(0, 0, 0);
    GLfloat YELLOW[3] = { yellow.getRed(),yellow.getGreen(),yellow.getBlue() };
    GLfloat BLACK[3] = { black.getRed(),black.getGreen(),black.getBlue() };
    displayListId = glGenLists(1);
    glNewList(displayListId, GL_COMPILE);
    GLfloat lightPosition[] = { 4, 3, 7, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    for (int x = 0; x < width - 1; x++) {
        for (int z = 0; z < depth - 1; z++) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                (x + z) % 2 == 0 ? YELLOW : BLACK);
            glVertex3d(x, 0, z);
            glVertex3d(x + 1.0, 0, z);
            glVertex3d(x + 1.0, 0, z + 1.0);
            glVertex3d(x, 0, z + 1.0);
        }
    }
    glEnd();
    glEndList();
}

void Surface::trans_and_rot(GLfloat transx, GLfloat transy, GLfloat transz, GLfloat rotx, GLfloat roty, GLfloat rotz)
{
    glPushMatrix();
    glTranslatef(transx, transy, transz);
    glRotatef(rotx, roty, rotz, 0);

    create();
    glPopMatrix();
}

//  support function for create to identify the tile list
void Surface::draw() {
    glCallList(displayListId);
}