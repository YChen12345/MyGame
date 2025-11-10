#pragma once
#include "GamesEngineeringBase.h"
#include "Mathf.h"
#include "Entity.h"
#include<fstream>
class tile {
public:
	GamesEngineeringBase::Image sprite;
	entity* player;
	int kindid;
	int tsx;
	int tsy;
public:
	tile();
	void load(std::string filename);
	void load(std::string filename, int sizex, int sizey);
	void draw(GamesEngineeringBase::Window& canvas, int x, int y);
};
class tileSet {
	int size;
	tile t[1000];
public:
	tileSet(int s, int sizex, int sizey, entity* p, std::string pre = "");
	int getSize();
	tile& operator[](unsigned int index);
};
const int mapSize = 10000;
class tileMap {

	tileSet ts;
	tileSet alphas;
	int map_sizex;
	int map_sizey;
	//size of each tile
	int tile_sizex;
	int tile_sizey;
public:
	unsigned int tarray[mapSize] = { 0 };
public:
	tileMap(int s, int msx, int msy, int tsx, int tsy,entity* p,int kind=0);

	void randomMap();
	void draw(GamesEngineeringBase::Window& canvas, int x, int y);
	void drawAlphas(GamesEngineeringBase::Window& canvas, int x, int y);
};