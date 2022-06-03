#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#ifndef PONG_H
#define PONG_H

#define FW 8 //font width
#define FH 16 //font height
#define WIDTH 800
#define HEIGHT 600

typedef struct Player {
	COORD pos;
	COORD direction;
	COORD prev;
	short size;
	short int score;
}Player;

typedef struct Pong {
	char _round, _quit;
	Player pl1, pl2, b;
	COORD wp1, wp2;
}Pong;

void InitPong(Pong* p);
void InitPos(Pong* p);
void RoundOver(char* score, char* round);
char event(Pong* p);
void update(Pong* p);

#endif