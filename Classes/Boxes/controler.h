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
		ResBox* b = new ResBox(1, { 2,2 });
		player = new ResBox(3, { 0,0 });
		big->addBox(player, { 2,3 }, true);
		big->addBox(b, { 0,0 }, true);
		big->addBox(big, { 1,0 }, false);
	}
	void initPanel(Sprite* fa, double size,pii s,Color3B color) {
		for (int i = 0; i < s.first; i++) {
			for (int j = 0; j < s.second; j++) {
				Sprite* sp = Sprite::create("MainMenu/boxes/panel.png");
				sp->setColor(color);
				sp->setContentSize(Size(size, size));
				sp->setPosition(Vec2((2 * i - s.first + 1) * size/2 , -(s.second - 2 * j - 1) * size/2 ));
				log("x:%lf;y:%lf", (2 * i - s.first + 1) * size , -(s.second - 2 * j - 1) * size );
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
		initPanel(s, size / big->size.first,big->size,big->color);
		for (int i = 0; i < big->size.first; i++) {
			for (int j = 0; j < big->size.second; j++) {
				if (big->son[i][j]) {//绘图需要：颜色：来自物体，大小：来自父亲，传入，位置：来自父亲
					double new_size = size / big->size.first;
					Vec2 v =Vec2((2 * (i )- big->size.first + 1) * new_size / 2, -(big->size.second - 2 * (j) - 1) * new_size / 2);
					draw(new_size, big->son[i][j], s,v);
				}
			}
		}
	}
	void draw( double size, ResBox* draw, Sprite* father,Vec2 pos) {
		if (draw->type == 2|| draw->type == 3|| draw->type == 4) {

			Sprite* s;
			if(draw->type == 4)
				s= Sprite::create("MainMenu/boxes/boundary.png");
			else
				s = Sprite::create("MainMenu/boxes/default_box.png");
			s->setPosition(pos);
			s->setContentSize(Size(size, size));
			s->setColor(draw->color);
			father->addChild(s);
			boxes.push_back(s);
		}
		else {
			Sprite* s = Sprite::create();
			s->setPosition(pos);
			father->addChild(s);
			boxes.push_back(s);
			initPanel(s, size / draw->size.first, draw->size, draw->color);
			if (size < 0.1) {
				return;
			}
			for (int i = 0; i < draw->size.first; i++) {
				for (int j = 0; j < draw->size.second; j++) {
					if (draw->son[i][j]) {//绘图需要：颜色：来自物体，大小：来自父亲，传入，位置：来自父亲
						double new_size = size / draw->size.first;
						Vec2 v = Vec2((2 * (i ) - draw->size.first + 1) * new_size / 2, -(draw->size.second - 2 * (j ) - 1) * new_size / 2);
						controler::draw(new_size, draw->son[i][j], s, v);
					}
				}
			}
		}
	}
};
#endif