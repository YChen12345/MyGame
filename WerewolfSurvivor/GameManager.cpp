#include "GameManager.h"

gameSystem::gameSystem(GamesEngineeringBase::Window& cs, GamesEngineeringBase::Timer& t) {
	canvas = &cs;
	time = &t;
	sceneid = 0;
	state = 0;
	totaltime = 0;
	second = 0;
	score = 0;
	mapchoice = 0;
	createThreshold = 3.0f;
	startpage.load("Resources/werewolf.png");
	startpage.scaleImage(1024,768);
	choosemappage.load("Resources/werewolf_02.png");
	choosemappage.scaleImage(1024, 768);
	selectarrow.load("Resources/tip_01.png");
	win.load("Resources/win.png");
	win.scaleImage(1024, 768);
	lose.load("Resources/lose.png");
	lose.scaleImage(1024, 768);
}
void gameSystem::initgame() {
	state = 0;
	totaltime = 0;
	mapchoice = 0;
	second = 0;
	score = 0;
	createThreshold = 3.0f;
	cam.trans.position = vector2D(zero);
	auto player_role= std::make_shared<hero>();
	player_role.get()->awake(*canvas, *time);
	player.init(1,cam, *this);
	player.addComponent(player_role);
	emy_list.clear();
	player_projectiles.clear();
	npc_projectiles.clear();
	props.clear();
	tmap_finite = std::make_unique<tileMap>(4, 100, 100, 32, 32, &player,0);
	tmap_infinite = std::make_unique<tileMap>(4, 100, 100, 32, 32, &player, 1);
}
void gameSystem::gameloop() {
	float dt = time->deltaTime;
	for (int i = 0; i < emy_list.length; i++) {
		if (emy_list[i]->active == 1) {
			emy_list.removeAt(i);
		}
	}
	for (int i = 0; i < player_projectiles.length; i++) {
		if (player_projectiles[i]->active == 1) {
			player_projectiles.removeAt(i);
		}
	}
	for (int i = 0; i < npc_projectiles.length; i++) {
		if (npc_projectiles[i]->active == 1) {
			npc_projectiles.removeAt(i);
		}
	}
	for (int i = 0; i < props.length; i++) {
		if (props[i]->active == 1) {
			props.removeAt(i);
		}
	}
	switch (sceneid)
	{
	case 0://start page
		canvas->clear();
		for (int y = 0; y < startpage.height; y++) {
			for (int x = 0; x < startpage.width; x++) {
				if (startpage.alphaAt(x, y) > 0) {
					canvas->drawCheck(x, y, startpage.at(x, y), canvas->getWidth(), canvas->getHeight());
				}
			}
		}
		if (canvas->keyPressed(VK_SPACE)&& previousKeyButton[VK_SPACE] == 1) {
			sceneid = 1;
		}
		if (canvas->keyPressed(VK_RETURN) && previousKeyButton[VK_RETURN] == 1) {
			sceneid = 1;
		}
		canvas->present();
		break;
	case 1://choose map
		canvas->clear();
		for (int y = 0; y < choosemappage.height; y++) {
			for (int x = 0; x < choosemappage.width; x++) {
				if (choosemappage.alphaAt(x, y) > 0) {
					canvas->drawCheck(x, y, choosemappage.at(x, y), canvas->getWidth(), canvas->getHeight());
				}
			}
		}
		if (mapchoice == 0) {
			for (int y = 0; y < selectarrow.height; y++) {
				for (int x = 0; x < selectarrow.width; x++) {
					if (selectarrow.alphaAt(x, y) > 0) {
						canvas->drawCheck(210+x, 175+y, selectarrow.at(x, y), canvas->getWidth(), canvas->getHeight());
					}
				}
			}
		}
		if (mapchoice == 1) {
			for (int y = 0; y < selectarrow.height; y++) {
				for (int x = 0; x < selectarrow.width; x++) {
					if (selectarrow.alphaAt(x, y) > 0) {
						canvas->drawCheck(480+x, 175+y, selectarrow.at(x, y), canvas->getWidth(), canvas->getHeight());
					}
				}
			}
		}
		if (mapchoice == 2) {
			for (int y = 0; y < selectarrow.height; y++) {
				for (int x = 0; x < selectarrow.width; x++) {
					if (selectarrow.alphaAt(x, y) > 0) {
						canvas->drawCheck(750 + x, 175 + y, selectarrow.at(x, y), canvas->getWidth(), canvas->getHeight());
					}
				}
			}
		}
		if (canvas->keyPressed('1')) {
			mapchoice = 0;
		}
		if (canvas->keyPressed('2')) {
			mapchoice = 1;
		}
		if (canvas->keyPressed('3')) {
			mapchoice = 2;
		}
		if (mapchoice == 0) {
			if ((canvas->keyPressed('D')&&previousKeyButton['D'] == 1)
				|| (canvas->keyPressed(VK_RIGHT) && previousKeyButton[VK_RIGHT] == 1)) {
				mapchoice = 1;
			}
		}
		else if (mapchoice == 1) {
			if ((canvas->keyPressed('D') && previousKeyButton['D'] == 1)
				|| (canvas->keyPressed(VK_RIGHT) && previousKeyButton[VK_RIGHT] == 1)) {
				mapchoice = 2;
			}
		}
		if (mapchoice == 2) {
			if ((canvas->keyPressed('A') && previousKeyButton['A'] == 1)
				|| (canvas->keyPressed(VK_LEFT) && previousKeyButton[VK_LEFT] == 1)) {
				mapchoice = 1;
			}
		}
		else if (mapchoice == 1) {
			if ((canvas->keyPressed('A') && previousKeyButton['A'] == 1)
				|| (canvas->keyPressed(VK_LEFT) && previousKeyButton[VK_LEFT] == 1)) {
				mapchoice = 0;
			}
		}
		if ((canvas->keyPressed(VK_SPACE) && previousKeyButton[VK_SPACE] == 1)
			|| (canvas->keyPressed(VK_RETURN) && previousKeyButton[VK_RETURN] == 1)) {
			if (mapchoice == 0) {
				sceneid = 2;
			}
			else if(mapchoice==1)
			{
				sceneid = 3;
			}
			else if (mapchoice == 2)
			{
				load();
			}
		}
		canvas->present();
		break;
	case 2://finite
		game_finitemap();
		break;
	case 3://infinite
		game_infinitemap();
		break;
	case 4://win
		if (state == 0) {
			state = 1;
			std::cout << "win! " << std::endl;
			std::cout << "score: " << score <<std::endl;
			std::cout << "Player Level: " << player.getComponent<hero>().skill_level-2 << std::endl;
			std::cout << "fps: " << static_cast<int>(1.f/dt) <<std::endl;
		}
		canvas->clear();
		for (int y = 0; y < win.height; y++) {
			for (int x = 0; x < win.width; x++) {
				if (win.alphaAt(x, y) > 0) {
					canvas->drawCheck(x, y, win.at(x, y), canvas->getWidth(), canvas->getHeight());
				}
			}
		}
		if (canvas->keyPressed(VK_SPACE) && previousKeyButton[VK_SPACE] == 1) {
			initgame();
			sceneid = 0;
		}
		if (canvas->keyPressed(VK_RETURN) && previousKeyButton[VK_RETURN] == 1) {
			initgame();
			sceneid = 0;
		}
		canvas->present();
		break;
	case 5://game over
		if (state == 0) {
			state = 1;
			std::cout << "lose! " << std::endl;
			std::cout << "score: " << score << std::endl;
			std::cout << "Player Level: " << player.getComponent<hero>().skill_level-2 << std::endl;
			std::cout << "fps: " << static_cast<int>(1.f / dt) << std::endl;
		}
		canvas->clear();
		for (int y = 0; y < lose.height; y++) {
			for (int x = 0; x < lose.width; x++) {
				if (lose.alphaAt(x, y) > 0) {
					canvas->drawCheck(x, y, lose.at(x, y), canvas->getWidth(), canvas->getHeight());
				}
			}
		}
		if (canvas->keyPressed(VK_SPACE) && previousKeyButton[VK_SPACE] == 1) {
			initgame();
			sceneid = 0;
		}
		if (canvas->keyPressed(VK_RETURN) && previousKeyButton[VK_RETURN] == 1) {
			initgame();
			sceneid = 0;
		}
		canvas->present();
		break;
	default:
		break;
	}
}
void gameSystem::destory(entity* e) {
	e->active = 1;
}
void gameSystem::record() {
	gd.scenceid = sceneid;
	gd.state = state;
	gd.totaltime = totaltime;
	gd.createThreshold = createThreshold;
	gd.cam_pos_x = cam.trans.position.x;
	gd.cam_pos_y = cam.trans.position.y;
	gd.player_pos_x = player.trans.position.x;
	gd.player_pos_y = player.trans.position.y;
	gd.player_atkgap = player.getComponent<hero>().atk_gap;
	gd.player_atktimer = player.getComponent<hero>().atk_timer;
	gd.player_blood = player.getComponent<hero>().blood;
	gd.player_skill_level = player.getComponent<hero>().skill_level;
	gd.player_skillgap = player.getComponent<hero>().skill_gap;
	gd.player_skilltimer = player.getComponent<hero>().skill_timer;
	gd.emynum = emy_list.length;
	gd.propnum = props.length;
	gd.emy_bullet_num = npc_projectiles.length;
	gd.player_bullet_num = player_projectiles.length;
	for (int i = 0; i < emy_list.length;i++) {
		gd.emykid[i] = emy_list[i]->getComponent<npc>().kindid;
		gd.emyblood[i] = emy_list[i]->getComponent<npc>().blood;
		gd.emypos_x[i] = emy_list[i]->trans.position.x;
		gd.emypos_y[i] = emy_list[i]->trans.position.y;
	}	
	for (int i = 0; i < props.length; i++) {
		gd.propkid[i] = props[i]->getComponent<prop>().kindid;
		gd.proppos_x[i] = props[i]->trans.position.x;
		gd.proppos_y[i] = props[i]->trans.position.y;
	}
	for (int i = 0; i < npc_projectiles.length; i++) {
		gd.eb_hurt[i] = npc_projectiles[i]->getComponent<npc_projectile>().hurt;
		gd.eb_timer[i] = npc_projectiles[i]->getComponent<npc_projectile>().timer;
		gd.eb_pos_x[i] = npc_projectiles[i]->trans.position.x;
		gd.eb_pos_y[i] = npc_projectiles[i]->trans.position.y;
		gd.eb_dir_x[i] = npc_projectiles[i]->getComponent<npc_projectile>().movedir.x;
		gd.eb_dir_y[i] = npc_projectiles[i]->getComponent<npc_projectile>().movedir.y;
	}
	for (int i = 0; i < player_projectiles.length; i++) {
		gd.pb_kid[i] = player_projectiles[i]->getComponent<hero_projectile>().kindid;
		gd.pb_hurt[i] = player_projectiles[i]->getComponent<hero_projectile>().hurt;
		gd.pb_timer[i] = player_projectiles[i]->getComponent<hero_projectile>().timer;
		gd.pb_pos_x[i] = player_projectiles[i]->trans.position.x;
		gd.pb_pos_y[i] = player_projectiles[i]->trans.position.y;
		gd.pb_dir_x[i] = player_projectiles[i]->getComponent<hero_projectile>().movedir.x;
		gd.pb_dir_y[i] = player_projectiles[i]->getComponent<hero_projectile>().movedir.y;
	}
	gd.save();
	
}
void gameSystem::load() {
	gd.load();
	sceneid = gd.scenceid;
	state = gd.state;
	totaltime = gd.totaltime;
	createThreshold = gd.createThreshold;
	cam.trans.position.x = gd.cam_pos_x;
	cam.trans.position.y = gd.cam_pos_y;
	player.trans.position.x = gd.player_pos_x;
	player.trans.position.y = gd.player_pos_y;
	player.getComponent<hero>().nextpos = player.trans.position;
	player.getComponent<hero>().nextpos_x = player.trans.position;
	player.getComponent<hero>().nextpos_y = player.trans.position;
	player.getComponent<hero>().atk_gap = gd.player_atkgap;
	player.getComponent<hero>().atk_timer = gd.player_atktimer;
	player.getComponent<hero>().blood = gd.player_blood;
	player.getComponent<hero>().skill_level = gd.player_skill_level;
	player.getComponent<hero>().skill_gap = gd.player_skillgap;
	player.getComponent<hero>().skill_timer = gd.player_skilltimer;

	for (int i = 0; i < gd.emynum; i++) {
		auto emy = std::make_shared<entity>(2, cam, *this);
		emy->trans.position = vector2D(gd.emypos_x[i], gd.emypos_y[i]);
		auto npc_role = std::make_shared<npc>(gd.emykid[i]);
		npc_role->awake(*canvas, *time);
		npc_role->player = &player;
		npc_role->blood = gd.emyblood[i];
		emy->addComponent(npc_role);
		emy_list.add(emy);
	}
	for (int i = 0; i < gd.propnum; i++) {
		auto p = std::make_shared<entity>(5, cam, *this);
		p->trans.position = vector2D(gd.proppos_x[i], gd.proppos_y[i]);
		auto p_prop = std::make_shared<prop>(gd.propkid[i]);
		p_prop->awake(*canvas, *time);
		p_prop->player = &player;
		p->addComponent(p_prop);
		props.add(p);
	}
	for (int i = 0; i < gd.emy_bullet_num; i++) {
		int hurt = gd.eb_hurt[i];
		vector2D dir = vector2D(gd.eb_dir_x[i], gd.eb_dir_y[i]);
		auto np = std::make_shared<entity>(4, cam, *this);
		auto npc_p = std::make_shared<npc_projectile>(hurt, vector2D(zero), dir, player);
		npc_p->awake(*canvas, *time);
		npc_p->timer= gd.eb_timer[i];
		np->addComponent(npc_p);
		np->trans.position = vector2D(gd.eb_pos_x[i], gd.eb_pos_y[i]);
		npc_projectiles.add(np);
	}
	for (int i = 0; i < gd.player_bullet_num; i++) {
		int kid = gd.pb_kid[i];
		int hurt = gd.pb_hurt[i];
		vector2D dir = vector2D(gd.pb_dir_x[i], gd.pb_dir_y[i]);
		auto pp = std::make_shared<entity>(3, cam, *this);
		auto player_p = std::make_shared<hero_projectile>(hurt, vector2D(zero), dir,kid);
		player_p->awake(*canvas, *time);
		player_p->timer = gd.pb_timer[i];
		pp->addComponent(player_p);
		pp->trans.position = vector2D(gd.pb_pos_x[i], gd.pb_pos_y[i]);
		player_projectiles.add(pp);
	}
}
void gameSystem::game_finitemap() {
	float dt = time->deltaTime;
	totaltime += dt;
	if (totaltime > 180) {
		totaltime = 0;
		sceneid = 4;
	}
	if (player.getComponent<hero>().blood <= 0) {
		sceneid = 5;
	}
	if (static_cast<int>(totaltime) > second) {
		second = static_cast<int>(totaltime);
		score++;
		std::cout << "Survive time: " << second << std::endl;
		std::cout << "score: " << score << std::endl;
		std::cout << "Player Level: " << player.getComponent<hero>().skill_level-2 << std::endl;
		std::cout << "fps: " << static_cast<int>(1.f / dt) << std::endl;
		std::cout << std::endl;
	}
	timer += dt;
	timer_prop += dt;
	canvas->clear();
	for (int y = 0; y < canvas->getHeight(); y++) {
		for (int x = 0; x < canvas->getWidth(); x++) {
			canvas->draw(x, y, 0, 0, 0);
		}
	}
	if (timer_prop > 4.5f) {
		timer_prop = 0;
		if (randomRes(0.6f)) {
			auto p = std::make_shared<entity>(5, cam, *this);
			p->trans.position = player.trans.position + randomVec2d() * randomRange(120, 500);
			auto p_prop = std::make_shared<prop>(0);
			p_prop->awake(*canvas, *time);
			p_prop->player = &player;
			p->addComponent(p_prop);
			props.add(p);
		}
		else
		{
			auto p = std::make_shared<entity>(5, cam, *this);
			p->trans.position = player.trans.position + randomVec2d() * randomRange(120, 500);
			auto p_prop = std::make_shared<prop>(1);
			p_prop->awake(*canvas, *time);
			p_prop->player = &player;
			p->addComponent(p_prop);
			props.add(p);
		}
	}
	if (timer > createThreshold) {
		timer = 0;
		createThreshold = max(0.5f, createThreshold - 0.2f);
		auto emy = std::make_shared<entity>(2, cam, *this);
		emy->trans.position = player.trans.position + randomVec2d() * randomRange(600, 1000);
		if (emy->trans.position.x > 1180) {
			emy->trans.position.x = 1180;
		}
		if (emy->trans.position.x < -1180) {
			emy->trans.position.x = -1180;
		}
		if (emy->trans.position.y > 1480) {
			emy->trans.position.y = 1480;
		}
		if (emy->trans.position.y < -1480) {
			emy->trans.position.y = -1480;
		}
		auto npc_role = std::make_shared<npc>(randomRangeint(0, 4));
		npc_role->awake(*canvas, *time);
		npc_role->player = &player;
		emy->addComponent(npc_role);
		emy_list.add(emy);
	}
	if (emy_list.length > 50) {
		emy_list.removeAt(0);
	}
	//std::cout << emy_list.length << std::endl;
	player.update();
	if (player.trans.position.x > 1180) {
		player.trans.position.x = 1180;
	}
	if (player.trans.position.x < -1180) {
		player.trans.position.x = -1180;
	}
	if (player.trans.position.y > 1480) {
		player.trans.position.y = 1480;
	}
	if (player.trans.position.y < -1480) {
		player.trans.position.y = -1480;
	}
	for (int i = 0; i < emy_list.length; i++) {
		emy_list[i]->update();
	}
	for (int i = 0; i < player_projectiles.length; i++) {
		player_projectiles[i]->update();
	}
	for (int i = 0; i < npc_projectiles.length; i++) {
		npc_projectiles[i]->update();
	}
	for (int i = 0; i < props.length; i++) {
		props[i]->update();
	}
	cam.trans.position = player.trans.position;
	if (cam.trans.position.x > 800) {
		cam.trans.position.x = 800;
	}
	if (cam.trans.position.x < -800) {
		cam.trans.position.x = -800;
	}
	if (cam.trans.position.y > 1280) {
		cam.trans.position.y = 1280;
	}
	if (cam.trans.position.y < -1280) {
		cam.trans.position.y = -1280;
	}
	cam.update();
	tmap_finite->draw(*canvas, cam.trans.position.x, cam.trans.position.y);
	for (int i = 0; i < emy_list.length; i++) {
		emy_list[i]->lateupdate();
	}
	for (int i = 0; i < player_projectiles.length; i++) {
		player_projectiles[i]->lateupdate();
	}
	for (int i = 0; i < npc_projectiles.length; i++) {
		npc_projectiles[i]->lateupdate();
	}
	for (int i = 0; i < props.length; i++) {
		props[i]->lateupdate();
	}
	int edge_left = cam.worldPosToScreenPos(vector2D(-1200, 1500)).x;
	int edge_right = cam.worldPosToScreenPos(vector2D(1200, -1500)).x;
	int edge_up = cam.worldPosToScreenPos(vector2D(1200, -1500)).y;
	int edge_down = cam.worldPosToScreenPos(vector2D(-1200, 1500)).y;
	for (int y = 0; y < canvas->getHeight(); y++) {
		for (int x = 0; x < canvas->getWidth(); x++) {
			if (x < edge_left) {
				canvas->draw(x, y, 0, 0, 0);
			}
			else if (x > edge_right)
			{
				canvas->draw(x, y, 0, 0, 0);
			}
			else if (y < edge_down)
			{
				canvas->draw(x, y, 0, 0, 0);
			}
			else if (y > edge_up)
			{
				canvas->draw(x, y, 0, 0, 0);
			}
		}
	}
	player.lateupdate();
	canvas->present();
	record();
}
void gameSystem::game_infinitemap() {
	float dt = time->deltaTime;
	totaltime += dt;
	if (totaltime > 180) {
		totaltime = 0;
		sceneid = 4;
	}
	if (player.getComponent<hero>().blood <= 0) {
		sceneid = 5;
	}
	if (static_cast<int>(totaltime) > second) {
		second = static_cast<int>(totaltime);
		score++;
		std::cout << "Survive time: " << second << std::endl;
		std::cout << "score: " << score << std::endl;
		std::cout << "Player Level: " << player.getComponent<hero>().skill_level-2 << std::endl;
		std::cout << "fps: " << static_cast<int>(1.f / dt) << std::endl;
		std::cout << std::endl;
	}
	timer += dt;
	timer_prop += dt;
	canvas->clear();
	for (int y = 0; y < canvas->getHeight(); y++) {
		for (int x = 0; x < canvas->getWidth(); x++) {
			canvas->draw(x, y, 0, 0, 0);
		}
	}
	if (timer_prop > 4.5f) {
		timer_prop = 0;
		if (randomRes(0.6f)) {
			auto p = std::make_shared<entity>(5, cam, *this);
			p->trans.position = player.trans.position + randomVec2d() * randomRange(120, 500);
			auto p_prop = std::make_shared<prop>(0);
			p_prop->awake(*canvas, *time);
			p_prop->player = &player;
			p->addComponent(p_prop);
			props.add(p);
		}
		else
		{
			auto p = std::make_shared<entity>(5, cam, *this);
			p->trans.position = player.trans.position + randomVec2d() * randomRange(120, 500);
			auto p_prop = std::make_shared<prop>(1);
			p_prop->awake(*canvas, *time);
			p_prop->player = &player;
			p->addComponent(p_prop);
			props.add(p);
		}
	}
	if (timer > createThreshold) {
		timer = 0;
		createThreshold = max(0.5f, createThreshold - 0.2f);
		auto emy = std::make_shared<entity>(2, cam, *this);
		emy->trans.position = player.trans.position + randomVec2d() * randomRange(600, 1000);
		auto npc_role = std::make_shared<npc>(randomRangeint(0, 4));
		npc_role->awake(*canvas, *time);
		npc_role->player = &player;
		emy->addComponent(npc_role);
		emy_list.add(emy);
	}
	if (emy_list.length > 50) {
		emy_list.removeAt(0);
	}
	//std::cout << emy_list.length << std::endl;
	player.update();
	for (int i = 0; i < emy_list.length; i++) {
		emy_list[i]->update();
	}
	for (int i = 0; i < player_projectiles.length; i++) {
		player_projectiles[i]->update();
	}
	for (int i = 0; i < npc_projectiles.length; i++) {
		npc_projectiles[i]->update();
	}
	for (int i = 0; i < props.length; i++) {
		props[i]->update();
	}
	cam.trans.position = player.trans.position;
	cam.update();
	tmap_infinite->draw(*canvas, cam.trans.position.x, cam.trans.position.y);
	for (int i = 0; i < emy_list.length; i++) {
		emy_list[i]->lateupdate();
	}
	for (int i = 0; i < player_projectiles.length; i++) {
		player_projectiles[i]->lateupdate();
	}
	for (int i = 0; i < npc_projectiles.length; i++) {
		npc_projectiles[i]->lateupdate();
	}
	for (int i = 0; i < props.length; i++) {
		props[i]->lateupdate();
	}
	player.lateupdate();
	canvas->present();
	record();
}
void gameSystem::keycontrol() {
	for (int i = 0; i < 256; i++) {
		if (canvas->keyPressed(i)) {
			previousKeyButton[i]++;
		}
		else
		{
			previousKeyButton[i] = 0;
		}
	}
}