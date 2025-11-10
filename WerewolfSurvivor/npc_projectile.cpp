#include "npc_projectile.h"
#include "GameManager.h"
void npc_projectile::update() {
	float dt = time->deltaTime;
	timer += dt;
	if (timer > 10) {
		gameobject->data->destory(gameobject);
	}
	gameobject->trans.transport(movedir * speed * dt);
	if (distance(gameobject->trans.position, player->trans.position) < 12) {
		player->getComponent<hero>().blood -= hurt;
		gameobject->data->destory(gameobject);
	}
}
void npc_projectile::lateupdate() {
	draw();
}
void npc_projectile::draw() {
	int w = canvas->getWidth();
	int h = canvas->getHeight();
	vector2D screenpos = gameobject->cam->worldPosToScreenPos(gameobject->trans.position);
	int x_ = screenpos.x;
	int y_ = screenpos.y;
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			canvas->drawCheck(static_cast<int>(x_ - 10 + x), static_cast<int>(y_ - 10 + y),255,0,0,w,h);
		}
	}
}