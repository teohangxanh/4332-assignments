
#include <windows.h>
#include "location.h"
#include "RGBColor.h"
#include "Object.h"
#include "Surface.h"
#include "Camera.h"
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

#define M_PI 3.1415926535897932384626433832795

/*************************************************************************
Class:		Surface class implementation
Purpose:	Provide floor and wall
Author      Ted, using https://cs.lmu.edu/~ray/notes/openglexamples/ as an inital base
Date:	    04/03/2020

Note:       Implementation uses existing Location, RGBColor classes rather than primitives
************************************************************************/
//  globals

//Ball balls[7];          //  seven balls in the example
Surface fl(20, 0, 20), wall1(20, 20, 0), wall2(0, 20, 20), wall3(0, 20, 20), ceiling = fl;
Camera camera;

//  set up colors.  Unfortunately a lot of the openGL calls use GLfloat so the RGBColor and Location information has to include a toGLFloat() function
RGBColor red(1, 0, 0);
RGBColor green(0, 1, 0);
RGBColor blue(0, 0, 1);
RGBColor cyan(0, 1, 1);
RGBColor magenta(1, 0, 1);
RGBColor yellow(1, 1, 0);
RGBColor white(1, 1, 1);
GLfloat WHITE[3], RED[3], GREEN[3], BLUE[3], MAGENTA[3], YELLOW[3], CYAN[3];
RGBColor colors[] = { red,green,blue,magenta,cyan,yellow, white };



/*************************************
Function:   init()
Purpose:    set up 3-D lighting
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/
Date:   3/2/2020
*************************************/
void init() {
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    fl.create();
    wall1.trans_and_rot(0, 0, -wall1.centerz(), 0, 0, M_PI / 2);
    wall2.trans_and_rot(0, -wall2.centerx(), 0, -M_PI / 2, 0, 0);
    wall3.trans_and_rot(0, wall3.centerx(), 0, 0, M_PI / 2, 0);
    ceiling.trans_and_rot(0, 2 * ceiling.centery(), 0, 0, 0, 0);
    Object toolbox(white, 
        {
        { 0, 0, 0 }, { 1, 0, 0 }, { 1, 3, 0 }, { 0, 3, 0 },
        { 1, 3, 0 }, { 0, 3, 0 }, { 0, 8, 2.5 }, { 1, 8, 2.5 },
        { 0, 8, 2.5 }, { 1, 8, 2.5 }, { 1, 8, 3 }, { 0, 8, 3 },
        { 1, 8, 3 }, { 0, 8, 3 }, { 0, 3, 5.5 }, { 1, 3, 5.5 },
        { 0, 3, 5.5 }, { 1, 3, 5.5 }, { 1, 0, 5.5 }, { 0, 0, 5.5 },
        { 0, 0, 0 }, { 0, 3, 0 }, { 0, 3, 5.5 }, { 0, 0, 5.5 },
        { 0, 3, 0 }, { 0, 3, 5.5 }, { 0, 8, 3 }, { 0, 8, 2.5 },

        { 11, 0, 0 }, { 12, 0, 0 }, { 12, 3, 0 }, { 11, 3, 0 },
        { 12, 3, 0 }, { 11, 3, 0 }, { 11, 8, 2.5 }, { 12, 8, 2.5 },
        { 11, 8, 2.5 }, { 12, 8, 2.5 }, { 12, 8, 3 }, { 11, 8, 3 },
        { 12, 8, 3 }, { 11, 8, 3 }, { 11, 3, 5.5 }, { 12, 3, 5.5 },
        { 11, 3, 5.5 }, { 12, 3, 5.5 }, { 12, 0, 5.5 }, { 11, 0, 5.5 },
        { 11, 0, 0 }, { 11, 3, 0 }, { 11, 3, 5.5 }, { 11, 0, 5.5 },
        { 11, 3, 0 }, { 11, 3, 5.5 }, { 11, 8, 3 }, { 11, 8, 2.5 },

        { 1, 0, 5.5 }, { 11, 0, 5.5 }, { 11, 3, 5.5 }, { 1, 3, 5.5 },
        { 1, 0, 4.5 }, { 11, 0, 4.5 }, { 11, 3, 4.5 }, { 1, 3, 4.5 },
        { 1, 3, 5.5 }, { 11, 3, 5.5 }, { 11, 3, 4.5 }, { 1, 3, 4.5 },
        { 1, 0, 1 }, { 11, 0, 1 }, { 11, 3, 1 }, { 1, 3, 1 },
        { 1, 0, 4.5 }, { 11, 0, 4.5 }, { 11, 3, 4.5 }, { 1, 3, 0 },
        { 1, 3, 0 }, { 11, 3, 0 }, { 11, 3, 0 }, { 1, 3, 0 }
        });
    toolbox.trans_and_rot(0, 0, 0, 0, 0, 0);

    Object chair(blue, 
        {
            {2, 0, 1}, {2.2, 0, 1}, {2.2, 0, 0.8}, {2, 0, 0.8},
            {2, 1, 1}, {2.2, 1, 1}, {2.2, 1, 0.8}, {2, 1, 0.8},
            {2, 0, 1}, {2, 0, 0.8}, {2, 1, 0.8}, {2, 1, 1},
            {2, 0.5, 1}, {2, 0.5, 0.8}, {2, 1.5, 0.8}, {2, 1.5, 1},
            {2, 0, 1}, {2.2, 0, 1}, {2.2, 1, 1}, {2, 1, 1},
            {2, 0, 0.5}, {2.2, 0, 0.5}, {2.2, 1, 0.5}, {2, 1, 0.5},

            {3.5, 0, 1}, {3.7, 0, 1}, {3.7, 0, 0.8}, {3.5, 0, 0.8},
            {3.5, 1, 1}, {3.7, 1, 1}, {3.7, 1, 0.8}, {3.5, 1, 0.8},
            {3.5, 0, 1}, {3.5, 0, 0.8}, {3.5, 1, 0.8}, {3.5, 1, 1},
            {3.5, 0.5, 1}, {3.5, 0.5, 0.8}, {3.5, 1.5, 0.8}, {3.5, 1.5, 1},
            {3.5, 0, 1}, {3.7, 0, 1}, {3.7, 1, 1}, {3.5, 1, 1},
            {3.5, 0, 0.5}, {3.7, 0, 0.5}, {3.7, 1, 0.5}, {3.5, 1, 0.5},

            {2, 0, -0.5}, {2.2, 0, -0.5}, {2.2, 0, -0.7}, {2, 0, -0.7},
            {2, 1, -0.5}, {2.2, 1, -0.5}, {2.2, 1, -0.7}, {2, 1, -0.7},
            {2, 0, -0.5}, {2, 0, -0.7}, {2, 1, -0.7}, {2, 1, -0.5},
            {2, 0.5, -0.5}, {2, 0.5, -0.7}, {2, 1.5, -0.7}, {2, 1.5, -0.5},
            {2, 0, -0.5}, {2.2, 0, -0.5}, {2.2, 1, -0.5}, {2, 1, -0.5},
            {2, 0, -1}, {2.2, 0, -1}, {2.2, 1, -1}, {2, 1, -1},

            {3.5, 0, -0.5}, {3.7, 0, -0.5}, {3.7, 0, -0.7}, {3.5, 0, -0.7},
            {3.5, 1, -0.5}, {3.7, 1, -0.5}, {3.7, 1, -0.7}, {3.5, 1, -0.7},
            {3.5, 0, -0.5}, {3.5, 0, -0.7}, {3.5, 1, -0.7}, {3.5, 1, -0.5},
            {3.5, 0.5, -0.5}, {3.5, 0.5, -0.7}, {3.5, 1.5, -0.7}, {3.5, 1.5, -0.5},
            {3.5, 0, -0.5}, {3.7, 0, -0.5}, {3.7, 1, -0.5}, {3.5, 1, -0.5},
            {3.5, 0, -1}, {3.7, 0, -1}, {3.7, 1, -1}, {3.5, 1, -1},

            {2, 1, 1}, {3.7, 1, 1}, {3.7, 1.2, 1}, {2, 1.2, 1},
            {2, 1, -0.5}, {3.7, 1, -0.5}, {3.7, 1.2, -0.5}, {2, 1.2, -0.5},
            {2, 1, 1}, {2, 1.2, 1}, {2, 1.2, -1.5}, {2, 1, -1.5},
            {3.7, 1, 1}, {3.7, 1.2, 1}, {3.7, 1.2, -1.5}, {3.7, 1, -1.5},
            {2, 1, 1}, {3.7, 1, 1}, {3.7, 1, -0.7}, {2, 1, -0.7},
            {2, 1.2, 1}, {3.7, 1.2, 1}, {3.7, 1.2, -0.7}, {2, 1.2, -0.7},

            {2, 1.2, -0.7}, {2.2, 1.2, -0.7}, {2.2, 3.7, -0.7}, {2, 3.7, -0.7},
            {2, 1.2, -0.9}, {2.2, 1.2, -0.9}, {2.2, 3.7, -0.9}, {2, 3.7, -0.9},
            {2, 1.2, -0.7}, {2, 3.7, -0.7}, {2, 3.7, -0.9}, {2, 1.2, -0.9},
            {2.2, 1.2, -0.7}, {2.2, 3.7, -0.7}, {2.2, 3.7, -0.9}, {2.2, 1.2, -0.9},
            {2, 1.2, -0.7}, {2.2, 1.2, -0.7}, {2.2, 1.2, -0.9}, {2, 1.2, -0.9},
            {2, 2.7, -0.7}, {2.2, 2.7, -0.7}, {2.2, 2.7, -0.9}, {2, 2.7, -0.9},

            {3.5, 1.2, -0.7}, {3.7, 1.2, -0.7}, {3.7, 3.7, -0.7}, {3.5, 3.7, -0.7},
            {3.5, 1.2, -0.9}, {3.7, 1.2, -0.9}, {3.7, 3.7, -0.9}, {3.5, 3.7, -0.9},
            {3.5, 1.2, -0.7}, {3.5, 3.7, -0.7}, {3.5, 3.7, -0.9}, {3.5, 1.2, -0.9},
            {3.7, 1.2, -0.7}, {3.7, 3.7, -0.7}, {3.7, 3.7, -0.9}, {3.7, 1.2, -0.9},
            {3.5, 1.2, -0.7}, {3.7, 1.2, -0.7}, {3.7, 1.2, -0.9}, {3.5, 1.2, -0.9},
            {3.5, 2.7, -0.7}, {3.7, 2.7, -0.7}, {3.7, 2.7, -0.9}, {3.5, 2.7, -0.9},

            {2.2, 2.4, -0.7}, {3.5, 2.4, -0.7}, {3.5, 2.7, -0.7}, {2.2, 2.7, -0.7},
            {2.2, 2.4, -0.9}, {3.5, 2.4, -0.9}, {3.5, 2.7, -0.9}, {2.2, 2.7, -0.9},
            {2.2, 2.4, -0.7}, {2.2, 2.4, -0.9}, {2.2, 2.7, -0.9}, {2.2, 2.7, -0.7},
            {2.2, 2.4, -0.7}, {2.2, 2.4, -0.9}, {2.2, 2.7, -0.9}, {2.2, 2.7, -0.7},
            {2.2, 2.4, -0.7}, {3.7, 2.4, -0.7}, {3.7, 2.4, -0.9}, {2.2, 2.4, -0.9},
            {2.2, 2.7, -0.7}, {3.7, 2.7, -0.7}, {3.7, 2.7, -0.9}, {2.2, 2.7, -0.9},

            {2.2, 1.9, -0.7}, {3.5, 1.9, -0.7}, {3.5, 2.2, -0.7}, {2.2, 2.2, -0.7},
            {2.2, 1.9, -0.9}, {3.5, 1.9, -0.9}, {3.5, 2.2, -0.9}, {2.2, 2., -0.9},
            {2.2, 1.9, -0.7}, {2.2, 1.9, -0.9}, {2.2, 2.2, -0.9}, {2.2, 2.2, -0.7},
            {2.2, 1.9, -0.7}, {2.2, 1.9, -0.9}, {2.2, 2.2, -0.9}, {2.2, 2.2, -0.7},
            {2.2, 1.9, -0.7}, {3.7, 1.9, -0.7}, {3.7, 1.9, -0.9}, {2.2, 1.9, -0.9},
            {2.2, 2.2, -0.7}, {3.7, 2.2, -0.7}, {3.7, 2.2, -0.9}, {2.2, 2.2, -0.9}
        });
    chair.trans_and_rot(0, 0, 0, 0, 0, 0);

    Object desk(white,
        { 
            {1, 0, -2.5}, {2, 0, -2.5}, {2, 0, -4.5}, {1, 0, -4.5},
            {1, 2, -2.5}, {2, 2, -2.5}, {2, 2, -4.5}, {1, 2, -4.5},
            {1, 0, -2,5}, {1, 0, -4.5}, {1, 2, -4.5}, {1, 2, -2.5},
            {2, 0, -2,5}, {2, 0, -4.5}, {2, 2, -4.5}, {2, 2, -2.5},
            {1, 0, -2.5}, {2, 0, -2.5}, {2, 2, -2.5}, {1, 2, -2.5},
            {1, 0.2, -2.5}, {2, 0.2, -2.5}, {2, 0.6, -2.5}, {1, 0.6, -2.5},
            {2, 0.6, -2.5}, {1, 0.6, -2.5}, {1, 1, -2.5}, {2, 1, -2.5},
            {1, 1, -2.5}, {2, 1, -2.5}, {2, 1.4, -2.5}, {1, 1.4, -2.5},
            {2, 1.4, -2.5}, {1, 1.4, -2.5}, {1, 1.8, -2.5}, {2, 1.8, -2.5},

            {3, 0, -2.5}, {4, 0, -2.5}, {4, 0, -4.5}, {3, 0, -4.5},
            {3, 2, -2.5}, {4, 2, -2.5}, {4, 2, -4.5}, {3, 2, -4.5},
            {3, 0, -2,5}, {3, 0, -4.5}, {3, 2, -4.5}, {3, 2, -2.5},
            {4, 0, -2,5}, {4, 0, -4.5}, {4, 2, -4.5}, {4, 2, -2.5},
            {3, 0, -2.5}, {4, 0, -2.5}, {4, 2, -2.5}, {3, 2, -2.5},
            {3, 0.2, -2.5}, {4, 0.2, -2.5}, {4, 0.6, -2.5}, {3, 0.6, -2.5},
            {4, 0.6, -2.5}, {3, 0.6, -2.5}, {3, 1, -2.5}, {4, 1, -2.5},
            {3, 1, -2.5}, {4, 1, -2.5}, {4, 1.4, -2.5}, {3, 1.4, -2.5},
            {4, 1.4, -2.5}, {3, 1.4, -2.5}, {3, 1.8, -2.5}, {4, 1.8, -2.5},

            {0.5, 2, -2}, {4.5, 2, -2}, {4.5, 2.5, -2}, {0.5, 2.5, -2},
            {0.5, 2, -5}, {4.5, 2, -5}, {4.5, 2.5, -5}, {0.5, 2.5, -5},
            {0.5, 2, -2}, {0.5, 2.5, -2}, {0.5, 2.5, -5}, {0.5, 2, -5},
            {3.5, 2, -2}, {3.5, 2.5, -2}, {3.5, 2.5, -5}, {3.5, 2, -5},
            {0.5, 2, -2}, {4.5, 2, -2}, {4.5, 2, -5}, {0.5, 2, -5}
        });
    desk.trans_and_rot(0, 0, 0, 0, 0, 0);

    Object workbench(magenta, 
    { 
        {-1, 0, 1}, {-1.3, 0, 1}, {-1.3, 0, 0.7}, {-1, 0, 0.7},
        {-1, 1, 1}, {-1.3, 1, 1}, {-1.3, 1, 0.7}, {-1, 1, 0.7},
        {-1, 0, 1}, {-1, 0, -0.7}, {-1, 1, 0.7}, {-1, 1, 1},
        {-0.7, 0, 1}, {-0.7, 0, -0.7}, {-0.7, 1, 0.7}, {-0.7, 1, 1},
        {-1, 0, 1}, {-0.7, 0, 1}, {-0.7, 1, 1}, {-1, 1, 1},
        {-1, 0, 0.7}, {-0.7, 0, 0.7}, {-0.7, 1, 0.7}, {-1, 1, 0.7},

        {1, 0, 1}, {1.3, 0, 1}, {1.3, 0, 0.7}, {1, 0, 0.7},
        {1, 1, 1}, {1.3, 1, 1}, {1.3, 1, 0.7}, {1, 1, 0.7},
        {1, 0, 1}, {1, 0, -0.7}, {1, 1, 0.7}, {1, 1, 1},
        {0.7, 0, 1}, {0.7, 0, -0.7}, {0.7, 1, 0.7}, {0.7, 1, 1},
        {1, 0, 1}, {0.7, 0, 1}, {0.7, 1, 1}, {1, 1, 1},
        {1, 0, 0.7}, {0.7, 0, 0.7}, {0.7, 1, 0.7}, {1, 1, 0.7},

        {1, 0, 0}, {1.3, 0, 0}, {1.3, 0, -0.3}, {1, 0, -0.3},
        {1, 1, -0.3}, {1.3, 1, -0.3}, {1.3, 1, -0.3}, {1, 1, -0.3},
        {1, 0, 0}, {1, 0, -0.7}, {1, 1, -0.7}, {1, 1, 0},
        {0.7, 0, 0}, {0.7, 0, -0.7}, {0.7, 1, -0.7}, {0.7, 1, 0},
        {1, 0, 0}, {0.7, 0, 0}, {0.7, 1, 0}, {1, 1, 0},
        {1, 0, -0.7}, {0.7, 0, -0.7}, {0.7, 1, -0.7}, {1, 1, -0.7},

        {-1, 0, 0}, {1.3, 0, 0}, {-0.7, 0, -0.3}, {-1, 0, -0.3},
        {-1, 1, -0.3}, {-0.7, 1, -0.3}, {-0.7, 1, -0.3}, {-1, 1, -0.3},
        {-1, 0, 0}, {-1, 0, -0.7}, {-1, 1, -0.7}, {-1, 1, 0},
        {-1.3, 0, 0}, {-1.3, 0, -0.7}, {-1.3, 1, -0.7}, {-1.3, 1, 0},
        {-1, 0, 0}, {-1.3, 0, 0}, {-1.3, 1, 0}, {-1, 1, 0},
        {-1, 0, -0.7}, {-1.3, 0, -0.7}, {-1.3, 1, -0.7}, {-1, 1, -0.7},

        {-1.1, 1, 1.1}, {1.1, 1, 1.1}, {1.1, 1, 0.1}, {-1.1, 1, 0.1},
        {-1.1, 1.5, 1.1}, {1.1, 1.5, 1.1}, {1.1, 1.5, 0.1}, {-1.1, 1.5, 0.1},
        {-1.1, 1, 1.1}, {-1.1, 1, 0.1}, {-1.1, 1.5, 0.1}, {-1.1, 1.5, 1.1},
        {1.1, 1, 1.1}, {1.1, 1, 0.1}, {1.1, 1.5, 0.1}, {1.1, 1.5, 1.1},
        {-1.1, 1, 1.1}, {1.1, 1, 1.1}, {1.1, 1.5, 1.1}, {-1.1, 1.5, 1.1},
        {-1.1, 1, 0.1}, {1.1, 1, 0.1}, {1.1, 1.5, 0.1}, {-1.1, 1.5, 0.1},

        {-1, 1.5, 1}, {-0.7, 1.5, 1}, {-0.7, 1.5, 0.7}, {-1, 1.5, 0.7},
        {-1, 3.5, 1}, {-0.7, 3.5, 1}, {-0.7, 3.5, 0.7}, {-1, 3.5, 0.7},
        {-1, 1.5, 1}, {-1, 1.5, 0.7}, {-1, 3.5, 0.7}, {-1, 3.5, 1},
        {-0.7, 1.5, 1}, {-0.7, 1.5, 0.7}, {-0.7, 3.5, 0.7}, {-0.7, 3.5, 1},
        {-1, 1.5, 1}, {-0.7, 1.5, 1}, {-0.7, 3.5, 1}, {-1, 3.5, 1},
        {-1, 1.5, 0.7}, {-0.7, 1.5, 0.7}, {-0.7, 3.5, 0.7}, {-1, 3.5, 0.7},

        {1, 1.5, 1}, {1.7, 1.5, 1}, {1.7, 1.5, 0.7}, {1, 1.5, 0.7},
        {1, 3.5, 1}, {1.7, 3.5, 1}, {1.7, 3.5, 0.7}, {1, 3.5, 0.7},
        {1, 1.5, 1}, {1, 1.5, 0.7}, {1, 3.5, 0.7}, {1, 3.5, 1},
        {1.7, 1.5, 1}, {1.7, 1.5, 0.7}, {1.7, 3.5, 0.7}, {1.7, 3.5, 1},
        {1, 1.5, 1}, {1.7, 1.5, 1}, {1.7, 3.5, 1}, {1, 3.5, 1},
        {1, 1.5, 0.7}, {1.7, 1.5, 0.7}, {1.7, 3.5, 0.7}, {1, 3.5, 0.7},

        {1, 1.5, 0}, {1.7, 1.5, 0}, {1.7, 1.5, -0.3}, {1, 1.5, -0.3},
        {1, 3.5, 0}, {1.7, 3.5, 0}, {1.7, 3.5, -0.3}, {1, 3.5, -0.3},
        {1, 1.5, 0}, {1, 1.5, -0.3}, {1, 3.5, -0.3}, {1, 3.5, 0},
        {1.7, 1.5, -01}, {1.7, 1.5, -0.3}, {1.7, 3.5, -0.3}, {1.7, 3.5, 0},
        {1, 1.5, 0}, {1.7, 1.5, 0}, {1.7, 3.5, 0}, {1, 3.5, 0},
        {1, 1.5, -0.3}, {1.7, 1.5, -0.3}, {1.7, 3.5, -0.3}, {1, 3.5, -0.3},

        {-1, 1.5, 0}, {-0.3, 1.5, 0}, {-0.3, 1.5, -0.3}, {-1, 1.5, -0.3},
        {-1, 3.5, 0}, {-0.3, 3.5, 0}, {-0.3, 3.5, -0.3}, {-1, 3.5, -0.3},
        {-1, 1.5, 0}, {-1, 1.5, -0.3}, {-1, 3.5, -0.3}, {-1, 3.5, 0},
        {-0.3, 1.5, 0}, {-0.3, 1.5, -0.3}, {-0.3, 3.5, -0.3}, {-0.3, 3.5, 0},
        {-1, 1.5, 0}, {-0.3, 1.5, 0}, {-0.3, 3.5, 0}, {-1, 3.5, 0},
        {-1, 1.5, -0.3}, {-0.3, 1.5, -0.3}, {-0.3, 3.5, -0.3}, {-1, 3.5, -0.3},

        {-1.5, 3.5, 1.5}, {1.5, 3.5, 1.5}, {1.5, 3.5, 0.5}, {-1.5, 3.5, 0.5},
        {-1.5, 4, 1.5}, {1.5, 4, 1.5}, {1.5, 4, 0.5}, {-1.5, 4, 0.5},
        {-1.5, 3.5, 1.5}, {-1.5, 3.5, 0.5}, {-1.5, 4, 0.5}, {-1.5, 4, 1},
        {1.5, 3.5, 1.5}, {1.5, 3.5, 0.5}, {1.5, 4, 0.5}, {1.5, 4, 1},
        {-1.5, 3.5, 1.5}, {1.5, 3.5, 1.5}, {1.5, 4, 1.5}, {-1.5, 4, 1.5},
        {-1.5, 3.5, -0.5}, {1.5, 3.5, -0.5}, {1.5, 4, -0.5}, {-1.5, 4, -0.5} 
    });
    workbench.trans_and_rot(0, 0, 0, 0, 0, 0);

    Object cupboard(cyan,
    {
        {-5, 3, -5}, {-4, 3, -5}, {-4, 3, -4}, {-5, 3, -4},
        {-4, 3, -5}, {-4, 3, -4}, {-4, 4, -4}, {-4, 4, -5},
        {-4, 4, -4}, {-4, 4, -5}, {-2, 4, -5}, {-2, 4, -4},
        {-2, 4, -5}, {-2, 4, -4}, {-2, 3, -4}, {-2, 3, -5},
        {-2, 3, -5}, {-2, 3, -4}, {-1, 3, -4}, {-1, 3, -5},
        {-1, 3, -4}, {-1, 3, -5}, {-1, 5, -5}, {-1, 5, -4},
        {-1, 5, -4}, {-1, 2, -4}, {-2, 2, -4}, {-2, 5, -4},
        {-2, 5, 4}, {-2, 3, -4}, {-1, 3, -4}, {-1, 5, -4},
        {-1, 3, -4}, {-1, 5, -4}, {-5, 5 ,-4}, {-5, 3, -4},
        {-5, 3, -5}, {-5, 3, -4}, {-5, 5, -4}, {-5, 5, -5},
        {-5, 3, -5}, {-3, 3, -5}, {-3, 5, -5}, {-5, 5, -5},
        {-3, 3, -5}, {-3, 5, -5}, {-2, 5, -5}, {-2, 3, -5},
        {-2, 5, -5}, {-1, 5, -5}, {-1, 3, -5}, {-2, 3, -5},

        {-4.8, 3.2, -3.9}, { -3.2, 3.2, -3.9 }, { -3.2, 3.2, -4 }, { -4.8, 3.2, -4 },
        { -3.8, 3.2, -4 }, { -3.8, 3.2, -3.9 }, { -3.8, 4.8, -3.9 }, { -3.8, 4.8, -4 },
        { -3.8, 4.8, -4 }, { -3.8, 4.8, -3.9 }, { -4.8, 4.8, -3.9 }, { -4.8, 4.8, -4 },
        { -4.8, 4.8, -4 }, { -4.8, 4.8, -3.9 }, { -4.8, 3.2, -3.9 }, { -4.8, 3.2, -4 },
        { -4.8, 4.8, -3.9 }, { -3.2, 4.8, -3.9 }, { -3.2, 3.2, -3.9 }, { -4.8, 3.2, -3.9 },
        { -4.8, 4.8, -4 }, { -3.2, 4.8, -4 }, { -3.2, 3.2, -4 }, { -4.8, 3.2, -4 },

        {-2.8, 4.8, -4}, { -2.2, 4.8, -4 }, { -2.2, 3.2, -4 }, { -2.8, 3.2, -4 },
        { -2.8, 4.8, -3.9 }, { -2.2, 4.8, -3.9 }, { -2.2, 3.2, -3.9 }, { -2.8, 3.2, -4 },
        { -2.8, 4.8, -4 }, { -2.8, 4.8, -3.9 }, { -2.8, 3.2, -3.9 }, { -2.8, 3.2, -4 },
        { -2.2, 3.2, -4 }, { -2.2, 4.8, -4 }, { -2.2, 4.8, -3.9 }, { -2.2, 3.2, -3.9 },
        { -2.8, 4.2, -4 }, { -2.2, 4.2, -4 }, { -2.2, 4.2, -3.9 }, { -2.8, 4.2, -3.9 },
        { -2.8, 4.8, -4 }, { -2, 4.8, -4 }, { -2.2, 4.8, -3.9 }, { -2.8, 4.8, -3.9 },

        {-1.8, 3.2, -4}, { -0.8, 3.2, -4 }, { -0.8, 3.2, -3.8 }, { -1.8, 3.2, -3.8 },
        { -1.8, 4.8, -4 }, { -0.8, 4.8, -4 }, { -0.8, 4.8, -3.8 }, { -1.8, 4.8, -3.8 },
        { -1.8, 4.8, -4 }, { -1.8, 4.8, -3.8 }, { -1.8, 3.2, -3.8 }, { -1.8, 3.2, -4 },
        { -0.8, 4.8, -4 }, { -0.8, 4.8, -3.8 }, { -0.8, 3.2, -3.8 }, { -0.8, 3.2, -4 },
        { -1.8, 4.8, -3.8 }, { -0.8, 4.8, 3.8 }, { -0.8, 3.2, 3.8 }, { -1.8, 3.2, 3.8 },
        { -1.8, 4.8, -5 }, { -0.8, 4.8, -5 }, { -0.8, 3.2, -5 }, { -1.8, 3.2, -5 } 
    });
    cupboard.trans_and_rot(0, 0, 0, 0, 0, 0);

    Object counter(green, 
        {
            {0, 0, 0}, {96.5, 0, 0}, {96.5, 36, 0}, {0, 36, 0},
            {0, 0, 42}, {24.5, 0, 42}, {24.5, 36, 42}, {0, 36, 42},
            {24.5, 0, 42}, {24.5, 36, 42}, {24.5, 36, 24.5}, {96.5, 0, 24.5},
            {24.5, 0, 24.5}, {24.5, 36, 24.5}, {96.5, 36, 24.5}, {96.5, 0, 24.5},
            {96.5, 0, 24.5}, {96.5, 36, 24.5}, {96.5, 36, 0}, {96.5, 0, 0},
            {0, 36, 42}, {24.5, 36, 42}, {24.5, 36, 0}, {0, 36, 0},
            {24.5, 36, 0}, {96.5, 36, 0}, {96.5, 36, 24.5}, {24.5, 36, 24.5}
        });
    counter.trans_and_rot(0, 0, 0, 0, 0, 0);
}

/*************************************
Function:   display()
Purpose:    set up display and update
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/
Date:       3/2/2020
*************************************/
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
        fl.centerx(), fl.centery(), fl.centerz(),
        0.0, 1.0, 0.0);
    fl.draw();
    wall1.draw();
    wall2.draw();
    wall3.draw();
    ceiling.draw();
    /*toolbox.draw();
    desk.draw();
    chair.draw();
    cupboard.draw();
    coutner.draw();*/

  /*  for (int i = 0; i < sizeof balls / sizeof(Ball); i++) {
        balls[i].update();
    }*/
    glFlush();
    glutSwapBuffers();
}

/*************************************
Function:   reshape()
Purpose:    manage changes to the window aspect ratio
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/
Date:       3/2/2020
*************************************/
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

/*************************************
Function:   timer()
Purpose:    manage update speed
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/
Date:       3/2/2020
*************************************/
void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}

/*************************************
Function:   special()
Purpose:    manage special keys, Arrow keys
Author:      https://cs.lmu.edu/~ray/notes/openglexamples/
Date:       3/2/2020
*************************************/
void special(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT: camera.moveLeft(); break;
    case GLUT_KEY_RIGHT: camera.moveRight(); break;
    case GLUT_KEY_UP: camera.moveUp(); break;
    case GLUT_KEY_DOWN: camera.moveDown(); break;
    }
    glutPostRedisplay();
}

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
    //initBalls();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("4332 Computer Graphics Assignment 3. Student: Nghia Dang");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutTimerFunc(100, timer, 0);

    init();
    glutMainLoop();
}