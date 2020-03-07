#include "Location.h"

/********************************************
Class: Location.cpp
Author: Ted Dang
Purpose: hold location structure information
Created: 03/01/2020
Dependencies: none
*********************************************/

//constructors
Location::Location() // sets to (0, 0)
{
	cord_x = 0;
	cord_y = 0;
	cord_z = 0;
}

Location::Location(double x, double y) // 2D
{
	cord_x = x;
	cord_y = y;
	cord_z = 0;
}
Location::Location(double x, double y, double z) // 3D
{
	cord_x = x;
	cord_y = y;
	cord_z = z;
}
//set methods
void Location::setX(double x) {
	cord_x = x;
}
void Location::setY(double y) {
	cord_y = y;
}
void Location::setZ(double z) {
	cord_z = z;
}

//get Methods
double Location::getX() {
	return cord_x;
}
double Location::getY() {
	return cord_y;
}
double Location::getZ() {
	return cord_z;
}