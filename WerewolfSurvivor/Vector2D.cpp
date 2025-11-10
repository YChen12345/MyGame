#include "Vector2D.h"

vector2D::vector2D() :x(0), y(0) {}
vector2D::vector2D(dir d) {
	switch (d)
	{
	case zero:
		x = 0;
		y = 0;
		break;
	case up:
		x = 0;
		y = 1;
		break;
	case down:
		x = 0;
		y = -1;
		break;
	case left:
		x = -1;
		y = 0;
		break;
	case right:
		x = 1;
		y = 0;
		break;
	case one:
		x = 1;
		y = 1;
		break;
	default:
		x = 0;
		y = 0;
		break;
	}
}
vector2D::vector2D(float a, float b) :x(a), y(b) {}
vector2D::vector2D(const vector2D& v) {
	x = v.x;
	y = v.y;
}
vector2D& vector2D::operator = (const vector2D& v) {
	x = v.x;
	y = v.y;
	return *this;
}
vector2D vector2D::operator + (const vector2D& v) {
	vector2D res;
	res.x = x+v.x;
	res.y = y+v.y;
	return res;
}
vector2D vector2D::operator - (const vector2D& v) {
	vector2D res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}
vector2D vector2D::operator * (float f) {
	vector2D res;
	res.x = x*f;
	res.y = y*f;
	return res;
}
void vector2D::set(float a, float b) {
	x = a;
	y = b;
}
vector2D vector2D::normalize() {
	vector2D v;
	if (x * x + y * y > 0.f) {
		v.x = x / std::sqrt(x * x + y * y);
		v.y = y / std::sqrt(x * x + y * y);
	}
	return v;
}
float vector2D::magnitude() {
	return std::sqrt(x * x + y * y);
}