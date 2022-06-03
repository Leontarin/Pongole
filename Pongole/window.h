#include <windows.h>
#include <stdio.h>
#include <winuser.h>
#include "pong.h"
#ifndef WINDOW_H
#define WINDOW_H

typedef struct Window {
	HANDLE hout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
}Window;

void InitWindow(Window* w, int W, int H);

void SetColor(HANDLE hout, int color);
void SetPos(HANDLE hout, short int X, short int Y);

void cls(HANDLE hout);
void ClearPrev(HANDLE hout, COORD prev);
void drawWall(HANDLE hout, COORD p1, COORD p2);
void draw(Window* w, Pong* p);

#endif