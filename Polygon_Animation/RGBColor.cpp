#include "RGBColor.h"

/********************************************
Class: RGBColor.cpp
Author: Ted Dang
Purpose: hold class structure information
Created: 03/02/2020
Dependencies: none
*********************************************/

//constructors 
RGBColor::RGBColor() //sets to black 
{
	red = 0;
	green = 0;
	blue = 0;
}

RGBColor::RGBColor(double red, double green, double blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
}

//set Methods 
void RGBColor::setRed(double red) //set individual colors 
{
	this->red = red;
}

void RGBColor::setBlue(double blue) {
	this->blue = blue;
}

void RGBColor::setGreen(double green) {
	this->green = green;
}

void RGBColor::setColors(double red, double green, double blue) // set all the colors 
{
	this->red = red;
	this->blue = blue;
	this->green = green;
}

// get methods 
double RGBColor::getRed() {
	return red;
}

double RGBColor::getBlue() {
	return blue;
}

double RGBColor::getGreen() {
	return green;
}

RGBColor* getColors() //gets a color object
{
	return new RGBColor();
}