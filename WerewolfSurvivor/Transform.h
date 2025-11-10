#pragma once
#include "Mathf.h"
#include "Vector2D.h"


class transform {
public:
	vector2D position;
	vector2D rotate;
	vector2D scale;
public:
	transform();
	void scaling(float multiple);
	void rotating(float angle);
	void transport(vector2D move);
	void init();
};
