/*File name: main.cpp
Name: Nghia Dang
Date: Feb 16, 2020
Course: COSC 4332 - Computer Graphics
Descsription: The program creates a snake game
*/

#define COLUMNS 40
#define ROWS 40
#define FPS 10

extern int score;
extern short sDirection;
extern int snake_length;
bool gameOver = false;
double speed = 150; // The bigger, the smaller

#include <Windows.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"
#include <string>


void display_callBack();
void reshape_callback(int, int);
void timer_callback(int);
void keyboard_callback(int, int, int); //Sets moving direction of the snake

/*******************************************************************************************
function: init()
purpose: initialize the window and set up
Author: Ted Dang
 Date: 2/21/2020
 *********************************************************************************************/
void init(void) {
	glClearColor(0.1, 0.1, 0.1, 0.0); //Set display-window color to be grey
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the screen and the depth buffer
	initGrid(COLUMNS, ROWS); // Create grid
	glMatrixMode(GL_PROJECTION); //Set projection parameters
	glLoadIdentity();
	glOrtho(0,COLUMNS,0,ROWS,-1,1); //It defines a view box's position
	glMatrixMode(GL_MODELVIEW);
}

/*******************************************************************************************
function: display_callBack
purpose: Sends graphics to display window
Author: Ted Dang
 Date: 2/21/2020
 *********************************************************************************************/
void display_callBack() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawGrid();
	drawSnake();
	drawFood();
	drawEnigma();
	glutSwapBuffers(); // swaps the buffers of the current window if double buffered
	if (gameOver) {
		char scores[10];
		_itoa_s(score, scores, 10);
		char notify[50] = "Your score: ";
		strcat_s(notify, scores);
		MessageBox(NULL, notify, "Game over", 0);
		exit(0);
	}
}

/*******************************************************************************************
function: reshape_callback
purpose: Sets the reshape callback for the current window
Author: Ted Dang
 Date: 2/21/2020
 *********************************************************************************************/
void reshape_callback(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // sets the viewport
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, -1.0); // multiply the current matrix with an orthographic matrix
}

/*******************************************************************************************
function: timer_callback
purpose: Registers a timer callback to be triggered in a specified number of milliseconds
Author: Ted Dang
 Date: 2/21/2020
 *********************************************************************************************/
void timer_callback(int) {
	glutPostRedisplay(); // marks the current window as needing to be redisplayed
	glutTimerFunc(speed, timer_callback, 0);
}

/*******************************************************************************************
function: keyboard_callback
purpose: Sets the special keyboard callback for the current window
Author: Ted Dang
 Date: 2/21/2020
 *********************************************************************************************/
void keyboard_callback(int key, int, int) {
	switch (key) {
	case GLUT_KEY_UP:
		if (sDirection != DOWN) {
			sDirection = UP;
		}
		break;
	case GLUT_KEY_DOWN:
		if (sDirection != UP) {
			sDirection = DOWN;
		}
		break;
	case GLUT_KEY_LEFT:
		if (sDirection != RIGHT) {
			sDirection = LEFT;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (sDirection != LEFT) {
			sDirection = RIGHT;
		}
		break;
	}
}

/*******************************************************************************************
function: main
purpose: Main function
Author: Ted Dang
 Date: 2/21/2020
 *********************************************************************************************/
int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Sets display mode
	glutInitWindowPosition(50, 100); // Sets top-left display-window position
	glutInitWindowSize(500, 500); // Sets display-window width and height
	glutCreateWindow("Course: 4332. Student name: Nghia Dang. Assignment 02"); // Creates display window
	init(); // Executes initialization procedure
	glutDisplayFunc(display_callBack); // Sends graphics to display window
	glutReshapeFunc(reshape_callback); // Sets the reshape callback for the current window
	glutTimerFunc(speed, timer_callback, 0); // registers a timer callback to be triggered in a specified number of milliseconds
	glutSpecialFunc(keyboard_callback); //  sets the special keyboard callback for the current window
	glutMainLoop(); // Displays everything and wait
	return(0);
}

