#include "Box.h"
Box* Box::player = nullptr;
Box::Box() :color(Color3B::GREEN), visible(true), true_body(true),size(100.0f) {
	this->setColor(color);
	this->initWithFile("MainMenu/boxes/default_box.png");
	this->setContentSize(Size(size, size));
};
bool Box::init() {
	return true;
}

void Box::update(int posX, int posY) {
	Point position = this->getPosition();
	this->setPosition(Point(position.x +posX*size, position.y +posY*size));
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