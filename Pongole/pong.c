#include "pong.h"

#define WIDTH 800
#define HEIGHT 600
#define ESC 27
#define KEYUP 72
#define KEYDOWN 80

void InitPos(Pong* p) {

	p->pl2.size = p->pl1.size = 7;

	p->pl1.pos.Y = p->pl2.pos.Y = (p->wp1.Y + p->wp2.Y) / 2;
	p->pl1.pos.Y -= p->pl1.size / 2;
	p->pl2.pos.Y -= p->pl2.size / 2;

	p->pl1.prev.X = p->pl1.pos.X = 8;
	p->pl2.prev.X = p->pl2.pos.X = 104;

	p->b.size = 1;
	p->b.pos.X = (p->pl1.pos.X + p->pl2.pos.X) / 2 - 1;
	p->b.pos.Y = (p->wp1.Y + 1) + rand() % (p->wp2.Y - p->wp1.Y - 1);
	
	p->pl1.prev.Y = p->pl2.prev.Y = p->b.prev.X = p->b.prev.Y = WIDTH / 2 - 1;
	p->b.direction.X = 1 - rand()%2 * 2;
	p->b.direction.Y = 1 - rand()%2 * 2;
	p->pl1.direction.X = p->pl1.direction.Y = 0;
	p->pl2.direction.X = p->pl2.direction.Y = 0;
}

void InitPong(Pong* p) {
	SetConsoleTitleA("Pongole [1.0.0]");
	p->_round = 0;
	p->_quit = 0;

	InitPos(p);

	p->wp1.X = p->wp1.Y = 2;
	p->wp2.X = 110;
	p->wp2.Y = 25;

	p->pl1.score = p->pl2.score = 0;
}

char event(Pong* p) {
	char ch = NULL;
	if (_kbhit()) {
		ch = _getch();
		switch (ch) {
		case ESC:
			if (p->_round) {
				InitPong(p);
			}
			else {
				p->_quit = 1;
			}
			break;
		case 'g':
			if (!p->_round)
				p->_round = 1;
			break;
		case KEYUP:
			p->pl2.prev.Y = p->pl2.pos.Y;
			p->pl2.pos.Y -= 2;
			if (p->pl2.pos.Y - 2 <= p->wp1.Y) {
				p->pl2.pos.Y = p->wp1.Y + 1;
			}
			break;
		case 'w':
			p->pl1.prev.Y = p->pl1.pos.Y;
			p->pl1.pos.Y -= 2;
			if (p->pl1.pos.Y - 2 <= p->wp1.Y) {
				p->pl1.pos.Y = p->wp1.Y + 1;
			}
			break;
		case KEYDOWN:
			p->pl2.prev.Y = p->pl2.pos.Y;
			p->pl2.pos.Y += 2;
			if (p->pl2.pos.Y + p->pl2.size >= p->wp2.Y) {
				p->pl2.pos.Y = p->wp2.Y - p->pl2.size;
			}
			break;
		case 's':
			p->pl1.prev.Y = p->pl1.pos.Y;
			p->pl1.pos.Y += 2;
			if (p->pl1.pos.Y + p->pl1.size >= p->wp2.Y) {
				p->pl1.pos.Y = p->wp2.Y - p->pl1.size;
			}
			break;
		default:
			break;
		}
	}
	return ch;
}

void update(Pong* p) {
	if (p->b.pos.Y + p->b.direction.Y == p->wp2.Y || p->b.pos.Y + p->b.direction.Y == p->wp1.Y)
		p->b.direction.Y *= -1;
	//hits player left
	if (p->b.pos.X + p->b.direction.X == p->pl1.pos.X) {
		if (p->b.pos.Y <= p->pl1.pos.Y + p->pl1.size + 1 && p->b.pos.Y >= p->pl1.pos.Y)
			p->b.direction.X *= -1;
	}
	//hits player right
	if (p->b.pos.X + p->b.direction.X == p->pl2.pos.X) {
		if (p->b.pos.Y <= p->pl2.pos.Y + p->pl2.size + 1 && p->b.pos.Y >= p->pl2.pos.Y)
			p->b.direction.X *= -1;
	}

	p->b.prev.X = p->b.pos.X;
	p->b.prev.Y = p->b.pos.Y;
	p->b.pos.X += p->b.direction.X;
	p->b.pos.Y += p->b.direction.Y;

	//ball hits wall
	if (p->b.pos.X == p->wp1.X) {
		RoundOver(&p->pl2, &p->_round);
	}
	else if (p->b.pos.X == p->wp2.X) {
		RoundOver(&p->pl1, &p->_round);
	}
}

void RoundOver(Player* pl, char* round) {
	pl->score += 1;
	*round = 0;
}

char GameOver(char winner) {
	return winner;
}