#ifndef _CONTROLER_H_
#define _CONTROLER_H_
#include "cocos2d.h"
#include "ResBox.h"
#include <vector>
#include "../GameFrame/GameScene.h"
USING_NS_CC;
using pii = std::pair<int, int>;
class controler {
public:
	ResBox* big;
	ResBox* player;
	std::vector<Sprite*> boxes;
	static controler* _instance;
	static controler* get() {
		return _instance;
	}
	controler() {
		big = nullptr;
		player = nullptr;
	};
	~controler() {};
	void init() {
		big = new ResBox(1, {4,4});
		player = new ResBox(3, { 0,0 });
		big->addBox(player, { 2,2 }, true);
	}
	void initPanel(Sprite* fa, double size,pii s,Color3B color) {
		for (int i = 0; i < s.first; i++) {
			for (int j = 0; j < s.second; j++) {
				Sprite* sp = Sprite::create("MainMenu/boxes/panel.png");
				sp->setColor(color);
				sp->setContentSize(Size(size, size));
				sp->setPosition(Vec2((2 * i - s.first + 1) * size / 2, (s.second - 2 * j - 1) * size / 2));
				fa->addChild(sp);
				boxes.push_back(sp);
			}
		}
	}
	void draw(GameScene* gs,double size) {
		Size winSize = Director::getInstance()->getWinSize();
		Sprite* s = Sprite::create();
		boxes.push_back(s);
		s->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		gs->addChild(s);
		s->setContentSize(Size(size, size));
		initPanel(s, size / big->size.first,big->size,big->color);
		for (int i = 0; i < big->size.first; i++) {
			for (int j = 0; j < big->size.second; j++) {
				if (big->son[i][j]) {//绘图需要：颜色：来自物体，大小：来自父亲，传入，位置：来自父亲
					double new_size = size / big->size.first;
					Vec2 v =Vec2((2 * i - big->size.first + 1) * new_size / 2, (big->size.second - 2 * j - 1) * new_size / 2);
					draw(new_size, big->son[i][j], s,v);
				}
			}
		}
	}
	void draw( double size, ResBox* draw, Sprite* father,Vec2 pos) {
		if (draw->type == 2&& draw->type == 3) {
			Sprite* s = Sprite::create("MainMenu/boxes/default_box.png");
			s->setPosition(Vec2(0,0));
			s->setContentSize(Size(1000, 1000));
			s->setColor(draw->color);
			father->addChild(s,100);
			boxes.push_back(s);
		}
	}
};
#endif