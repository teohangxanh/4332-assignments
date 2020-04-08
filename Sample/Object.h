#define _OBJECT_
#include "RGBColor.h"
#include <vector>

using namespace std;

/*************************************
Function:   Object class file
Purpose:    create an object
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/ as modified by Ted to incorporate RGBColor class
Date:   04/03/2020
*************************************/
class Object {
    RGBColor color;
    vector<GLfloat[3]> dimension;

public:
    Object(RGBColor c, vector<GLfloat[3]> d);
    
    //  member set methods
    void setColor(RGBColor);
    void setDimension(vector<GLfloat[3]> d);

    //      member get methods
    RGBColor getColor();
    vector<GLfloat[3]> getDimension();

    void create();
    void trans_and_rot(GLfloat transx, GLfloat transy, GLfloat transz, GLfloat rotx, GLfloat roty, GLfloat rotz);

    //  support function for create to identify the tile list
    void draw();
};