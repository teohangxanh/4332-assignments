//#include <gl/GL.h>
#include <GL/glew.h>
#include "RGBColor.h"
#include "Location.h"
#include <vector>
using namespace std;
#ifndef Shape_H 
#define Shape_H 

/********************************************
Class: Shape.h
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
	vector<Location> vertices;

public:
	//constructors
	Shape();
	Shape(int numSides, RGBColor color, Location origin, GLint drawMode);

	//set methods
	void setSides(int numSides);
	void setColor(RGBColor color);
	void setOrigin(Location origin);
	void setDrawMode(GLint drawMode);
	void setVertex(int index, Location l);
	void setVertices(int size);

	//get Methods
	int getSides();
	RGBColor getColor();
	GLint getDrawMode();
	vector<Location> getVertices();
};
#endif 