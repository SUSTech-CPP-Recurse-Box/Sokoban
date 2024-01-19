#include "Box.h"

Box* Box::player = nullptr;
Box::Box() :color(MyColor::RandomDark()), visible(true), true_body(true), size(100.0f), actual_box(this) {
	this->setColor(color);
	this->initWithFile("MainMenu/boxes/default_box.png");
	this->setContentSize(Size(size, size));
};
Box::Box(bool is_bondary) :color(MyColor::RandomDark()), visible(true), true_body(true), size(100.0f), actual_box(this) {
	this->setColor(color);
	this->is_bondary = is_bondary;
	if(is_bondary)
		this->initWithFile("MainMenu/boxes/boundary.png");
	else
		this->initWithFile("MainMenu/boxes/default_box.png");
	this->setContentSize(Size(size, size));
};
Box::Box(Color3B color, Box* actual_box, long posX,
	long posY, float size, BoxCollection* father, bool true_body, bool player,bool is_bondary) :
	color(color), actual_box(actual_box), true_body(true_body),
	posX(posX), posY(posY), size(size), father(father),is_bondary(is_bondary) {
	if (true_body && player) {
		Box::player = this;
	}
	
	if (true_body) {
		actual_box = this;
	}
	this->setColor(color);
	if (is_bondary)
		this->initWithFile("MainMenu/boxes/boundary.png");
	else
		this->initWithFile("MainMenu/boxes/default_box.png");
	this->setContentSize(Size(size, size));
};
//todo:change the false box of it lighter
Box* Box::copy(long posX, long posY, float size, BoxCollection* father,bool true_body,bool player) {
	Box* box = Box::create(color, actual_box, posX, posY, size, father, true_body, player,is_bondary);
	if (true_body)
		actual_box = box;
	return box;
};
bool Box::init() {
	return true;
}

void Box::update(long posX, long posY) {
	Point position = this->getPosition();
	this->setPosition(Point(position.x + posX * size, position.y + posY * size));
}

bool Box::set_to_player(Box* box) {
	if (player == NULL) {
		player = box;
		return true;
	}
	else
		if (player == this) {
			player = box;
			return true;
		}
	return false;
}