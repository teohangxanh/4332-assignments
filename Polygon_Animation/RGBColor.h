#pragma once 
#include <gl/GL.h>
#include <GL/glew.h>
#ifndef _RGBCOLOR_ 
#define RGBCOLOR_ 
#endif 

/********************************************
Class: RGBColor.h
Author: Cooper
Purpose: hold class structure information
Created: 02/12/2020
Dependencies: none
*********************************************/

class RGBColor {
private: 
	double red; 
	double green; 
	double blue;

public:
	//constructors 
	RGBColor(); //sets to black 
	RGBColor(double red, double green, double blue);

	//set Methods 
	void setRed(double red); //set individual colors 
	void setBlue(double blue);
	void setGreen(double green);
	void setColors(double red, double green, double blue); // set all the colors 

	// get methods 
	double getRed();
	double getBlue();
	double getGreen();
	RGBColor* getColors(); //gets a color object
};
