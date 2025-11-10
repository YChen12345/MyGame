#include "hero.h"
#include "GameManager.h"
#include "Entity.h"
hero::hero(){
	id = 1;
	maxblood = 20;
	blood = 20;
	hurt = 24;
	speed = 150;
	atk_gap = 1;
	skill_gap = 6;
	atk_timer = 0;
	skill_timer = 1;
	skill_level = 3;
	blocked = 0;
	nextpos = vector2D(zero);
	nextpos_x = vector2D(zero);
	nextpos_y = vector2D(zero);

	sprite.load("Resources/werewolf_hero.png");
	sprite.scaleImage(32, 32);
	skill.load("Resources/skill_01.png");
	skill.scaleImage(120, 120);
}
void hero::update() {
	if (blood > maxblood) {
		blood = maxblood;
	}
	if (time != nullptr&&canvas!=nullptr) {
		float dt = time->deltaTime;
		atk_timer += dt;
		skill_timer += dt;
		float mindis=380;
		entity* emy=nullptr;
		if (atk_timer > atk_gap) {
			for (int i = 0; i < gameobject->data->emy_list.length; i++) {
				if (distance(gameobject->trans.position, gameobject->data->emy_list[i].get()->trans.position)<mindis) {
					mindis = distance(gameobject->trans.position, gameobject->data->emy_list[i].get()->trans.position);
					emy = gameobject->data->emy_list[i].get();
				}
			}
			if (emy != nullptr) {
				atk_timer = 0;
				auto pp = std::make_shared<entity>(3, *gameobject->cam, *gameobject->data);
				auto hero_p = std::make_shared<hero_projectile>(hurt, gameobject->trans.position, direction(gameobject->trans.position, emy->trans.position));
				hero_p->awake(*canvas, *time);
				pp->addComponent(hero_p);
				pp->trans.position = gameobject->trans.position;
				gameobject->data->player_projectiles.add(pp);
			}		
		}
		if (canvas->keyPressed('H')) {
			blood = maxblood;
		}
		if (canvas->keyPressed('K')) {
			if (skill_timer > skill_gap) {
				skill_timer = 0;
				int blood[150] = { 0 };
				vector2D dir[150] = {randomVec2d()};
				entity* es[150] = {nullptr};
				int emy_amount = gameobject->data->emy_list.length;
				int bullet_amount = min(skill_level, emy_amount);
				for (int i = 0; i < emy_amount; i++) {
					if (gameobject->cam->inCamera(gameobject->data->emy_list[i]->trans.position)) {
						blood[i] = gameobject->data->emy_list[i]->getComponent<npc>().blood;
						dir[i] = direction(gameobject->trans.position, gameobject->data->emy_list[i]->trans.position);
						es[i] = gameobject->data->emy_list[i].get();
					}			
				}
				for (int i = 0; i < skill_level; i++) {
					int maxbl=0;
					for (int j = i; j < emy_amount; j++) {
						if (blood[j] > maxbl) {
							maxbl = blood[j];
							int v = blood[i];
							blood[i] = blood[j];
							blood[j] = v;
							vector2D d = dir[i];
							dir[i] = dir[j];
							dir[j] = dir[i];
							entity* e = es[i];
							es[i] = es[j];
							es[j] = es[i];
						}
					}
				}
				for (int i = 0; i < bullet_amount; i++) {
					if (es[i] != nullptr) {
						es[i]->getComponent<npc>().blood -= 5 * hurt;
						auto pp = std::make_shared<entity>(3, *gameobject->cam, *gameobject->data);
						//auto hero_p = std::make_shared<hero_projectile>(5*hurt, gameobject->trans.position, dir[i], 1);
						auto hero_p = std::make_shared<hero_projectile>(5 * hurt, gameobject->trans.position, vector2D(zero), 1);
						hero_p->awake(*canvas, *time);
						pp->addComponent(hero_p);
						pp->trans.position = es[i]->trans.position;
						//pp->trans.position = gameobject->trans.position;
						gameobject->data->player_projectiles.add(pp);
					}				
				}
			}
		}
		if (blocked == 0) {
			gameobject->trans.position=nextpos;
			nextpos = gameobject->trans.position;
			nextpos_x = gameobject->trans.position;
			nextpos_y = gameobject->trans.position;
		}
		else{
			if (blocked_x == 0) {
				gameobject->trans.position = nextpos_x;
			}
			else
			{
				if (blocked_y == 0) {
					gameobject->trans.position = nextpos_y;
				}
			}
		}
		blocked = 0;
		blocked_x = 0;
		blocked_y = 0;
		nextpos = gameobject->trans.position;
		nextpos_x = gameobject->trans.position;
		nextpos_y = gameobject->trans.position;
		if ((canvas->keyPressed('W') && canvas->keyPressed('A'))
			||(canvas->keyPressed(VK_UP)&&canvas->keyPressed(VK_LEFT))) {
			nextpos = gameobject->trans.position + (vector2D(up) + vector2D(left)).normalize() * speed * dt;
			nextpos_x = gameobject->trans.position + vector2D(left) * speed * dt;
			nextpos_y = gameobject->trans.position + vector2D(up) * speed * dt;
		}
		else if ((canvas->keyPressed('W') && canvas->keyPressed('D')) 
			|| (canvas->keyPressed(VK_UP) && canvas->keyPressed(VK_RIGHT))) {
			nextpos = gameobject->trans.position + (vector2D(up) + vector2D(right)).normalize() * speed * dt;
			nextpos_x = gameobject->trans.position + vector2D(right) * speed * dt;
			nextpos_y = gameobject->trans.position + vector2D(up) * speed * dt;
		}
		else if ((canvas->keyPressed('S') && canvas->keyPressed('A')) 
			|| (canvas->keyPressed(VK_DOWN) && canvas->keyPressed(VK_LEFT))) {
			nextpos = gameobject->trans.position + (vector2D(down) + vector2D(left)).normalize() * speed * dt;
			nextpos_x = gameobject->trans.position + vector2D(left) * speed * dt;
			nextpos_y = gameobject->trans.position + vector2D(down) * speed * dt;
		}
		else if ((canvas->keyPressed('S') && canvas->keyPressed('D')) 
			|| (canvas->keyPressed(VK_DOWN) && canvas->keyPressed(VK_RIGHT))) {
			nextpos = gameobject->trans.position + (vector2D(down) + vector2D(right)).normalize() * speed * dt;
			nextpos_x = gameobject->trans.position + vector2D(right) * speed * dt;
			nextpos_y = gameobject->trans.position + vector2D(down) * speed * dt;
		}
		else if (canvas->keyPressed('W')||canvas->keyPressed(VK_UP)) {
			nextpos = gameobject->trans.position + vector2D(up) * speed * dt;
			nextpos_x = nextpos;
			nextpos_y = nextpos;
		}
		else if (canvas->keyPressed('S') || canvas->keyPressed(VK_DOWN)) {
			nextpos = gameobject->trans.position + vector2D(down) * speed * dt;
			nextpos_x = nextpos;
			nextpos_y = nextpos;
		}
		else if (canvas->keyPressed('A') || canvas->keyPressed(VK_LEFT)) {
			nextpos = gameobject->trans.position + vector2D(left) * speed * dt;
			nextpos_x = nextpos;
			nextpos_y = nextpos;
		}
		else if (canvas->keyPressed('D') || canvas->keyPressed(VK_RIGHT)) {
			nextpos = gameobject->trans.position + vector2D(right) * speed * dt;
			nextpos_x = nextpos;
			nextpos_y = nextpos;
		}
	}
}
void hero::lateupdate() {
	draw();
	drawBlood();
	drawSkill();
	drawTime();
}
void hero::draw() {
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
void hero::drawBlood() {
	int maxbloodline_length = 400;
	int bloodline_length = maxbloodline_length*blood/maxblood;
	for (int y = 45; y < 70; y++) {
		for (int x = 312; x < 312+maxbloodline_length; x++) {
			canvas->draw(x, y, 128, 128, 128);
		}
	}
	for (int y = 45; y < 70; y++) {
		for (int x = 312; x < 312 + bloodline_length; x++) {
			canvas->draw(x, y, 255, 0, 0);
		}
	}
}
void hero::drawSkill() {
	int maxline_length = 120;
	int line_length = maxline_length * max(0,(skill_gap-skill_timer)) / skill_gap;
	for (int y = 0; y < skill.height; y++) {
		for (int x = 0; x < skill.width; x++) {
			if (skill.alphaAt(x, y) > 0) {
				canvas->drawCheck(x + 60, y + 600, skill.at(x, y), canvas->getWidth(), canvas->getHeight());
			}
		}
	}
	for (int y = 600; y < 600 + line_length; y++) {
		for (int x = 60; x < 180; x++) {
			canvas->draw(x, y, 128, 128, 128);
		}
	}
}
void hero::drawTime() {
	int maxtimeline_length = 120;
	int timeline_length = maxtimeline_length * gameobject->data->totaltime / 180;
	for (int y = 45; y < 70; y++) {
		for (int x = 800; x < 800 + maxtimeline_length; x++) {
			canvas->draw(x, y, 60, 60, 60);
		}
	}
	for (int y = 45; y < 70; y++) {
		for (int x = 800; x < 800 + timeline_length; x++) {
			canvas->draw(x, y, 204, 204, 0);
		}
	}
}