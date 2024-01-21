#include "DesignControler.h"

DesignControler* DesignControler::_instance = new DesignControler();

DesignControler* DesignControler::get() {
	return _instance;
}
void DesignControler::init(DesignLayer* dl) {
	size_x = 3;
	size_y = 3;
	boxcnt = 0;
	disp.clear();
	chosen = nullptr;
	this->dl = dl;
	addDefault();
	display();
}
void DesignControler::addDefault() {
	Sprite* add = Sprite::create("MainMenu/boxes/add.png");
	Sprite* player = Sprite::create("MainMenu/boxes/player.png");
	Sprite* box = Sprite::create("MainMenu/boxes/default_box.png");
	Sprite* wall = Sprite::create("MainMenu/boxes/boundary.png");
	Sprite* player_t = Sprite::create("MainMenu/boxes/traget_player.png");
	Sprite* box_t = Sprite::create("MainMenu/boxes/target_box.png");
	Sprite* ground = Sprite::create("MainMenu/boxes/panel.png");
	add->setName("-1");
	box->setName("O ");
	player->setName("P ");
	wall->setName("# ");
	player_t->setName("= ");
	box_t->setName("- ");
	ground->setName(". ");
	disp.push_back(add);
	disp.push_back(player);
	disp.push_back(box);
	disp.push_back(wall);
	disp.push_back(player_t);
	disp.push_back(box_t);
	disp.push_back(ground);
	dl->addChild(player);
	dl->addChild(add);
	dl->addChild(box);
	dl->addChild(wall);
	dl->addChild(player_t);
	dl->addChild(box_t);
	dl->addChild(ground);
}
void DesignControler::setChosen(Sprite* s) {
	if (chosen != nullptr) {
		chosen->removeFromParent();
		chosen = nullptr;
	}
	if (s->getName() == "-1") {
		log("-1");
		Sprite* s = Sprite::create("MainMenu/boxes/box_i.png");
		data.push_back(new dataset(boxcnt, size_x, size_y));
		auto label = Label::createWithTTF(std::to_string(boxcnt), "fonts/arial.ttf", 40);
		label->setPosition(Vec2(30, 30));
		label->setColor(Color3B(50, 50, 50));
		s->addChild(label);
		std::string sss = " " + std::to_string(boxcnt);
		s->setName(" " + std::to_string(boxcnt));
		boxcnt++;
		disp.push_back(s);
		dl->addChild(s);
		display();
		drawBox(data[0]);
		return;
	}

	if (s->getName() == "O ") {
		log("O ");
		chosen = Sprite::create("MainMenu/boxes/default_box.png");
		chosen->setName("O ");
	}
	else if (s->getName() == "P ") {
		log("P ");
		chosen = Sprite::create("MainMenu/boxes/player.png");
		chosen->setName("P ");
	}
	else if (s->getName() == "# ") {
		log("# ");
		chosen = Sprite::create("MainMenu/boxes/boundary.png");
		chosen->setName("# ");
	}
	else if (s->getName() == "= ") {
		log("= ");
		chosen = Sprite::create("MainMenu/boxes/traget_player.png");
		chosen->setName("= ");
	}
	else if (s->getName() == "- ") {
		log("- ");
		chosen = Sprite::create("MainMenu/boxes/target_box.png");
		chosen->setName("- ");
	}
	else if (s->getName() == ". ") {
		log(". ");
		chosen = Sprite::create("MainMenu/boxes/panel.png");
		chosen->setName(". ");
	}
	else {
		chosen = Sprite::create("MainMenu/boxes/box_i.png");
		chosen->setName(s->getName());
		std::string ss = "";
		auto label = Label::createWithTTF(ss + s->getName()[1], "fonts/arial.ttf", 40);
		label->setPosition(Vec2(30, 30));
		label->setColor(Color3B(50, 50, 50));
		chosen->addChild(label);
	}

	chosen->setContentSize(Size(DEFAULT_SIZE * 3, DEFAULT_SIZE * 3));
	dl->addChild(chosen);
}
void DesignControler::display() {
	for (int i = 0; i < disp.size(); i++) {
		Sprite* s = disp[i];
		s->setContentSize(Size(DEFAULT_SIZE * 3, DEFAULT_SIZE * 3));
		if (i < 7) {
			s->runAction(MoveTo::create(0, Vec2(DEFAULT_SIZE * 5, DEFAULT_SIZE * 4 * (2 + i))));
		}
		else {
			s->runAction(MoveTo::create(0, Vec2(DEFAULT_SIZE * 10, DEFAULT_SIZE * 4 * (2 + i-7))));

		}
	}
}
void DesignControler::drawBox(dataset* dc) {
	this_box = dc->cnt;
	if (board.size() != 0) {
		for (int i = 0; i < board.size(); i++) {
			board[i]->removeFromParent();
		}
		board.clear();
	}
	Size winSize = Director::getInstance()->getWinSize();
	double start_x = winSize.width / 2 - 3 * DEFAULT_SIZE / 2 * dc->x;
	double start_y = winSize.height / 2 - 3 * DEFAULT_SIZE / 2 * dc->y;
	for (int i = 0; i < dc->x; i++) {
		for (int j = 0; j < dc->y; j++) {
			Sprite* s;
			if (dc->data1[i][j] == '.') {
				s = Sprite::create("MainMenu/boxes/panel.png");
			}
			else if (dc->data1[i][j] == '=') {
				s = Sprite::create("MainMenu/boxes/traget_player.png");
			}
			else if (dc->data1[i][j] == 'P') {
				s = Sprite::create("MainMenu/boxes/player.png");
			}
			else if (dc->data1[i][j] == 'O') {
				s = Sprite::create("MainMenu/boxes/default_box.png");
			}
			else if (dc->data1[i][j] == '#') {
				s = Sprite::create("MainMenu/boxes/boundary.png");
			}
			else if (dc->data1[i][j] == '-') {
				s = Sprite::create("MainMenu/boxes/target_box.png");
			}
			else {
				s = Sprite::create("MainMenu/boxes/box_i.png");
				std::string ss = "";
				auto label = Label::createWithTTF(ss + dc->data2[i][j], "fonts/arial.ttf", 40);
				label->setPosition(Vec2(30, 30));
				label->setColor(Color3B(50, 50, 50));
				s->addChild(label);
			}
			s->setName(std::to_string(i) + "," + std::to_string(j));
			s->setPosition(Vec2(start_x + i * 3 * DEFAULT_SIZE, start_y + j * 3 * DEFAULT_SIZE));
			s->setContentSize(Size(3 * DEFAULT_SIZE, 3 * DEFAULT_SIZE));
			dl->addChild(s);
			board.push_back(s);

		}
	}
}
void DesignControler::displayBox(Sprite* box) {
	if (box->getName()[1] != ' ') {
		drawBox(data[box->getName()[1] - '0']);
	}
}
void DesignControler::putBox(Sprite* box) {
	if (!chosen) {
		return;
	}
	data[this_box]->data1[box->getName()[0] - '0'][box->getName()[2] - '0'] = chosen->getName()[0];
	data[this_box]->data2[box->getName()[0] - '0'][box->getName()[2] - '0'] = chosen->getName()[1];
	chosen->removeFromParent();
	chosen = nullptr;
	drawBox(data[this_box]);
}
DesignControler::DesignControler() {
	chosen = nullptr;
	dl = nullptr;
};

DesignControler::~DesignControler() {
};