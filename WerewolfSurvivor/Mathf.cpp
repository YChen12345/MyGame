#include "Mathf.h"

int ceilDiv(int a, int b) {
	if (a % b > 0) {
		return 1 + a / b;
	}
	else
	{
		return a / b;
	}
}
float distance(vector2D v1, vector2D v2) {
	return (v1 - v2).magnitude();
}
vector2D direction(vector2D position, vector2D aim_position) {
	return (aim_position - position).normalize();
}
vector2D randomVec2d() {
	float angle = randomRange(0, 360);
	float radians = angle_radians(angle);
	float x = cosf(radians);
	float y = sinf(radians);
	return vector2D(x, y);
}
vector2D randomVec2dInRange(vector2D v, float angle) {
	float randomAngle = randomRange(-angle, angle);
	vector2D res = rotateVec2d(v, randomAngle);
	return res;
}
vector2D randomVec2dInRange(vector2D v1, vector2D v2) {
	float angle_1 = angle360(v1);
	float angle_2 = angle360(v2);
	if (angle_2 > angle_1) {
		return rotateVec2d(vector2D(right), randomRange(angle_1, angle_2));
	}
	else if (angle_2 < angle_1) {
		return rotateVec2d(vector2D(right), randomRange(angle_2, angle_1));
	}
	else{
		return v1.normalize();
	}
}
bool randomRes(float probability) {
	if (randomRange(0, 1) <= probability) {
		return true;
	}
	else
	{
		return false;
	}
}
float randomRange(float min, float max) {
	static std::mt19937 gen{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}
int randomRangeint(int min, int max) {
	static std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(min, max - 1);
	return dist(gen);
}
vector2D rotateVec2d(vector2D v, float angle) {
	vector2D res;
	float radians = angle_radians(angle);
	float a = v.x;
	float b = v.y;
	res.x = a * cosf(radians) + b * sinf(radians);
	res.y = -a * sinf(radians) + b * cosf(radians);
	return res;
}
float angle_radians(float angle) {
	return angle * PI / 180.f;
}
float angle360(vector2D v)
{
	float rad = std::atan2(v.y, v.x);
	if (rad < 0) {
		rad += 2 * PI;
	}
	return rad * 180.f / PI;
}
bool inArea(vector2D point, vector2D start, vector2D end) {
	if (point.x >= start.x && point.x <= end.x && point.y <= start.y && point.y >= end.y) {
		return true;
	}
	else
	{
		return false;
	}
}