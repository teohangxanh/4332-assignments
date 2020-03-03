#include "RGBColor.h"

/********************************************
Class: RGBColor.cpp
Author: Ted Dang
Purpose: hold class structure information
Created: 03/02/2020
Dependencies: none
*********************************************/

class RGBColor {
private:
	double red;
	double green;
	double blue;

public:
	//constructors 
	RGBColor() //sets to black 
	{
		red = 0;
		green = 0;
		blue = 0;
	}

	RGBColor(double red, double green, double blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	//set Methods 
	void setRed(double red) //set individual colors 
	{
		this->red = red;
	}

	void setBlue(double blue) {
		this->blue = blue;
	}

	void setGreen(double green) {
		this->green = green;
	}

	void setColors(double red, double green, double blue) // set all the colors 
	{
		this->red = red;
		this->blue = blue;
		this->green = green;
	}

	// get methods 
	double getRed() {
		return red;
	}

	double getBlue() {
		return blue;
	}

	double getGreen() {
		return green;
	}

	RGBColor* getColors() //gets a color object
	{
		return new RGBColor();
	}
};