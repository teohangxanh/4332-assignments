#include <GL/glut.h>
#include "Location.h"
#include "RGBColor.h"

/*************************************************************************
Class:		Checkerboard class 
Purpose:	Provide a Red/White 8x8 checkerboard
Author https://cs.lmu.edu/~ray/notes/openglexamples/ as modified by Cooper
Date:	3/2/2020
************************************************************************/

class Checkerboard {
private:
    GLint displayListId;        //  List of individual tiles
    GLint width;               //    width and depth of checkboard in tile units
    GLint depth;
public:
    Checkerboard();
    Checkerboard(GLint width, GLint depth);

    // Locate the center of the checkboard for the camera
    double centerx();
    double centerz();

    // Create and draw checkerboard
    void create();
    void draw();
};
