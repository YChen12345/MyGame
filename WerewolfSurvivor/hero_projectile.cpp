#include "hero_projectile.h"
#include "GameManager.h"
void hero_projectile::update() {
	float dt = time->deltaTime;
	timer += dt;
	if (timer > 10) {
		gameobject->data->destory(gameobject);
	}
	gameobject->trans.transport(movedir * speed * dt);
	if (kindid == 0) {
		float mindis = 45;
		entity* emy = nullptr;
		for (int i = 0; i < gameobject->data->emy_list.length; i++) {
			if (distance(gameobject->trans.position, gameobject->data->emy_list[i].get()->trans.position) < mindis) {
				mindis = distance(gameobject->trans.position, gameobject->data->emy_list[i].get()->trans.position);
				emy = gameobject->data->emy_list[i].get();
			}
		}
		if (emy != nullptr) {
			emy->getComponent<npc>().blood -= hurt;
			gameobject->data->destory(gameobject);
		}
	}
	if (kindid == 1) {
		/*float mindis = 66;
		entity* emy = nullptr;
		for (int i = 0; i < gameobject->data->emy_list.length; i++) {
			if (distance(gameobject->trans.position, gameobject->data->emy_list[i].get()->trans.position) < mindis) {
				emy = gameobject->data->emy_list[i].get();
				gameobject->data->emy_list[i]->getComponent<npc>().blood -= hurt;
			}
		}
		if (emy != nullptr) {
			gameobject->data->destory(gameobject);
		}*/
		if (timer > 0.5f) {
			gameobject->data->destory(gameobject);
		}
	}	
}
void hero_projectile::lateupdate() {
	draw();
}
void hero_projectile::draw() {
	int w = canvas->getWidth();
	int h = canvas->getHeight();
	vector2D screenpos = gameobject->cam->worldPosToScreenPos(gameobject->trans.position);
	int x_ = screenpos.x;
	int y_ = screenpos.y;
	if (kindid == 0) {
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 16; x++) {
				canvas->drawCheck(static_cast<int>(x_ - 10 + x), static_cast<int>(y_ - 10 + y), 0, 0, 255, w, h);
			}
		}
	}
	if (kindid == 1) {
		for (int y = 0; y < 30; y++) {
			for (int x = 0; x < 30; x++) {
				canvas->drawCheck(static_cast<int>(x_ - 10 + x), static_cast<int>(y_ - 10 + y), 0, 10, 0, w, h);
			}
		}
	}
}