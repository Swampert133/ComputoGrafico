#pragma once
#include "BaseApplication.h"
#include "Vector2d.h"
#include <vector>

class Application : public BaseApplication
{
private:
	int x = -500;
	bool firstgo = true;
	int centerX, centerY;
	int currentPositionX, currentPositionY;
	Color currentcolor;
	Color black;
	Color yellow;
public:
	Application();
	~Application();
	void PutPixel(const int &x, const int&y);
	void draw();
	void ClearScreen();
	void line(const int&x1, const int &y1);
	void midPointLine3(const int &x, const int &y, const int &x1, const int &y1);
	void setColor(Color color);
	void setColor(const char &R, const char &G, const char &B, const char &A);
	void move_To(const int &x, const int&y);
	void line_To(const int &x, const int&y);
};

