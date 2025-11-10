#pragma once
#include "Behavior.h"
#include "NPC.h"
#include "hero.h"
#include "Entity.h"

class hero_projectile :public behavior {
public:
	vector2D movedir;
	float speed;
	int hurt;
	float timer;
	int kindid;
public:
	hero_projectile(int h, vector2D pos, vector2D dir) {
		hurt = h;
		movedir = dir;
		speed = 400;
		timer = 0;
		kindid = 0;
	}
	hero_projectile(int h, vector2D pos, vector2D dir,int kid) {
		hurt = h;
		movedir = dir;
		speed = 400;
		timer = 0;
		kindid = kid;
	}
	~hero_projectile() = default;
	void update();
	void lateupdate();
	void draw();
};
