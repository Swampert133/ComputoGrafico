#pragma once
#include "BaseApplication.h"
#include "Vector2d.h"
#include "Vector3D.h"
#include <vector>

class Application : public BaseApplication
{
private:
	std::vector<Vector2d> TriangleV;
	std::vector<Vector2d> TriangleV1;
	std::vector<Vector2d> TriangleV2;
	std::vector<Vector2d> vertices;
	int f1, f2, f3, f4, f5;
	bool firstgo = true;
	int centerX, centerY;
	int currentPositionX, currentPositionY;
	Color currentcolor;
	Color black;
	Color yellow;
	Color purple;
	Color green;
	Color blue;
public:
	Application();
	~Application();
	void PutPixel(const int &x, const int&y);
	void draw();
	void set();
	void ClearScreen();
	void line(const int&x1, const int &y1);
	void Figure(const int &lados, const int &r);
	void CreateFigure(const int &lados, const int &r, const int &x, const int&y);
	void midPointLine(const int&x0, const int&x1, const int&y0, const int &y1);
	void midPointLine2(const int&x0, const int&x1, const int&y0, const int &y1);
	void midPointLine3(const int &x, const int &y, const int &x1, const int &y1);
	void setColor(Color color);
	void triangle(const Vector2d v, const Vector2d v1, const Vector2d v2);
	std::vector<Vector2d> generateTriangles();
	void Randomtriangle();
	void setColor(const char &R, const char &G, const char &B, const char &A);
	void move_To(const int &x, const int&y);
	void line_To(const int &x, const int&y);
	void SierpinskyGasket(Vector2d a, Vector2d b, Vector2d c, int subDiv);
	Vector2d PuntoMedioVec(Vector2d a, Vector2d b);
};