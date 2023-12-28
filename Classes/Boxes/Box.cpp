#include "Box.h"
Box* Box::player = nullptr;
Box::Box() :color(Color3B::GREEN), visible(true), true_body(true),size(100.0f) {
	this->initWithFile("MainMenu/boxes/default_box.png");
	this->setContentSize(Size(size, size));
};
bool Box::init() {
	return true;
}

void Box::update(int x, int y) {
	Point position = this->getPosition();
	this->setPosition(Point(position.x +x*size, position.y +y*size));
}

bool Box::set_to_player(Box* box) {
	if (player == NULL) {
		player = box;
		return true;
	}else
	if (player == this) {
		player = box;
		return true;
	}
	return false;
}