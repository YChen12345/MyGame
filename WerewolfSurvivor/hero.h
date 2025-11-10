#pragma once
#include "Behavior.h"
#include "hero_projectile.h"
#include "npc_projectile.h"

class hero :public behavior {
public:
	GamesEngineeringBase::Image sprite;
	GamesEngineeringBase::Image skill;
	float speed;
	int maxblood;
	int blood;
	int hurt;
	float atk_gap;
	float skill_gap;
	float atk_timer;
	float skill_timer;
	int skill_level;
	int blocked;
	int blocked_x;
	int blocked_y;
	vector2D nextpos;
	vector2D nextpos_x;
	vector2D nextpos_y;
public:
	hero();
	~hero()=default;
	void update();
	void lateupdate();
	void draw();
	void drawBlood();
	void drawSkill();
	void drawTime();
};