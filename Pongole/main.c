#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "window.h"
#include "pong.h"
#include <time.h>

#define ESC 27

int main() {
	Window w;
	Pong p;
	char ch, winner = 0;
	InitWindow(&w, WIDTH, HEIGHT);
	srand(time(NULL));
	InitPong(&p);
	//PROGRAM loop
	do {
		cls(w.hout);
		ch = (char)NULL;
		//Start Menu loop
		InitPos(&p);
		draw(&w, &p);
		SetPos(w.hout, (WIDTH / FW) / 2 - 5, p.wp1.Y + 10);
		printf("press 'g' to start\n");
		do {
			ch = event(&p);
		}while (!p._round && !p._quit);
		//Game loop
		cls(w.hout);
		while (p._round && !p._quit) {
			ch = event(&p);
			update(&p);
			draw(&w, &p);
			Sleep(5);
		}
		//Game over
		if (p.pl1.score == 5) {
			winner = 1;
			p._quit = 1;
		}
		else if (p.pl2.score == 5) {
			winner = 2;
			p._quit = 1;
		}
	} while (!p._quit);

	if (winner) {
		SetPos(w.hout, (WIDTH / FW) / 2 - 5, p.wp1.Y + 10);
		printf("PLAYER %d WON!", winner);
		SetPos(w.hout, (WIDTH / FW) / 2 - 10, p.wp1.Y + 12);
		printf("press 'q' to continue (quit)...");
		while(_getch() != 'q'){}
	}
	return 0;
}
