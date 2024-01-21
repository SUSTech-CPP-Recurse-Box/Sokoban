#include "DesignControler.h"

DesignControler* DesignControler::_instance = new DesignControler();

DesignControler* DesignControler::get() {
    return _instance;
}
void DesignControler::init(DesignLayer* dl) {
    disp.clear();
    this->dl = dl;
    addDefault();
    display();
}
void DesignControler::addDefault() {
    Sprite* add = Sprite::create("MainMenu/boxes/add.png");
    Sprite* player = Sprite::create("MainMenu/boxes/player.png");
    Sprite* box = Sprite::create("MainMenu/boxes/default_box.png");
    Sprite* wall = Sprite::create("MainMenu/boxes/boundary.png");
    player->setName("-3");
    add->setName("-1");
    box->setName("-2");
    wall->setName("-4");
    disp.push_back(add);
    disp.push_back(player);
    disp.push_back(box);
    disp.push_back(wall);
    dl->addChild(player);
    dl->addChild(add);
    dl->addChild(box);
    dl->addChild(wall);

}
void DesignControler::display() {
    for (int i = 0; i < disp.size();i++) {
        Sprite* s = disp[i];
        s->setContentSize(Size(DEFAULT_SIZE*3, DEFAULT_SIZE*3));
        s->runAction(MoveTo::create(0, Vec2(DEFAULT_SIZE*5, DEFAULT_SIZE* 4*(2+i))));
    }
}
DesignControler::DesignControler() {
};

DesignControler::~DesignControler() {
};