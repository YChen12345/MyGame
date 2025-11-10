#include "Transform.h"

transform::transform() {
	position=vector2D(zero);
	rotate = vector2D(up);
	scale = vector2D(one);
}
void transform::scaling(float multiple) {
	scale.x = scale.x * multiple;
	scale.y = scale.y * multiple;
}
void transform::rotating(float angle) {
	rotate = rotateVec2d(rotate, angle);
}
void transform::transport(vector2D move) {
	position = position + move;
}
void transform::init() {
	position = vector2D(zero);
	rotate = vector2D(up);
	scale = vector2D(one);
}