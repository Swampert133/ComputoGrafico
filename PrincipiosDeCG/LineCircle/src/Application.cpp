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
yellow(255,255,0,0)
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

void Application::draw()
{
	
	setColor(yellow);
	x++;
	if (x < 500)
	{
		PutPixel(x, 0);
		PutPixel(0, x);
		PutPixel(x, x);
		PutPixel(x, -x);
	}
} 

Application::~Application()
{
}