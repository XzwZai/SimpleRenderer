#pragma once
#include "VMath.h"
class Color : public Vec3
{
public:
	float R, G, B;	

	Color(float _R = 0.0f, float _G = 0.0f, float _B = 0.0f) {
		R = _R; G = _G; B = _B;
	}

	Color operator = (const Vec3 v) {
		R = v.x; G = v.y; B = v.z;
	}

};
const Color BLACK = Color();
const Color WHITE = Color(1.0f, 1.0f, 1.0f);
