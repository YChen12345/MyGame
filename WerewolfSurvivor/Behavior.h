#pragma once
#include "GamesengineeringBase.h"
#include "Camera.h"
class entity;

//#include "GamesEngineeringBase.h"
class behavior {
public:
	int id;
	GamesEngineeringBase::Window* canvas = nullptr;
	GamesEngineeringBase::Timer* time = nullptr;
	entity* gameobject= nullptr;
public:
	void setGameobject(entity* e) {
		gameobject = e;
	}
	void awake(GamesEngineeringBase::Window& cs, GamesEngineeringBase::Timer& t)
	{
		canvas = &cs;
		time = &t;
	}
	virtual void update() = 0;          
	virtual void lateupdate() = 0;
	virtual ~behavior() = default;      
};