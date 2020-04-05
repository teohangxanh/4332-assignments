#include <GL/glut.h>
#include "Location.h"
#include "RGBColor.h"

/*************************************************************************
Class:		Surface class
Purpose:	Provide a surface
Author https://cs.lmu.edu/~ray/notes/openglexamples/ as modified by Ted
Date:	04/03/2020
************************************************************************/

class Surface {
private:
    GLint displayListId;        //  List of individual tiles
    GLint width;               //    dimensions of the surface
    GLint length;
    GLint depth;
public:
    Surface();
    Surface(GLint width, GLint length, GLint depth);

    // Locate the center of the floor for the camera
    double centerx();
    double centery();
    double centerz();

    // Create and draw floor
    void create();
    void draw();
};
