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
class Shape {
private:
	int NumSides; // Number of Polygon Sides
	RGBColor color; //Shape color
	Location origin; //center of the shape
	GLint drawMode; //drawing mode
	Location* vertices; // array of vertices for the shape

public:
	//constructors
	Shape() {
		NumSides = 1;
	}
	Shape(int numSides, RGBColor color, Location origin, GLint drawMode) {
		NumSides = numSides;
		this->color = color;
		this->origin = origin;
		this->drawMode = drawMode;
	}

	//set methods
	void setSides(int numSides) {
		NumSides = numSides;
	}
	void setColor(RGBColor color) {
		this->color = color;
	}
	void setOrigin(Location origin) {
		this->origin = origin;
	}
	void setDrawMode(GLint drawMode) {
		this->drawMode = drawMode;
	}
	void setVertex(int index, Location l) {
		vertices[index] = l;
	}
	void setVertices(int size) {
		vertices[size];
	}

	//get Methods
	int getSides() {
		return NumSides;
	}
	RGBColor getColor() {
		return color;
	}
	GLint getDrawMode() {
		return drawMode;
	}
	Location* getVertices() {
		return sizeof(vertices) / sizeof(vertices[0]);
	}
};