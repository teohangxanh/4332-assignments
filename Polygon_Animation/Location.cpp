#include "Location.h"

/********************************************
Class: Location.cpp
Author: Ted Dang
Purpose: hold location structure information
Created: 03/01/2020
Dependencies: none
*********************************************/
class Location {
private:
	double cord_x;
	double cord_y;
	double cord_z;

public:
	//constructors
	Location() // sets to (0, 0)
	{
		cord_x = 0;
		cord_y = 0;
		cord_z = 0;
	}

	Location(double x, double y) // 2D
	{
		cord_x = x;
		cord_y = y;
	}
	Location(double x, double y, double z) // 3D
	{
		cord_x = x;
		cord_y = y;
		cord_z = z;
	}
	//set methods
	void setX(double x) {
		cord_x = x;
	}
	void setY(double y) {
		cord_y = y;
	}
	void setZ(double z) {
		cord_z = z;
	}

	//get Methods
	double getX() {
		return cord_x;
	}
	double getY() {
		return cord_y;
	}
	double getZ() {
		return cord_z;
	}
};