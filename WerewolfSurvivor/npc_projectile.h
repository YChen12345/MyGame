#pragma once
#include "Behavior.h"
#include "hero.h"
#include "Entity.h"
class npc_projectile:public behavior {
public:
	entity* player;
	vector2D movedir;
	float speed;
	int hurt;
	float timer;
public:
	npc_projectile(int h,vector2D pos,vector2D dir,entity& p) {
		hurt = h;
		movedir = dir;
		speed = 400;
		player = &p;
		timer = 0;
	}
	~npc_projectile() = default;
	void update();
	void lateupdate();
	void draw();
};
