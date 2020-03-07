#include "RGBColor.h"
#include "Shape.h"
#include "Location.h"
 
/********************************************
Class: Shape.cpp
Author: Ted Dang
Purpose: hold shape structure information
Created: 03/01/2020
Dependencies: none
*********************************************/

//constructors
Shape::Shape() {
	NumSides = 1;
}

Shape::Shape(int numSides, RGBColor color, Location origin, GLint drawMode) {
	NumSides = numSides;
	this->color = color;
	this->origin = origin;
	this->drawMode = drawMode;
}

//set methods
void Shape::setSides(int numSides) {
	NumSides = numSides;
}

void Shape::setColor(RGBColor color) {
	this->color = color;
}

void Shape::setOrigin(Location origin) {
	this->origin = origin;
}

void Shape::setDrawMode(GLint drawMode) {
	this->drawMode = drawMode;
}

void Shape::setVertex(int index, Location l) {
	vertices[index] = l;
}

void Shape::setVertices(int size) {
	vertices[size];
}

//get Methods
int Shape::getSides() {
	return NumSides;
}

RGBColor Shape::getColor() {
	return color;
}

GLint Shape::getDrawMode() {
	return drawMode;
}

Location* Shape::getVertices() {
	return vertices;
}
