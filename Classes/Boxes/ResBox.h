#ifndef _RES_BOX_H_
#define _RES_BOX_H_
#include "cocos2d.h"
#include "../Tools/MyColor.h"
#include <vector>
#include <unordered_map>
#include <cmath>
constexpr int RESBOX_MAX_SIZE=15;
constexpr int RESBOX_MAX_LEVEL=15;

USING_NS_CC;

using pii = std::pair<int, int>;
class ResBox {
public:
	static ResBox* player;
	static ResBox* big;
	static ResBox* inf;
	static ResBox* eps;
	static ResBox* blank;
	std::vector<pii> target_people;
	std::vector<pii> target_box;
	int type;//1有内部结构,2无内部结构,3player,4墙
	ResBox* son[RESBOX_MAX_SIZE][RESBOX_MAX_SIZE];
	ResBox* father;//真父亲指针
	pii pos;//在真父亲内部所在的位置
	pii size;//盒子大小,初始化
	Color3B color;
	ResBox(int type, pii size);
	void init();
	void setTarget(pii p, int type) {//1:people,2:box
		if (type == 2) {
			target_people.push_back(p);

		}
		else
			target_box.push_back(p);
	}
	void addBox(ResBox* sonBox, pii posi,bool is_true) {
		son[posi.first][posi.second] = sonBox;
		if (is_true) {
			sonBox->father = this;
			sonBox->pos = posi;
		}
	}
	//belong 1:进-1出0正常
	bool processObjects(ResBox* startObject, ResBox* lastFather, ResBox* startFather, pii dir, pii pos, int belong, ResBox* first, pii pos_1, pii pos_2, ResBox* llFather, int inf);
};
#endif