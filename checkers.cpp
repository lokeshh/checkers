#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>

using namespace std ;
extern float pl1x[];
extern float pl1y[];
extern float pl2x[];
extern float pl2y[];

class Piece;

class Place
{
public:
	float x, y;
	Place *u, *d, *l, *r;
	Piece *pc;
	Place(float a, float b)
	{
		pc = NULL;
		x = a;
		y = b;
		u = this;
		d = this;
		l = this;
		r = this;
	}
	void getLoc()
	{
		cout << "(" << x << ", " << y << ")" << endl;
	}
};

class Piece
{
public:
	int player;  						// Either 1 or 2
	int no;                 // 0 to 5
	Place *p;
	Piece(int pl, int number)
	{
		player = pl;
		no = number;
		p = NULL;
	}
};

class Board
{
public:
	Place *curPlace;
	Place *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, \
				*p9, *p10, *p11, *p12, *p13, *p14, *p15, *p16;
	int p1Left, p2Left;
	Piece *pl1pcs[6];
	Piece *pl2pcs[6];
	bool isAnimate;
	Place *moveFrom;
	Place *moveTo;
	int i1, i2;
	bool isMove;
	int player;
	Board()
	{
		player = 1;
		isMove = false;
		i1 = 0;
		i2 = 0;
		moveFrom = NULL;
		moveTo = NULL;
		p1Left = 6;
		p2Left = 6;
		p1 = new Place(-0.4, -0.4);
		p2 = new Place(0.0, -0.4);
		p3 = new Place(0.4, -0.4);
		p4 = new Place(0.4, 0.0);
		p5 = new Place(0.4, 0.4);
		p6 = new Place(0.0, 0.4);
		p7 = new Place(-0.4, 0.4);
		p8 = new Place(-0.4, 0.0);
		p9 = new Place(-0.2, 0.0);
		p10 = new Place(-0.2, 0.2);
		p11 = new Place(0.0, 0.2);
		p12 = new Place(0.2, 0.2);
		p13 = new Place(0.2, 0.0);
		p14 = new Place(0.2, -0.2);
		p15 = new Place(0.0, -0.2);
		p16 = new Place(-0.2, -0.2);
		curPlace = p1;
		p1->r = p2;
		p2->r = p3;
		p3->u = p4;
		p4->u = p5;
		p5->l = p6;
		p6->l = p7;
		p7->d = p8;
		p8->d = p1;
		p8->u = p7;
		p7->r = p6;
		p6->r = p5;
		p5->d = p4;
		p4->d = p3;
		p3->l = p2;
		p2->l = p1;
		p1->u = p8;
		p9->u = p10;
		p10->r = p11;
		p11->r = p12;
		p12->d = p13;
		p13->d = p14;
		p14->l = p15;
		p15->l = p16;
		p16->u = p9;
		p9->d = p16;
		p16->r = p15;
		p15->r = p14;
		p14->u = p13;
		p13->u = p12;
		p12->l = p11;
		p11->l = p10;
		p10->d = p9;
		p8->r = p9;
		p9->l = p8;
		p11->u = p6;
		p6->d = p11;
		p13->r = p4;
		p4->l = p13;
		p15->d = p2;
		p2->u = p15;
		isAnimate = false;
	}
	void rightPress()
	{
		curPlace = curPlace->r;
	}
	void leftPress()
	{
		curPlace = curPlace->l;
	}
	void upPress()
	{
		curPlace = curPlace->u;
	}
	void downPress()
	{
		curPlace = curPlace->d;
	}
	void getCursor()
	{
		curPlace->getLoc();
	}
	bool placePiece()
	{
		if (player == 1 && p1Left != 0 && curPlace->pc == NULL)
		{
			p1Left--;
			pl1pcs[p1Left] = new Piece(1, p1Left);
			curPlace->pc = pl1pcs[p1Left];
			pl1pcs[p1Left]->p = curPlace;
			return true;
		}
		if (player == 2 && p2Left != 0 && curPlace->pc == NULL)
		{
			p2Left--;
			pl2pcs[p2Left] = new Piece(2, p2Left);
			curPlace->pc = pl2pcs[p2Left];
			pl2pcs[p2Left]->p = curPlace;
			return true;
		}
		return false;
	}

	void remove()
	{
		if (player == 2)
		{
			pl2x[curPlace->pc->no] = 1000;
			pl2y[curPlace->pc->no] = 1000;
		}
		else
		{
			pl1x[curPlace->pc->no] = 1000;
			pl1y[curPlace->pc->no] = 1000;
		}
		curPlace->pc->p = NULL;
		curPlace->pc = NULL;
		glutPostRedisplay();

	}

	void animate_helper()
	{
		if (player == 1)											// Execute this if player 1's turn
		{
			if (isAnimate == true)
			{
				if ((abs(pl1x[p1Left] - curPlace->x) >= 0.006) ||
						(abs(pl1y[p1Left] - curPlace->y) >= 0.006))
				{
					pl1x[p1Left] += (curPlace->x - pl1x[p1Left])/5;
					pl1y[p1Left] += (curPlace->y - pl1y[p1Left])/5;
				}
				else
				{
					player = (player == 1) ? 2:1;
					isAnimate = false;
				}
			}

			if (isMove == true)
			{
				if ((abs(moveTo->x - pl1x[moveTo->pc->no]) >= 0.006) ||
						(abs(moveTo->y - pl1y[moveTo->pc->no]) >= 0.006))
				{
					pl1x[moveTo->pc->no] += (moveTo->x - pl1x[moveTo->pc->no])/5;
					pl1y[moveTo->pc->no] += (moveTo->y - pl1y[moveTo->pc->no])/5;
				}
				else
				{
					player = (player == 1) ? 2:1;
					isMove = false;
				}
			}
		}
		else								                  // Execute this if player 2's turn
		{
			if (isAnimate == true)
			{
				if ((abs(pl2x[p2Left] - curPlace->x) >= 0.006) ||
						(abs(pl2y[p2Left] - curPlace->y) >= 0.006))
				{
					pl2x[p2Left] += (curPlace->x - pl2x[p2Left])/5;
					pl2y[p2Left] += (curPlace->y - pl2y[p2Left])/5;
				}
				else
				{
					player = (player == 1) ? 2:1;
					isAnimate = false;
				}
			}

			if (isMove == true)
			{
				if ((abs(moveTo->x - pl2x[moveTo->pc->no]) >= 0.006) ||
						(abs(moveTo->y - pl2y[moveTo->pc->no]) >= 0.006))
				{
					pl2x[moveTo->pc->no] += (moveTo->x - pl2x[moveTo->pc->no])/5;
					pl2y[moveTo->pc->no] += (moveTo->y - pl2y[moveTo->pc->no])/5;
				}
				else
				{
					player = (player == 1) ? 2:1;
					isMove = false;
				}
			}
		}
		glutPostRedisplay();
	}

	void move()
	{
		moveTo->pc = moveFrom->pc;
		moveTo->pc->p = moveTo;
		moveFrom->pc = NULL;
		moveFrom = NULL;
	}


};
