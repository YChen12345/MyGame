#pragma once
#include "Transform.h"
class camera{
public:
	transform trans;
	int height;
	int width;
	vector2D renderStartPosition;
	vector2D renderEndPosition;
public:
	camera();
	vector2D screenPosToCameraPos(vector2D point);
	vector2D cameraPosToWorldPos(vector2D point);
	vector2D screenPosToWorldPos(vector2D point);

	vector2D worldPosToCameraPos(vector2D point);
	vector2D cameraPosToScreenPos(vector2D point);
	vector2D worldPosToScreenPos(vector2D point);
	void update();
	bool candraw(vector2D point);
	bool inCamera(vector2D point);
};