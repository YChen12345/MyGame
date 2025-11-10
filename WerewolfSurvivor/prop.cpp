#include "prop.h"
#include "GameManager.h"
void prop::update() {
	if (distance(gameobject->trans.position, player->trans.position) < 54) {
		switch (kindid)
		{
		case 0:
			player->getComponent<hero>().atk_gap = max(player->getComponent<hero>().atk_gap - 0.1f, 0.2f);
			player->getComponent<hero>().skill_level = min(player->getComponent<hero>().skill_level + 1, 20);
			break;
		case 1:
			player->getComponent<hero>().blood += 5;
			break;
		default:
			break;
		}
		gameobject->data->destory(gameobject);
	}	
}
void prop::lateupdate() {
	draw();
}
void prop::draw() {
	int w = canvas->getWidth();
	int h = canvas->getHeight();
	vector2D screenpos = gameobject->cam->worldPosToScreenPos(gameobject->trans.position);
	int x_ = screenpos.x;
	int y_ = screenpos.y;
	for (int y = 0; y < sprite.height; y++) {
		for (int x = 0; x < sprite.width; x++) {
			if (sprite.alphaAt(x, y) > 0) {
				canvas->drawCheck(static_cast<int>(x_ - sprite.width / 2 + x), static_cast<int>(y_ - sprite.height / 2 + y), sprite.at(x, y), w, h);
			}
		}
	}
}