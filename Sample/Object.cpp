#ifndef _OBJECT_
#include "Object.h"
#endif

/*************************************
Function:   Object class file
Purpose:    create an object
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/ as modified to incorporate RGBColor class
Date:   04/03/2020
*************************************/

Object::Object(RGBColor c, vector<GLfloat[3]> d) {
	this->color = c;
	this->dimension = dimension;
}

//  member set methods
void Object::setColor(RGBColor c) {
	this->color = c;
}
void Object::setDimension(vector<GLfloat[3]> d) {
	this->dimension = dimension;
}

//      member get methods
RGBColor Object::getColor() {
	return color;
}
vector<GLfloat[3]> Object::getDimension() {
	return dimension;
}

void Object::create() {
    glNewList(glGenLists(1), GL_COMPILE);
    GLfloat lightPosition[] = { 4, 3, 7, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glNormal3d(0, 1, 0);
    for (int i = 0; i < dimension.size(); i++) {
        if (i % 4 == 0) {
            glBegin(GL_QUADS);
        }
        GLfloat x = this->dimension[i][0];
        GLfloat y = this->dimension[i][1];
        GLfloat z = this->dimension[i][2];
        glVertex3f(x, y, z);
        if (i % 4 == 3) {
            glEnd();
        }
    }
    glEnd();
    glEndList();
}

void Object::trans_and_rot(GLfloat transx, GLfloat transy, GLfloat transz, GLfloat rotx, GLfloat roty, GLfloat rotz)
{
    glPushMatrix();
    glTranslatef(transx, transy, transz);
    glRotatef(rotx, roty, rotz, 0);
    create();
    glPopMatrix();
}

//  support function for create to identify the tile list
void Object::draw() {
    glCallList(glGenLists(1));
}