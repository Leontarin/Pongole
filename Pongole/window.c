#include "window.h"

void InitWindow(Window* w, int W, int H) {
	COORD c;
	SMALL_RECT r;
	w->hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(w->hout, &w->csbi)) {
		printf("Get csbi failed.\n");
		exit(1);
	}
	r.Left = r.Top = 0;
	r.Right = W - 1;
	r.Bottom = H - 1;
	SetConsoleWindowInfo(w->hout, 1, &r);
	c.X = w->csbi.srWindow.Right - w->csbi.srWindow.Left + 1;
	c.Y = w->csbi.srWindow.Bottom - w->csbi.srWindow.Top + 1;
	
	SetConsoleScreenBufferSize(w->hout, c);

	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(w->hout, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(w->hout, &cci);
}

void SetColor(HANDLE hout, int color) {
	SetConsoleTextAttribute(hout, color);
}

void SetPos(HANDLE hout, short int X, short int Y) {
	COORD c;
	c.X = X;
	c.Y = Y;
	SetConsoleCursorPosition(hout, c);
}

void cls(HANDLE hout) {
	COORD c;
	SMALL_RECT r;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CHAR_INFO fill;
	SetColor(hout, 0x0f);

	if (!GetConsoleScreenBufferInfo(hout, &csbi))
		return;

	r.Top = r.Left = 0;
	r.Right = csbi.dwSize.X;
	r.Bottom = csbi.dwSize.Y;

	c.X = 0;
	c.Y = (SHORT)(0 - csbi.dwSize.Y);

	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	ScrollConsoleScreenBuffer(hout, &r, NULL, c, &fill);
	SetPos(hout, 0, 0);
}

void ClearPrev(HANDLE hout, COORD prev, int size) {
	int i;
	SetColor(hout, 0x00);
	for (i = 0;i < size;i++) {
		SetPos(hout, prev.X, prev.Y + i);
		printf(" ");
	}
}

void drawWall(HANDLE hout, COORD p1, COORD p2) {
	short int i;
	//draw Top wall
	SetColor(hout,0xff);
	for (i = p1.X; i <= p2.X; i++) {
		SetPos(hout, i, p1.Y);
		printf(" ");
	}
	//draw Bottom Wall
	for (i = p1.X; i <= p2.X; i++) {
		SetPos(hout, i, p2.Y);
		printf(" ");
	}
	//draw Right Wall
	for (i = p1.Y; i <= p2.Y; i++) {
		SetPos(hout, p1.X, i);
		printf(" ");
	}
	//draw Left Wall
	for (i = p1.Y; i <= p2.Y; i++) {
		SetPos(hout, p2.X, i);
		printf(" ");
	}
}

void draw(Window* w, Pong* p) {
	int i;
	
	drawWall(w->hout, p->wp1, p->wp2);
		//clear previous frames
	ClearPrev(w->hout, p->pl1.prev, p->pl1.size);
	ClearPrev(w->hout, p->pl2.prev, p->pl2.size);
	ClearPrev(w->hout, p->b.prev, p->b.size);

	//Player and ball positions
	SetColor(w->hout, 0xff);
	for (i = 0;i < p->pl1.size; i++) {
		SetPos(w->hout, p->pl1.pos.X, p->pl1.pos.Y + i);
		printf(" ");
	}
	for (i = 0;i < p->pl2.size; i++) {
		SetPos(w->hout, p->pl2.pos.X, p->pl2.pos.Y + i);
		printf(" ");
	}
	SetColor(w->hout, 0xee);
	for (i = 0;i < p->b.size; i++) {
		SetPos(w->hout, p->b.pos.X, p->b.pos.Y + i);
		printf(" ");
	}

	SetColor(w->hout, 0x0f);
	SetPos(w->hout, WIDTH / FW / 2, p->wp2.Y + 2);
	printf("%d : %d", p->pl1.score, p->pl2.score);
}