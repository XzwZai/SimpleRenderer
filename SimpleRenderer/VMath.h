#pragma once
#include <string>
#include <math.h>
#define PI 3.1415926
class Vec3;
class Vec4;
typedef Vec3 Color;
typedef Vec3 Pos;
typedef Vec3 Normal;
class Vec3
{
public:
	float x, y, z;
	float &r = x, &g = y, &b = z;	
	Vec3()
	{
		x = 0; y = 0; z = 0;
	}
	Vec3(float _x, float _y, float _z) {
		x = _x;	y = _y;	z = _z;
	}

	Vec3 operator + (const Vec3 &v) {
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	Vec3 operator - (const Vec3 &v) {
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	Vec3 operator * (const Vec3 &v) {
		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	Vec3 operator * (float f) {
		return Vec3(x * f, y * f, z * f);
	}

	Vec3 operator / (float f) {
		return Vec3(x / f, y / f, z / f);
	}

	void operator = (const Vec3 &v) {
		x = v.x; y = v.y; z = v.z;
	}

	Vec3 norm() {
		return *this / (length());
	}

	float dot(const Vec3 &v) {
		return x * v.x + y * v.y + z * v.z;
	}

	Vec3 cross(const Vec3 &v) {
		return Vec3(y*v.z - z*v.y,z*v.x - x*v.z,x*v.y - y*v.x);
	}

	float length() {
		return sqrt(x * x + y * y + z * z);
	};

	std::string toString()
	{
		return "(" + std::to_string(x) + " ," + std::to_string(y) + " ," + std::to_string(z) + " )";
	}
};

class Vec4
{
public:
	float x, y, z, w;
	Vec4() { x = y = z = 0; w = 1; }
	Vec4(float _x, float _y, float _z, float _a) { x = _x; y = _y; z = _z; w = _a; }
	Vec4(Vec3 v, float _a) { x = v.x; y = v.y; z = v.z; w = _a; }

};

class Mat4
{
public:
	float mat[16];
	Mat4()
	{
		mat[0] = 1.0; mat[4] = 0.0; mat[8] = 0.0; mat[12] = 0.0;
		mat[1] = 0.0; mat[5] = 1.0; mat[9] = 0.0; mat[13] = 0.0;
		mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = 0.0;
		mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
	}
	Mat4(const Vec3& v0, const Vec3& v1, const Vec3& v2)
	{
		mat[0] = v0.x; mat[4] = v1.x; mat[8] = v2.x; mat[12] = 0.0f;
		mat[1] = v0.y; mat[5] = v1.y; mat[9] = v2.y; mat[13] = 0.0f;
		mat[2] = v0.z; mat[6] = v1.z; mat[10] = v2.z; mat[14] = 0.0f;
		mat[3] = 0.0f; mat[7] = 0.0f; mat[11] = 0.0f; mat[15] = 1.0f;
	}
	~Mat4() { }
	Mat4(const Mat4 &Mat4)
	{
		for (int i = 0; i < 16; i++) {
			mat[i] = Mat4.mat[i];
		}
	}
	Mat4 transpose()
	{
		Mat4 Matrix;
		Matrix[0] = mat[0];
		Matrix[1] = mat[4];
		Matrix[2] = mat[8];
		Matrix[3] = mat[12];
		Matrix[4] = mat[1];
		Matrix[5] = mat[5];
		Matrix[6] = mat[9];
		Matrix[7] = mat[13];
		Matrix[8] = mat[2];
		Matrix[9] = mat[6];
		Matrix[10] = mat[10];
		Matrix[11] = mat[14];
		Matrix[12] = mat[3];
		Matrix[13] = mat[7];
		Matrix[14] = mat[11];
		Matrix[15] = mat[15];
		return Matrix;
	}

	bool inverse()
	{
		double inv[16], det;
		int i;

		inv[0] = mat[5] * mat[10] * mat[15] -
			mat[5] * mat[11] * mat[14] -
			mat[9] * mat[6] * mat[15] +
			mat[9] * mat[7] * mat[14] +
			mat[13] * mat[6] * mat[11] -
			mat[13] * mat[7] * mat[10];

		inv[4] = -mat[4] * mat[10] * mat[15] +
			mat[4] * mat[11] * mat[14] +
			mat[8] * mat[6] * mat[15] -
			mat[8] * mat[7] * mat[14] -
			mat[12] * mat[6] * mat[11] +
			mat[12] * mat[7] * mat[10];

		inv[8] = mat[4] * mat[9] * mat[15] -
			mat[4] * mat[11] * mat[13] -
			mat[8] * mat[5] * mat[15] +
			mat[8] * mat[7] * mat[13] +
			mat[12] * mat[5] * mat[11] -
			mat[12] * mat[7] * mat[9];

		inv[12] = -mat[4] * mat[9] * mat[14] +
			mat[4] * mat[10] * mat[13] +
			mat[8] * mat[5] * mat[14] -
			mat[8] * mat[6] * mat[13] -
			mat[12] * mat[5] * mat[10] +
			mat[12] * mat[6] * mat[9];

		inv[1] = -mat[1] * mat[10] * mat[15] +
			mat[1] * mat[11] * mat[14] +
			mat[9] * mat[2] * mat[15] -
			mat[9] * mat[3] * mat[14] -
			mat[13] * mat[2] * mat[11] +
			mat[13] * mat[3] * mat[10];

		inv[5] = mat[0] * mat[10] * mat[15] -
			mat[0] * mat[11] * mat[14] -
			mat[8] * mat[2] * mat[15] +
			mat[8] * mat[3] * mat[14] +
			mat[12] * mat[2] * mat[11] -
			mat[12] * mat[3] * mat[10];

		inv[9] = -mat[0] * mat[9] * mat[15] +
			mat[0] * mat[11] * mat[13] +
			mat[8] * mat[1] * mat[15] -
			mat[8] * mat[3] * mat[13] -
			mat[12] * mat[1] * mat[11] +
			mat[12] * mat[3] * mat[9];

		inv[13] = mat[0] * mat[9] * mat[14] -
			mat[0] * mat[10] * mat[13] -
			mat[8] * mat[1] * mat[14] +
			mat[8] * mat[2] * mat[13] +
			mat[12] * mat[1] * mat[10] -
			mat[12] * mat[2] * mat[9];

		inv[2] = mat[1] * mat[6] * mat[15] -
			mat[1] * mat[7] * mat[14] -
			mat[5] * mat[2] * mat[15] +
			mat[5] * mat[3] * mat[14] +
			mat[13] * mat[2] * mat[7] -
			mat[13] * mat[3] * mat[6];

		inv[6] = -mat[0] * mat[6] * mat[15] +
			mat[0] * mat[7] * mat[14] +
			mat[4] * mat[2] * mat[15] -
			mat[4] * mat[3] * mat[14] -
			mat[12] * mat[2] * mat[7] +
			mat[12] * mat[3] * mat[6];

		inv[10] = mat[0] * mat[5] * mat[15] -
			mat[0] * mat[7] * mat[13] -
			mat[4] * mat[1] * mat[15] +
			mat[4] * mat[3] * mat[13] +
			mat[12] * mat[1] * mat[7] -
			mat[12] * mat[3] * mat[5];

		inv[14] = -mat[0] * mat[5] * mat[14] +
			mat[0] * mat[6] * mat[13] +
			mat[4] * mat[1] * mat[14] -
			mat[4] * mat[2] * mat[13] -
			mat[12] * mat[1] * mat[6] +
			mat[12] * mat[2] * mat[5];

		inv[3] = -mat[1] * mat[6] * mat[11] +
			mat[1] * mat[7] * mat[10] +
			mat[5] * mat[2] * mat[11] -
			mat[5] * mat[3] * mat[10] -
			mat[9] * mat[2] * mat[7] +
			mat[9] * mat[3] * mat[6];

		inv[7] = mat[0] * mat[6] * mat[11] -
			mat[0] * mat[7] * mat[10] -
			mat[4] * mat[2] * mat[11] +
			mat[4] * mat[3] * mat[10] +
			mat[8] * mat[2] * mat[7] -
			mat[8] * mat[3] * mat[6];

		inv[11] = -mat[0] * mat[5] * mat[11] +
			mat[0] * mat[7] * mat[9] +
			mat[4] * mat[1] * mat[11] -
			mat[4] * mat[3] * mat[9] -
			mat[8] * mat[1] * mat[7] +
			mat[8] * mat[3] * mat[5];

		inv[15] = mat[0] * mat[5] * mat[10] -
			mat[0] * mat[6] * mat[9] -
			mat[4] * mat[1] * mat[10] +
			mat[4] * mat[2] * mat[9] +
			mat[8] * mat[1] * mat[6] -
			mat[8] * mat[2] * mat[5];

		det = mat[0] * inv[0] + mat[1] * inv[4] + mat[2] * inv[8] + mat[3] * inv[12];

		if (det == 0)
			return false;

		det = 1.0 / det;

		for (i = 0; i < 16; i++)
			mat[i] = inv[i] * det;

		return true;
	}

	Mat4& operator = (const Mat4 &Mat4)
	{
		for (int i = 0; i < 16; i++) {
			mat[i] = Mat4.mat[i];			
		}
		return *this;
	}
	inline float& operator [] (int Index)
	{
		return mat[Index];
	}
	inline double* operator & ()
	{
		return (double*)this;
	}
	friend inline Mat4 operator * (const Mat4 &Matrix1, const Mat4 &Matrix2)
	{
		Mat4 Matrix3;

		Matrix3.mat[0] = Matrix1.mat[0] * Matrix2.mat[0] + Matrix1.mat[4] * Matrix2.mat[1] + Matrix1.mat[8] * Matrix2.mat[2] + Matrix1.mat[12] * Matrix2.mat[3];
		Matrix3.mat[1] = Matrix1.mat[1] * Matrix2.mat[0] + Matrix1.mat[5] * Matrix2.mat[1] + Matrix1.mat[9] * Matrix2.mat[2] + Matrix1.mat[13] * Matrix2.mat[3];
		Matrix3.mat[2] = Matrix1.mat[2] * Matrix2.mat[0] + Matrix1.mat[6] * Matrix2.mat[1] + Matrix1.mat[10] * Matrix2.mat[2] + Matrix1.mat[14] * Matrix2.mat[3];
		Matrix3.mat[3] = Matrix1.mat[3] * Matrix2.mat[0] + Matrix1.mat[7] * Matrix2.mat[1] + Matrix1.mat[11] * Matrix2.mat[2] + Matrix1.mat[15] * Matrix2.mat[3];

		Matrix3.mat[4] = Matrix1.mat[0] * Matrix2.mat[4] + Matrix1.mat[4] * Matrix2.mat[5] + Matrix1.mat[8] * Matrix2.mat[6] + Matrix1.mat[12] * Matrix2.mat[7];
		Matrix3.mat[5] = Matrix1.mat[1] * Matrix2.mat[4] + Matrix1.mat[5] * Matrix2.mat[5] + Matrix1.mat[9] * Matrix2.mat[6] + Matrix1.mat[13] * Matrix2.mat[7];
		Matrix3.mat[6] = Matrix1.mat[2] * Matrix2.mat[4] + Matrix1.mat[6] * Matrix2.mat[5] + Matrix1.mat[10] * Matrix2.mat[6] + Matrix1.mat[14] * Matrix2.mat[7];
		Matrix3.mat[7] = Matrix1.mat[3] * Matrix2.mat[4] + Matrix1.mat[7] * Matrix2.mat[5] + Matrix1.mat[11] * Matrix2.mat[6] + Matrix1.mat[15] * Matrix2.mat[7];

		Matrix3.mat[8] = Matrix1.mat[0] * Matrix2.mat[8] + Matrix1.mat[4] * Matrix2.mat[9] + Matrix1.mat[8] * Matrix2.mat[10] + Matrix1.mat[12] * Matrix2.mat[11];
		Matrix3.mat[9] = Matrix1.mat[1] * Matrix2.mat[8] + Matrix1.mat[5] * Matrix2.mat[9] + Matrix1.mat[9] * Matrix2.mat[10] + Matrix1.mat[13] * Matrix2.mat[11];
		Matrix3.mat[10] = Matrix1.mat[2] * Matrix2.mat[8] + Matrix1.mat[6] * Matrix2.mat[9] + Matrix1.mat[10] * Matrix2.mat[10] + Matrix1.mat[14] * Matrix2.mat[11];
		Matrix3.mat[11] = Matrix1.mat[3] * Matrix2.mat[8] + Matrix1.mat[7] * Matrix2.mat[9] + Matrix1.mat[11] * Matrix2.mat[10] + Matrix1.mat[15] * Matrix2.mat[11];

		Matrix3.mat[12] = Matrix1.mat[0] * Matrix2.mat[12] + Matrix1.mat[4] * Matrix2.mat[13] + Matrix1.mat[8] * Matrix2.mat[14] + Matrix1.mat[12] * Matrix2.mat[15];
		Matrix3.mat[13] = Matrix1.mat[1] * Matrix2.mat[12] + Matrix1.mat[5] * Matrix2.mat[13] + Matrix1.mat[9] * Matrix2.mat[14] + Matrix1.mat[13] * Matrix2.mat[15];
		Matrix3.mat[14] = Matrix1.mat[2] * Matrix2.mat[12] + Matrix1.mat[6] * Matrix2.mat[13] + Matrix1.mat[10] * Matrix2.mat[14] + Matrix1.mat[14] * Matrix2.mat[15];
		Matrix3.mat[15] = Matrix1.mat[3] * Matrix2.mat[12] + Matrix1.mat[7] * Matrix2.mat[13] + Matrix1.mat[11] * Matrix2.mat[14] + Matrix1.mat[15] * Matrix2.mat[15];

		return Matrix3;
	}

	friend inline Vec3 operator * (const Mat4 &Mat4, const Vec3 &Vector)
	{
		Vec4 v = Mat4 * Vec4(Vector, 0.0f);
		return Vec3(v.x,v.y,v.z);
	}

	friend inline Vec4 operator * (const Mat4 &Mat4, const Vec4 &Vector)
	{
		Vec4 v;
		v.x = Mat4.mat[0] * Vector.x + Mat4.mat[4] * Vector.y + Mat4.mat[8] * Vector.z + Mat4.mat[12] * Vector.w;
		v.y = Mat4.mat[1] * Vector.x + Mat4.mat[5] * Vector.y + Mat4.mat[9] * Vector.z + Mat4.mat[13] * Vector.w;
		v.z = Mat4.mat[2] * Vector.x + Mat4.mat[6] * Vector.y + Mat4.mat[10] * Vector.z + Mat4.mat[14] * Vector.w;
		v.w = Mat4.mat[3] * Vector.x + Mat4.mat[7] * Vector.y + Mat4.mat[11] * Vector.z + Mat4.mat[15] * Vector.w;
		return v;
	}
};

Mat4 translationMat(int x, int y, int z)
{
	Mat4 m;
	m.mat[12] = x;
	m.mat[13] = y;
	m.mat[14] = z;
	return m;
}

Mat4 translationMat(Vec3 v)
{
	Mat4 m;
	m.mat[12] = v.x;
	m.mat[13] = v.y;
	m.mat[14] = v.z;
	return m;
}

float max(float a, float b) {
	return a > b ? a : b;
}

float min(float a, float b) {
	return a < b ? a: b;
}

float max(float a, float b, float c) {
	if (a > b) {
		return max(a, c);
	}
	else {
		return max(b, c);
	}
}

float min(float a, float b, float c) {
	if (a < b) {
		return min(a, c);
	}
	else {
		return min(b, c);
	}
}

const Color BLACK = Color();
const Color WHITE = Color(1.0f, 1.0f, 1.0f);
const Color RED = Color(1.0f, 0.0f, 0.0f);
const Color BLUE = Color(0.0f, 0.0f, 1.0f);