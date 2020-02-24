#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN - 1
#define RIGHT 2
#define LEFT -2
#define MAX 200


void initGrid(int, int);
void drawGrid(); // draws the playground
void unit(int, int); // draws the board
void drawSnake();
void drawFood();
void drawEnigma();
void random(int&, int&);

#endif