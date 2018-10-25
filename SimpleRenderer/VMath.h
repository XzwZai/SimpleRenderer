#pragma once
#include <string>
#include <math.h>
class Vec3;
typedef Vec3 Color;
class Vec3
{
public:
	float x, y, z;
	Vec3()
	{
		x = 0; y = 0; z = 0;
	}
	Vec3(float _x, float _y, float _z) {
		x = _x;	y = _y;	z = _z;
	}

	Vec3 operator + (const Vec3 v) {
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	Vec3 operator - (const Vec3 v) {
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	Vec3 operator * (const Vec3 v) const {
		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	Vec3 operator * (const float f) {
		return Vec3(x * f, y * f, z * f);
	}

	Vec3 operator / (const float f) const {
		return Vec3(x / f, y / f, z / f);
	}

	void operator = (const Vec3 v) {
		x = v.x; y = v.y; z = v.z;
	}

	Vec3 norm() {
		return *this / (length());
	}

	float dot(Vec3 v) {
		return x * v.x + y * v.y + z * v.z;
	}

	float length() {
		return sqrt(x * x + y * y + z * z);
	};

	std::string toString()
	{
		return "(" + std::to_string(x) + " ," + std::to_string(y) + " ," + std::to_string(z) + " )";
	}
};

const Color BLACK = Color();
const Color WHITE = Color(1.0f, 1.0f, 1.0f);
const Color RED = Color(1.0f, 0.0f, 0.0f);
const Color BLUE = Color(0.0f, 0.0f, 1.0f);