#include "Application.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <stdlib.h>
#include <time.h>


Application::Application() : BaseApplication(),
centerX(WIDTH / 2),
centerY(HEIGHT / 2),
currentPositionX(0),
currentPositionY(0),
currentcolor(0, 0, 0, 0),
black(0, 0, 0, 255),
yellow(255,255,0,0),
purple(255,0,255,0),
green( 0, 255, 0, 0),
blue( 0, 0, 255, 0)
{
}

void Application::PutPixel(const int&x, const int&y)
{
	putPixel(centerX + x, centerY - y, currentcolor);
}

void Application::ClearScreen() 
{
	for (int i = 0; i <= WIDTH; ++i)
	{
		for (int j = 0; j <= HEIGHT; ++j)
			putPixel(i, j, black);
	}
}

void Application::move_To(const int&x, const int&y)
{
	currentPositionX = x + centerX;
	currentPositionY = -y + centerY;
}

void Application::line(const int&xdestino, const int &ydestino)
{
	int x1 = currentPositionX;
	int x2 = centerX + xdestino;
	int y1 = currentPositionY;
	int y2 = centerY - ydestino;
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x<maxX; x++)
	{
		if (steep)
		{
			putPixel(y, x, currentcolor);
		}
		else
		{
			putPixel(x, y, currentcolor);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}


void Application::midPointLine3(const int&x, const int&y, const int&x1, const int &y1)
{
	int xfinal = x1;
	int yfinal = y1;
	int xdelta;
	int ydelta;
	if (x1 > x)
	{
		xdelta = x;
		ydelta = y;
	}
	else
	{
		xdelta = x1;
		ydelta = y1;
		xfinal = x;
		yfinal = y;
	}
	int a = yfinal - ydelta;
	int b = xfinal - xdelta;
	int d = 2 * a - b;
	int incE = 2 * a;
	int incNE = 2 * (a - b);
	if (abs(a) > abs(b))
	{
		d = 2 * b - a;
		incE = 2 * b;
		incNE = 2 * (b - a);
		if (yfinal > ydelta)
		{
			while (ydelta < yfinal)
			{
				putPixel(xdelta, ydelta, currentcolor);
			    if (d > 0)
				{
					++xdelta;
					d = d + incNE;
				}
				else
					d = d + incE;
				++ydelta;
			}
		}
		else
		{
			incNE = 2 * (a + b);
			while (ydelta >= yfinal)
			{
				putPixel(xdelta, ydelta, currentcolor);
				if (d > 0)
				{
					++xdelta;
					d += incNE;
				}
				else
					d += incE;
				--ydelta;
			}
		}
	}
	else
	{
		if (yfinal > ydelta)
		{
			while (xdelta <= xfinal)
			{
				putPixel(xdelta, ydelta, currentcolor);
				if (d > 0)
				{
					++ydelta;
					d = d + incNE;
				}
				else
					d = d + incE;
				++xdelta;
			}
		}
		else
		{
			incNE = 2 * (a + b);
			while (xdelta <= xfinal)
			{
				putPixel(xdelta, ydelta, currentcolor);
				if (d < 0)
				{
					--ydelta;
					d += incNE;
				}
				else
					d += incE;
				++xdelta;
			}
		}
	}
}

void Application::line_To(const int &xd, const int&yd)
{
	midPointLine3(currentPositionX, currentPositionY, centerX + xd, centerY - yd);
	move_To(xd, yd);
}

void Application::setColor(Color color)
{
	currentcolor = color;
}

void Application::setColor(const char &R, const char &G, const char &B, const char &A)
{
	currentcolor = Color(R, G, B, A);
}

void Application::Randomtriangle()
{
	move_To(0,0);
	line_To(100, 100);
	line_To(100, -100);
	line_To(0, -1);
}

int randomnumber()
{
	int i = (rand() % 1000 - 500);
	return i;
}

std::vector<Vector2d> Application::generateTriangles()
{
	std::vector<Vector2d> trianglevertexes;
	Vector2d v, v1, v2;
	v.x = randomnumber();
	v.y = randomnumber();
	v1.x = randomnumber();
	v1.y = randomnumber();
	v2.x = randomnumber();
	v2.y = randomnumber();
	trianglevertexes.push_back(v);
	trianglevertexes.push_back(v1);
	trianglevertexes.push_back(v2);
	return trianglevertexes;
}

void Application::triangle(const Vector2d v, const Vector2d v1, const Vector2d v2)
{
	move_To(v.x, v.y);
	line_To(v1.x, v1.y);
	line_To(v2.x, v2.y);
	line_To(v.x, v.y);
}

void Application::Figure(const int &lados, const int &r)
{
	setColor(purple);
	float inc = 360.0f / (float)lados;
	move_To(r, 0);

	for (float ang = inc; ang < 360; ang += inc)
	{
		int x = r * cos(ang * 3.141592654 / 180);
		int y = r * sin(ang * 3.141592654 / 180);
		line_To(x, y);
	}
	line_To(r, 0);
}

void Application::CreateFigure(const int &lados, const int &r, const int &x, const int &y)
{
	setColor(purple);
	float inc = 360.0f / (float)lados;
	move_To(x + r,y + 0);

	for (float ang = inc; ang < 360; ang += inc)
	{
		int x1 = r * cos(ang * 3.141592654 / 180);
		int y2 = r * sin(ang * 3.141592654 / 180);
		line_To(x + x1, y + y2);
	}
	line_To(x + r,y + 0);
}


void Application::draw()
{
	ClearScreen();
	setColor(yellow);
	if (firstgo == true)
	{
		srand(time(NULL));
		TriangleV = generateTriangles();
		TriangleV1 = generateTriangles();
		TriangleV2 = generateTriangles();
		firstgo = false;
		f1 = rand() % 12 + 3;
		f2 = rand() % 12 + 3;
		f3 = rand() % 12 + 3;
		f4 = rand() % 12 + 3;
		f5 = rand() % 12 + 3;
	}
	else
	{
		triangle(TriangleV[0], TriangleV[1], TriangleV[2]);
		triangle(TriangleV1[0], TriangleV1[1], TriangleV1[2]);
		triangle(TriangleV2[0], TriangleV2[1], TriangleV2[2]);
		Figure(f1, 50);
		CreateFigure(f2, 50, -250, -250);
		CreateFigure(f3, 50, 250, -250);
		CreateFigure(f4, 50, -250, 250);
		CreateFigure(f5, 50, 250, 250);
	}
} 

Application::~Application()
{
}