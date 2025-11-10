#include "Entity.h"
#include "GameManager.h"
void entity::update() {
	for (unsigned int i = 0; i < components.length; ++i) {
		components[i]->update();
	}
}
void entity::lateupdate() {
	for (unsigned int i = 0; i < components.length; ++i) {
		components[i]->lateupdate();
	}
}
