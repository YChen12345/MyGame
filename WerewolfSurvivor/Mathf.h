#pragma once
#include <iostream>
#include <cmath>
#include "Vector2D.h"
#include <random>

const float PI = 3.1415926f;
int ceilDiv(int a, int b);// a/b
float distance(vector2D v1, vector2D v2);
vector2D direction(vector2D position, vector2D aim_position);
vector2D randomVec2d();
vector2D randomVec2dInRange(vector2D v,float angle);
vector2D randomVec2dInRange(vector2D v1, vector2D v2);
bool randomRes(float probability);
float randomRange(float min,float max);
int randomRangeint(int min,int max);
vector2D rotateVec2d(vector2D v, float angle);
float angle_radians(float angle);
float angle360(vector2D v);
bool inArea(vector2D point, vector2D start, vector2D end);