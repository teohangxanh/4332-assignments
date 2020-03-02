#pragma once
#include "RGBColor.h"
#ifndef _Location_ #define Location_ 
#endif 
/********************************************
Class: Location.h
Author: Ted Dang
Purpose: hold location structure information
Created: 03/01/2020
Dependencies: none
*********************************************/
class Location {
private:
	double cord_x = 0;
	double cord_y = 0;
	double cord_z = 0;

public:
	//constructors
	Location(); // sets to (0, 0)
	Location(double x, double y); // 2D
	Location(double x, double y, double z); // 3D

	//set methods
	void setX(double x);
	void setY(double y);
	void setZ(double z);

	//get Methods
	double getX();
	double getY();
	double getZ();
};