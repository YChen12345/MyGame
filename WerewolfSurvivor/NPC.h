#pragma once
#include "Behavior.h"
#include "Entity.h"
#include "hero.h"
#include "npc_projectile.h"
class npc :public behavior {
public:
	GamesEngineeringBase::Image sprite;
	int kindid;
	float speed;
	int blood;
	int hurt;
	float atk_timer;
	float atk_gap;
	entity* player;
public:
	npc();
	npc(int kid);
	~npc() = default;
	void update();
	void lateupdate();
	void draw();

};