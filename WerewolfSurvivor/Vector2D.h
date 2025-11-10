#pragma once
#include <cmath>
enum dir {
	zero = 0,
	up = 1,
	down = 2,
	left = 3,
	right = 4,
	one = 5
};
class vector2D {
public:
	float x;
	float y;
public:
	vector2D();
	vector2D(dir d);
	vector2D(float a, float b);
	vector2D(const vector2D& v);
	vector2D& operator = (const vector2D& v);
	vector2D operator + (const vector2D& v);
	vector2D operator - (const vector2D& v);
	vector2D operator * (float f);
	void set(float a, float b);
	vector2D normalize();
	float magnitude();
};