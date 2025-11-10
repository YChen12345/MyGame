#pragma once
#include "GamesengineeringBase.h"
#include "Mathf.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Behavior.h"
#include "Entity.h"
#include "TileMap.h"
#include "Camera.h"
#include "List.h"
#include "Container.h"
#include "hero.h"
#include "NPC.h"
#include "prop.h"
#include "GameData.h";

class gameSystem {
public:
	GamesEngineeringBase::Window* canvas = nullptr;
	GamesEngineeringBase::Timer* time = nullptr;
	int sceneid;
	int state;
	int mapchoice;
	float totaltime;
	float timer;
	float timer_prop;
	int second;
	int score;
	float createThreshold;
	int previousKeyButton[256] = { 0 };
	gamedata gd;
	camera cam;
	entity player;
	std::unique_ptr<tileMap> tmap_infinite;
	std::unique_ptr<tileMap> tmap_finite;
	container<std::shared_ptr<entity>> emy_list;
	container<std::shared_ptr<entity>> player_projectiles;
	container<std::shared_ptr<entity>> npc_projectiles;
	container<std::shared_ptr<entity>> props;
	GamesEngineeringBase::Image startpage;
	GamesEngineeringBase::Image choosemappage;
	GamesEngineeringBase::Image selectarrow;
	GamesEngineeringBase::Image win;
	GamesEngineeringBase::Image lose;
public:
	gameSystem(GamesEngineeringBase::Window& canvas,GamesEngineeringBase::Timer& t);
	void initgame();
	void gameloop();
	void keycontrol();
	void destory(entity* e);
	void record();
	void load();
	void game_finitemap();
	void game_infinitemap();

};