#include "checkerboard.h"
#include "RGBColor.h"


/*************************************************************************
Class:		Checkboard class implementation
Purpose:	Provide a Red/White 8x8 checkerboard
Author https://cs.lmu.edu/~ray/notes/openglexamples/ as modified by Cooper
Date:	3/2/2020
************************************************************************/

//Constructors.  For the moment, only the default constructor is used
Checkerboard::Checkerboard() { width = 8, depth = 8; displayListId = 0; }
Checkerboard::Checkerboard(GLint w, GLint d) { width = w;	depth = d; displayListId = 0; }

//get the center of the board for the camera
double Checkerboard::centerx() { return width / 2; }
double Checkerboard::centerz() { return depth / 2; }

//  construct the checkerboard
void Checkerboard::create() {
    RGBColor red(1, 0, 0);
    RGBColor white(1, 1, 1);
    GLfloat RED[3] = { red.getRed(),red.getGreen(),red.getBlue() };
    GLfloat WHITE[3] = { white.getRed(),white.getGreen(),white.getBlue() };
    displayListId = glGenLists(1);
    glNewList(displayListId, GL_COMPILE);
    GLfloat lightPosition[] = { 4, 3, 7, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    for (int x = 0; x < width - 1; x++) {
        for (int z = 0; z < depth - 1; z++) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                (x + z) % 2 == 0 ? RED : WHITE);
            glVertex3d(x, 0, z);
            glVertex3d(x+1.0, 0, z);
            glVertex3d(x+1.0, 0, z+1.0);
            glVertex3d(x, 0, z+1.0);
        }
    }
    glEnd();
    glEndList();
}

//  support function for create to identify the tile list
void Checkerboard::draw() {
    glCallList(displayListId);
}