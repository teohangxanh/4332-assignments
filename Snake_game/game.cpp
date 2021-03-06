#include <Windows.h>
#include <GL/freeglut.h>
#include <ctime>
#include "Game.h"


extern bool gameOver;
bool food = true;
bool enigma = true;
extern double speed;
short sDirection = RIGHT; // Default direction
int score = 0;
int gridX, gridY;
int snake_length = 2;
int posX[MAX] = { 20 }, posY[MAX] = { 20 }; // Store position of the snake's segments
int foodX, foodY; // Position of food
int enigmaX = 20, enigmaY = 20; // Position of enigma

/*******************************************************************************************
function: initGrid
purpose: Create grid
Author: Ted Dang
Date: 2/21/2020
********************************************************************************************/
void initGrid(int x, int y) {
	gridX = x;
	gridY = y;
}

/*******************************************************************************************
function: drawGrid
purpose: Sets the playground for the game
Author: Ted Dang
Date: 2/21/2020
********************************************************************************************/
void drawGrid() {
	for (int i = 0; i < gridX; i++) {
		for (int j = 0; j < gridY; j++) {
			unit(i, j);
		}
	}
}

/*******************************************************************************************
function: unit
purpose: Oustand the playground's border
Author: Ted Dang
Date: 2/21/2020
********************************************************************************************/
void unit(int x, int y) {
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) {
		glLineWidth(3.0); // sets the width of the line
		glColor3f(1.0, 0.0, 0.0); // sets the color of the line
	}
	else {
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
}

/*******************************************************************************************
function: drawSnake
purpose: Draw snake and handle cases when the snake eats food, collides with its body, 
		 touches window edges, etc.
Author: Ted Dang
Date: 2/21/2020
********************************************************************************************/
void drawSnake() {
	glColor3f(1.0, 0.0, 1.0); // Color of enigma
	glRectf(enigmaX, enigmaY, enigmaX + 1, enigmaY + 1); // Rectangle representing enigma

	// The new snake's segment copy the immediately previous one
	for (int i = snake_length - 1; i > 0; i--) {
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}

	// Move the snake's head
	switch (sDirection) {
	case UP: posY[0]++; break;
	case DOWN: posY[0]--; break;
	case LEFT: posX[0]--; break;
	case RIGHT: posX[0]++; break;
	}

	// Draw the snake's segments
	for (int i = 0; i < snake_length; i++) {
		if (i == 0) {
			glColor3f(0.0, 1.0, 0.0); // A viper
		}
		else {
			glColor3f(1.0, 1.0, 0.0); 
		}
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
	}

	// If the snake eats its body, game over
	for (int i = 1; i < snake_length; i++) {
		if (posX[0] == posX[i] && posY[0] == posY[i]) gameOver = true;
	}

	// The snake reappears at the opposite window edge
	if (posX[0] == 0 || posX[0] == gridX-1 || posY[0] == 0 || posY[0] == gridY-1) {
		if (posX[0] == 0) posX[0] = gridX - 2;
		if (posX[0] == gridX - 1) posX[0] = 0;
		if (posY[0] == 0) posY[0] = gridY - 2;
		if (posY[0] == gridY - 1) posY[0] = 0;
	}

	//When the snake eats food
	if (foodX == posX[0] && foodY == posY[0]) {	
		score += 1;
		speed *= 0.95;
		snake_length++;
		if (snake_length > MAX) {
			snake_length = MAX;
		}
		food = true;
		drawFood();
	}

	//When the snake gets enigma, reduce speed by 20%
	if (enigmaX == posX[0] && enigmaY == posY[0]) {
		if (enigma) {
			speed *= 1.2;
			enigma = false;
		}
		else {
			enigma = true;
		}
	}
}

/*******************************************************************************************
function: drawFood
purpose: Draw food
Author: Ted Dang
Date: 2/21/2020
********************************************************************************************/
void drawFood() {
	if (food) //Food has to be reset
	{
		//srand(time(NULL));
		random(foodX, foodY);
	}
	food = false;
	glColor3f(1.0, 0.0, 0.0);
	glRectf(foodX, foodY, foodX + 1, foodY + 1);
}

/*******************************************************************************************
function: random
purpose: Assign a random value from 1 to grid - 2 to x and y (x != y)
Author: Ted Dang
Date: 2/21/2020
********************************************************************************************/

void random(int& x, int& y) {
	int _maxX = gridX - 2;
	int _maxY = gridY - 2;
	int _min = 1;
	srand(time(NULL)); // seeds the pseudo random number generator used by the rand() function.
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);
}