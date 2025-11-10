#include "NPC.h"
#include "GameManager.h"
npc::npc() {
	id = 2;
	kindid = 0;
	blood = 20;
	hurt = 3;
	speed = 120;
	atk_gap = 1;
	atk_timer = 0;
	player = nullptr;
	sprite.load("Resources/npc_01.png");
	sprite.scaleImage(32, 32);
}
npc::npc(int kid) {
	id = 2;
	switch (kid)
	{
	case 0:
		kindid = 0;
		blood = 20;
		hurt = 3;
		speed = 120;
		atk_gap = 1;
		atk_timer = 0;
		player = nullptr;
		sprite.load("Resources/npc_01.png");
		sprite.scaleImage(32, 32);
		break;
	case 1:
		kindid = 1;
		blood = 30;
		hurt = 2;
		speed = 60;
		atk_gap = 2.5f;
		atk_timer = 0;
		player = nullptr;
		sprite.load("Resources/npc_02.png");
		sprite.scaleImage(45, 45);
		break;
	case 2:
		kindid = 2;
		blood = 50;
		hurt = 2;
		speed = 100;
		atk_gap = 1;
		atk_timer = 0;
		player = nullptr;
		sprite.load("Resources/npc_03.png");
		sprite.scaleImage(36, 36);
		break;
	case 3:
		kindid = 3;
		blood = 80;
		hurt = 4;
		speed = 75;
		atk_gap = 1;
		atk_timer = 0;
		player = nullptr;
		sprite.load("Resources/npc_04.png");
		sprite.scaleImage(50, 50);
		break;
	default:
		break;
	}
}
void npc::update() {
	if (blood <= 0) {
		gameobject->data->score++;
		gameobject->data->destory(gameobject);
	}
	float dt = time->deltaTime;
	atk_timer += dt;
	vector2D dir = direction(gameobject->trans.position, player->trans.position);
	switch (kindid)
	{
	case 0:
		if (distance(gameobject->trans.position, player->trans.position) > 5) {
			gameobject->trans.transport(dir * speed * dt);
			//std::cout << player->trans.position.x<<',' << player->trans.position.y << std::endl;
			//std::cout << (direction(gameobject->trans.position, player->trans.position) * speed * time->dt()).magnitude() << std::endl;
		}
		if (distance(gameobject->trans.position, player->trans.position) < 12)
		{
			if (atk_timer > atk_gap) {
				atk_timer = 0;
				player->getComponent<hero>().blood -= hurt;
			}
		}
		break;
	case 1:
		if (distance(gameobject->trans.position, player->trans.position) > 450) {
			gameobject->trans.transport(dir * speed * dt);
		}
		if (gameobject->cam->inCamera(gameobject->trans.position)) {
			if (atk_timer > atk_gap) {
				atk_timer = 0;
				auto np = std::make_shared<entity>(4, *gameobject->cam, *gameobject->data);
				auto npc_p = std::make_shared<npc_projectile>(hurt,gameobject->trans.position,dir,*player);
				npc_p->awake(*canvas, *time);
				np->addComponent(npc_p);
				np->trans.position = gameobject->trans.position;
				gameobject->data->npc_projectiles.add(np);
			}
		}
		break;
	case 2:
		if (distance(gameobject->trans.position, player->trans.position) > 5) {
			gameobject->trans.transport(dir * speed * dt);
		}
		if (distance(gameobject->trans.position, player->trans.position) < 12)
		{
			if (atk_timer > atk_gap) {
				atk_timer = 0;
				player->getComponent<hero>().blood -= hurt;
			}
		}
		break;
	case 3:
		if (distance(gameobject->trans.position, player->trans.position) > 5) {
			gameobject->trans.transport(dir * speed * dt);
		}
		if (distance(gameobject->trans.position, player->trans.position) < 15)
		{
			if (atk_timer > atk_gap) {
				atk_timer = 0;
				player->getComponent<hero>().blood -= hurt;
			}
		}
		break;
	default:
		break;
	}	
}
void npc::lateupdate() {
	draw();
}
void npc::draw() {
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