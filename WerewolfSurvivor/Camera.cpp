#include "Camera.h"
camera::camera(){
	trans = transform();
	width = 1024;
	height = 768;
	renderStartPosition = vector2D(trans.position.x-width/2, trans.position.y + height / 2);
	renderEndPosition = vector2D(trans.position.x + width / 2, trans.position.y - height / 2);
}
void camera::update() {
	renderStartPosition = vector2D(trans.position.x - width / 2, trans.position.y + height / 2);
	renderEndPosition = vector2D(trans.position.x + width / 2, trans.position.y - height / 2);
}
bool camera::candraw(vector2D point) {
	return inCamera(point);
}
bool camera::inCamera(vector2D point) {
	return inArea(point, renderStartPosition, renderEndPosition);
}
vector2D camera::screenPosToCameraPos(vector2D point) {
	int x = point.x - width / 2;
	int y = -point.y + height / 2;
	return vector2D(x, y);
}
vector2D camera::cameraPosToWorldPos(vector2D point) {
	return point + trans.position;
}
vector2D camera::screenPosToWorldPos(vector2D point) {
	return cameraPosToWorldPos(screenPosToCameraPos(point));
}

vector2D camera::worldPosToCameraPos(vector2D point) {
	return point - trans.position;
}
vector2D camera::cameraPosToScreenPos(vector2D point) {
	int x = point.x + width / 2;
	int y = -point.y + height / 2;
	return vector2D(x, y);
}
vector2D camera::worldPosToScreenPos(vector2D point) {
	return cameraPosToScreenPos(worldPosToCameraPos(point));
}