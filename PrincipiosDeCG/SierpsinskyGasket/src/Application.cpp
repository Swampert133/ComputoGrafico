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
blue( 0, 0, 125, 0)
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

void Application::SierpinskyGasket(Vector3D a, Vector3D b, Vector3D c, int subDiv)
{
	if (subDiv <= 0)
	{
		vertices.push_back(a);
		vertices.push_back(b);
		vertices.push_back(c);
	}
	else
	{
		Vector3D ab = PuntoMedioVec(a, b);
		Vector3D bc = PuntoMedioVec(b, c);
		Vector3D ca = PuntoMedioVec(c, a);
		SierpinskyGasket(a, ab, ca, subDiv - 1);
		SierpinskyGasket(ab, b, bc, subDiv - 1);
		SierpinskyGasket(ca, bc, c, subDiv - 1);
	}
}

Vector3D Application::PuntoMedioVec(Vector3D a, Vector3D b)
{
	Vector3D pmvec;
	pmvec.x = (a.x + b.x) / 2;
	pmvec.y = (a.y + b.y) / 2;
	return pmvec;
}

void Application::drawArray(const std::vector<Vector3D>& v, Type type)
{
	setColor(yellow);
	int translationx;
	int translationy;
	switch (type)
	{
	case POINTS:
		translationx = -400; translationy = 100;
		for (Vector3D vactual : v)
			PutPixel(translationx + vactual.x,translationy + vactual.y);
		break;
	case LINES:
		translationx = -200; translationy = 350;
		for (int i = 0; i < v.size() -1; i += 2)
		{
			move_To(translationx + v[i].x, translationy + v[i].y);
			line_To(translationx + v[i + 1].x, translationy + v[i + 1].y);
		}
		break;
	case LINESTRIP:
		translationx = 200; translationy = 350;
		move_To(translationx + v[0].x, translationy + v[0].y);
		for (int i = 1; i < v.size(); ++i)
		{
			line_To(translationx + v[i].x, translationy + v[i].y);
		}
		break;
	case LINELOOP:
		translationx = 400; translationy = 100;
		move_To(translationx + v[0].x, translationy + v[0].y);
		for (int i = 1; i < v.size(); ++i)
		{
			line_To(translationx + v[i].x, translationy + v[i].y);
		}
		line_To(translationx + v[0].x, translationy + v[0].y);
		break;
	case TRIANGLE:
		translationx = -300; translationy = -300;
		for (int i = 0; i < v.size() - 2; i += 3)
		{
			triangle(translatev(vectorcase[i],translationx,translationy),
				     translatev(vectorcase[i+1], translationx, translationy),
				     translatev(vectorcase[i+2], translationx, translationy));
		}
		break;
	case TRIANGLEFAN:
		translationx = 0; translationy = -300;
		if (vectorcase.size() < 3)
			break;
		else
		{
			triangle(translatev(vectorcase[0], translationx, translationy),
				     translatev(vectorcase[1], translationx, translationy),
				     translatev(vectorcase[2], translationx, translationy));
			for (int i = 3; i < vectorcase.size(); ++i)
			{
				move_To(vectorcase[i - 1].x + translationx, vectorcase[i - 1].y + translationy);
				line_To(vectorcase[i].x + translationx, vectorcase[i].y + translationy);
				line_To(vectorcase[0].x + translationx, vectorcase[0].y + translationy);
			}
		}
		break;
	case TRIANGLESTRIP:
		translationx = 300; translationy = -300;
		if (vectorcase.size() < 3)
			break;
		else
		{
			triangle(translatev(vectorcase[0], translationx, translationy),
				translatev(vectorcase[1], translationx, translationy),
				translatev(vectorcase[2], translationx, translationy));
			for (int i = 3; i < vectorcase.size(); ++i)
			{
				move_To(vectorcase[i - 1].x + translationx, vectorcase[i - 1].y + translationy);
				line_To(vectorcase[i].x + translationx, vectorcase[i].y + translationy);
				line_To(vectorcase[i-2].x + translationx, vectorcase[i-2].y + translationy);
			}
		}
		break;
	default:
		std::cout << "not a valid type" << std::endl;
		break;
	}
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

void Application::triangle(const Vector3D v, const Vector3D v1, const Vector3D v2)
{
	move_To(v.x, v.y);
	line_To(v1.x, v1.y);
	line_To(v2.x, v2.y);
	line_To(v.x, v.y);
}

Vector3D Application::translatev(const Vector3D v, const int &x, const int &y)
{
	Vector3D translatedv;
	translatedv.x = v.x + x;
	translatedv.y = v.y + y;
	translatedv.z = v.z;
	return translatedv;
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
void Application::set()
{
	Vector3D a(0, 250, 1);
	Vector3D b(-250, -150, 1);
	Vector3D c(250, -150, 1);
	SierpinskyGasket(a, b, c, 3);
	Vector3D d(-80, -50, 1); 
	vectorcase.push_back(d);
	Vector3D e(-50, 50, 1);
	vectorcase.push_back(e);
	Vector3D f(50, -50, 1);
	vectorcase.push_back(f);
	Vector3D g(80, 50, 1);
	vectorcase.push_back(g);
}

void Application::draw()
{
	ClearScreen();
	setColor(green);
	for (int i = 0; i < vertices.size(); i += 3)
		triangle(vertices[i], vertices[i + 1], vertices[i + 2]);
	drawArray(vectorcase, POINTS);
	drawArray(vectorcase, LINES);
	drawArray(vectorcase, LINESTRIP);
	drawArray(vectorcase, LINELOOP);
	drawArray(vectorcase, TRIANGLE);
	drawArray(vectorcase, TRIANGLEFAN);
	drawArray(vectorcase, TRIANGLESTRIP);
} 

Application::~Application()
{
}