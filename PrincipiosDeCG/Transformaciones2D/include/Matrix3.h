#pragma once
#include "Vector3D.h"

class Matrix3
{
public:
	float m[3][3];
	static Matrix3 Translate(const Vector3D &v);
	static Matrix3 Rotation(const int &angle);
	static Matrix3 Scale(const double &s);
	Vector3D operator*(const Vector3D &RH) const;
	Matrix3 & operator*(const Matrix3 &RH);
	Matrix3 & operator=(const Matrix3 &RH);
	Matrix3();
	~Matrix3();
};