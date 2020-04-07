#define _OBJECT_
#include "RGBColor.h"
#include <vector>

using namespace std;

/*************************************
Function:   Object class file
Purpose:    create an object
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/ as modified to incorporate RGBColor class
Date:   04/03/2020
*************************************/
class Object {
    RGBColor color;
    vector<GLfloat[1][3]> dimension;

public:
    Object(RGBColor c, vector<GLfloat[1][3]> d);
    
    //  member set methods
    void setColor(RGBColor);
    void setDimension(vector<GLfloat[1][3]> d);

    //      member get methods
    RGBColor getColor();
    vector<GLfloat[1][3]> getDimension();
};