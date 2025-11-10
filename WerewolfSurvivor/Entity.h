#pragma once
#include "Transform.h"
#include "Container.h"
#include "Behavior.h"
class camera;
class gameSystem;


class entity {
public:
	container<std::shared_ptr<behavior>> components;
public:
	int id;
	int active;
	transform trans;
	camera* cam;
	gameSystem* data;
public:
	entity() = default;
	entity(int eid, camera& c, gameSystem& gd) { id = eid; cam = &c; data = &gd; active = 0; }
	void addComponent(std::shared_ptr<behavior> c) {
		c.get()->setGameobject(this);
		components.add(c);
	}
	template <typename U>
	void removeComponent() {
		components.removeAll<U>();
	}
	template <typename U>
	U& getComponent() {
		return components.template get<U>();
	}
	void init(int eid, camera& c, gameSystem& gd) {
		id = eid;
		cam = &c;
		data = &gd;
		trans.init();
		components.clear();
	}
	//void destory(entity* e);
	void update();
	void lateupdate();
};