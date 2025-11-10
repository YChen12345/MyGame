#include "TileMap.h"
#include "hero.h"

tile::tile() {}
void tile::load(std::string filename) {
	sprite.load(filename);
	tsx = sprite.width;
	tsy = sprite.height;
}
void tile::load(std::string filename, int sizex, int sizey) {
	sprite.load(filename);
	sprite.scaleImage(sizex, sizey);
	tsx = sizex;
	tsy = sizey;
}
void tile::draw(GamesEngineeringBase::Window& canvas, int x, int y) {
	for (unsigned int i = 0; i < sprite.height; i++) {
		// bounds checking goes here
		if (y + i >= 0 && (y + i) < (canvas.getHeight())) {
			for (unsigned int j = 0; j < sprite.width; j++)
				if (x + j >= 0 && (x + j) < (canvas.getWidth())) {
					canvas.drawCheck(x + j, y + i, sprite.at(j, i), canvas.getWidth(), canvas.getHeight());
				}
		}
	}
	if (kindid == 0) {
		if (player != nullptr) {
			if (x > 0 && x < canvas.getWidth() && y>0 && y < canvas.getHeight()) {
				vector2D scpos = vector2D(x +  tsx/ 2, y + tsy / 2);
				vector2D player_nextpos = player->cam->worldPosToScreenPos(player->getComponent<hero>().nextpos);
				vector2D player_nextpos_x = player->cam->worldPosToScreenPos(player->getComponent<hero>().nextpos_x);
				vector2D player_nextpos_y = player->cam->worldPosToScreenPos(player->getComponent<hero>().nextpos_y);
				if (player->getComponent<hero>().blocked != 1) {
					if (abs(scpos.x - player_nextpos.x) < 1 + tsx / 2 && abs(scpos.y - player_nextpos.y) < 1 + tsy / 2) {
						player->getComponent<hero>().blocked = 1;
					}
				}
				if (player->getComponent<hero>().blocked_x != 1) {
					if (abs(scpos.x - player_nextpos_x.x) < 1 + tsx / 2 && abs(scpos.y - player_nextpos_x.y) < 1 + tsy / 2) {
						player->getComponent<hero>().blocked_x = 1;
					}
				}
				if (player->getComponent<hero>().blocked_y != 1) {
					if (abs(scpos.x - player_nextpos_y.x) < 1 + tsx / 2 && abs(scpos.y - player_nextpos_y.y) < 1 + tsy / 2) {
						player->getComponent<hero>().blocked_y = 1;
					}
				}			
			}
		}	
	}
}
tileSet::tileSet(int s, int sizex, int sizey, entity* p, std::string pre) :size(s) {
	for (int i = 0; i < size; i++) {
		std::string filename;
		filename = "Resources/" + pre + std::to_string(i) + ".png";
		t[i].load(filename, sizex, sizey);
		t[i].kindid = i;
		t[i].player = p;
	}
}
int tileSet::getSize() {
	return size;
}
tile& tileSet::operator[](unsigned int index) { return t[index]; }

tileMap::tileMap(int s, int msx, int msy, int tsx, int tsy,entity* p,int kind) :ts(s, tsx, tsy,p), alphas(s, tsx, tsy,p, "alpha") {
	tile_sizex = tsx;
	tile_sizey = tsy;
	map_sizex = msx;
	map_sizey = msy;
	///
	if (kind == 0) {
		std::ifstream fin("Resources/map_finite.txt");
		fin >> map_sizex;
		fin >> map_sizey;
		for (unsigned int i = 0; i < map_sizex * map_sizey; i++) {
			if (!(fin >> tarray[i])) {
				return;
			}
		}
		fin.close();
	}
	if (kind == 1) {
		std::ifstream fin("Resources/map_infinite.txt");
		fin >> map_sizex;
		fin >> map_sizey;
		for (unsigned int i = 0; i < map_sizex * map_sizey; i++) {
			if (!(fin >> tarray[i])) {
				return;
			}
		}
		fin.close();
	}	
}

void tileMap::randomMap() {
	for (unsigned int i = 0; i < mapSize; i++) {
		tarray[i] = rand() % ts.getSize();
	}
}

void tileMap::draw(GamesEngineeringBase::Window& canvas, int x, int y) {
	int offsetX = -x % tile_sizex;
	int X = -x / tile_sizex;
	int offsetY = y % tile_sizey;
	int Y = y / tile_sizey;
	int xAmount = ceilDiv(canvas.getWidth(), tile_sizex);
	int yAmount = ceilDiv(canvas.getHeight(), tile_sizey);
	int xx = 0;
	int yy = 0;
	if (X > 0) {
		xx = map_sizex - X % map_sizex;
	}
	else
	{
		xx = abs(X);
	}
	if (Y > 0) {
		yy = map_sizey - Y % map_sizey;
	}
	else
	{
		yy = abs(Y);
	}
	for (int i = 0; i < yAmount + 2; i++) {
		for (int j = 0; j < xAmount + 2; j++) {
			int yyy = (yy % map_sizey + i) % map_sizey;
			int xxx = (xx % map_sizex + j) % map_sizex;
			ts[tarray[yyy * map_sizex + xxx]].draw(canvas, static_cast<int>(tile_sizex) * (j - 1) + offsetX, static_cast<int>(tile_sizey) * (i - 1) + offsetY);
			/*std::cout <<'(' << xx << ',' << yy << ')';
			std::cout << '[' << static_cast<int>(tile_sizex) * (j - 1) + offsetX << ',' << static_cast<int>(tile_sizey) * (i - 1) + offsetY << ']' << '|';*/
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;
	/*ts[tarray[Y % mapSize]].draw(canvas, (canvas.getHeight() / 2) + offset);
	ts[tarray[(Y + 1) % mapSize]].draw(canvas, offset);
	ts[tarray[(Y + 2) % mapSize]].draw(canvas, offset - (canvas.getHeight() / 2));*/
}

void tileMap::drawAlphas(GamesEngineeringBase::Window& canvas, int x, int y) {
	int offsetX = -x % tile_sizex;
	int X = -x / tile_sizex;
	int offsetY = y % tile_sizey;
	int Y = y / tile_sizey;
	int xAmount = ceilDiv(canvas.getWidth(), tile_sizex);
	int yAmount = ceilDiv(canvas.getHeight(), tile_sizey);
	int xx = 0;
	int yy = 0;
	if (X > 0) {
		xx = map_sizex - X % map_sizex;
	}
	else
	{
		xx = abs(X);
	}
	if (Y > 0) {
		yy = map_sizey - Y % map_sizey;
	}
	else
	{
		yy = abs(Y);
	}
	for (int i = 0; i < yAmount + 2; i++) {
		for (int j = 0; j < xAmount + 2; j++) {
			int yyy = (yy % map_sizey + i) % map_sizey;
			int xxx = (xx % map_sizex + j) % map_sizex;
			alphas[tarray[yyy * map_sizex + xxx]].draw(canvas, static_cast<int>(tile_sizex) * (j - 1) + offsetX, static_cast<int>(tile_sizey) * (i - 1) + offsetY);
			/*std::cout <<'(' << xx << ',' << yy << ')';
			std::cout << '[' << static_cast<int>(tile_sizex) * (j - 1) + offsetX << ',' << static_cast<int>(tile_sizey) * (i - 1) + offsetY << ']' << '|';*/
		}
		//std::cout << std::endl;
	}
}