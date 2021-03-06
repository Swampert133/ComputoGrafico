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
	std::vector<Vector3D> vertices;
	std::vector<Vector3D> vectorcase;
	int f1, f2, f3, f4, f5;
	bool firstgo = true;
	int centerX, centerY;
	int currentPositionX, currentPositionY;
	static enum Type
	{
		POINTS,
		LINES,
		LINESTRIP,
		LINELOOP,
		TRIANGLE,
		TRIANGLEFAN,
		TRIANGLESTRIP
	};
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
	void midPointLine3(const int &x, const int &y, const int &x1, const int &y1);
	void setColor(Color color);
	void triangle(const Vector2d v, const Vector2d v1, const Vector2d v2);
	void triangle(const Vector3D v, const Vector3D v1, const Vector3D v2);
	std::vector<Vector2d> generateTriangles();
	void Randomtriangle();
	void setColor(const char &R, const char &G, const char &B, const char &A);
	void move_To(const int &x, const int&y);
	void line_To(const int &x, const int&y);
	void SierpinskyGasket(Vector3D a, Vector3D b, Vector3D c, int subDiv);
	Vector3D PuntoMedioVec(Vector3D a, Vector3D b);
	Vector3D translatev(Vector3D v, const int &x, const int &y);
	void drawArray(const std::vector<Vector3D> &v, Type type);
};