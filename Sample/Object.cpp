#ifndef _OBJECT_
#include "Object.h"
#endif

/*************************************
Function:   Object class file
Purpose:    create an object
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/ as modified to incorporate RGBColor class
Date:   04/03/2020
*************************************/

Object::Object(RGBColor c, vector<GLfloat[1][3]> d) {
	this->color = c;
	this->dimension = dimension;
}

//  member set methods
void Object::setColor(RGBColor) {
	this->color = c;
}
void Object::setDimension(vector<GLfloat[1][3]> d) {
	this->dimension = dimension;
}

//      member get methods
RGBColor Object::getColor() {
	return color;
}
vector<GLfloat[1][3]> Object::getDimension() {
	return dimension;
}