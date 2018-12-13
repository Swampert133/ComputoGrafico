#include "Matrix3.h"
#include <math.h>

Matrix3	Identity()
{
	Matrix3 r;
	r.m[0][0] = r.m[1][1] = r.m[2][2] = 1;
	r.m[0][1] = r.m[0][2] = 0;
	r.m[1][0] = r.m[1][2] = 0;
	r.m[2][0] = r.m[2][1] = 0;
	return r;
}

Matrix3 Matrix3::Translate(const Vector3D &v)
{
	Matrix3	r = Identity();
	r.m[0][2] = v.x;
	r.m[1][2] = v.y;
	return r;
}

Matrix3 Matrix3::Rotation(const int &angle)
{
	Matrix3 r = Identity();
	r.m[0][0] = r.m[1][1] = cos((angle * 3.141592654) / 180);
	r.m[0][1] = sin((angle * 3.141592654) / 180);
	r.m[1][0] = -sin((angle * 3.141592654) / 180);
	return r;
}

Matrix3 Matrix3::Scale(const double &s)
{
	Matrix3 r = Identity();
	r.m[0][0] = r.m[1][1] = s;
	return r;
}

Vector3D Matrix3::operator*(const Vector3D &RH)const
{
	Vector3D result;
	result.x = m[0][0] * RH.x + m[0][1] * RH.y + m[0][2];
	result.y = m[1][0] * RH.x + m[1][1] * RH.y + m[1][2];
	result.z = m[2][0] * RH.x + m[2][1] * RH.y + m[2][2];
	return result;
}

Matrix3 & Matrix3::operator*(const Matrix3 & RH)
{
	Matrix3 result = Identity();
	result.m[0][0] = result.m[1][1] = result.m[2][2] = 0;
	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			for (int i = 0; i < 3; ++i)
				result.m[row][col] += m[row][i] * RH.m[i][col];
	return result;
}

Matrix3 & Matrix3::operator=(const Matrix3 & RH)
{
	if (this != &RH)
		for (int row = 0; row < 3; ++row)
			for (int col = 0; col < 3; ++col)
				m[row][col] = RH.m[row][col];
	return *this;
}

Matrix3::Matrix3()
{
}

Matrix3::~Matrix3()
{
}