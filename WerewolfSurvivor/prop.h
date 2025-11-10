#pragma once
#include "Behavior.h"
#include "hero.h"
#include "Entity.h"
class prop :public behavior {
public:
	GamesEngineeringBase::Image sprite;
	int kindid;
	entity* player;
public:
	prop(int kid):kindid(kid){
		switch (kid)
		{
		case 0:
			sprite.load("Resources/prop_01.png");
			sprite.scaleImage(32, 32);
			break;
		case 1:
			sprite.load("Resources/prop_02.png");
			sprite.scaleImage(32, 32);
			break;
		default:
			break;
		}
		player = nullptr;
	}
	void update();
	void lateupdate();
	void draw();
};