/*File name: main.cpp
Name: Nghia Dang
Date: Feb 16, 2020
Course: COSC 4332 - Computer Graphics
Descsription: The program creates a snake game
*/

#define COLUMNS 40
#define ROWS 40
#define FPS 10

extern short sDirection;
extern int snake_length;
int score = 0;
bool gameOver = false;
double speed = 100;

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"
#include <string>


void display_callBack();
void reshape_callback(int, int);
void timer_callback(int);
void keyboard_callback(int, int, int); //Sets moving direction of the snake

void init(void) {
	glClearColor(0.1, 0.1, 0.1, 0.0); //Set display-window color to be grey
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the screen and the depth buffer
	initGrid(COLUMNS, ROWS); // Create grid
	glMatrixMode(GL_PROJECTION); //Set projection parameters
	glLoadIdentity();
	glOrtho(0,COLUMNS,0,ROWS,-1,1); //It defines a view box's position
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Sets display mode
	glutInitWindowPosition(50, 100); // Sets top-left display-window position
	glutInitWindowSize(800, 800); // Sets display-window width and height
	glutCreateWindow("Course: 4332. Student name: Nghia Dang. Assignment 02"); // Creates display window
	init(); // Executes initialization procedure
	glutDisplayFunc(display_callBack); // Sends graphics to display window
	glutReshapeFunc(reshape_callback); // sets the reshape callback for the current window
	glutTimerFunc(speed, timer_callback, 0); // registers a timer callback to be triggered in a specified number of milliseconds.
	glutSpecialFunc(keyboard_callback); //  sets the special keyboard callback for the current window.
	glutMainLoop(); // Displays everything and wait
	return(0);

}

void display_callBack() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawGrid();
	drawEnigma();
	drawSnake();
	drawFood();
	glutSwapBuffers(); // swaps the buffers of the current window if double buffered
	if (gameOver) // Displays message box after the game is over 
	{
		MessageBox(NULL, L"your score:", L"...", MB_OK);
		exit(0);
	}
}

void reshape_callback(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // sets the viewport
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, -1.0); // multiply the current matrix with an orthographic matrix
}

void timer_callback(int) {
	glutPostRedisplay(); // marks the current window as needing to be redisplayed.
	glutTimerFunc(speed, timer_callback, 0);
	//if (snake_length >= 2) speed *= 0.95;
}

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