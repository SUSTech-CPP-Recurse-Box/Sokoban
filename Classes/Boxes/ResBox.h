#ifndef _RES_BOX_H_
#define _RES_BOX_H_
#include "cocos2d.h"
#include <vector>
#define MAX_SIZE 10
#define MAX_LEVEL 10
USING_NS_CC;
using pii = std::pair<int, int>;
class ResBox {
public:
	int type;//1有内部结构,2无内部结构,3player,4墙
	ResBox* son[MAX_SIZE][MAX_SIZE];
	ResBox* father;//真父亲指针
	pii pos;//在真父亲内部所在的位置
	pii size;//盒子大小,初始化
	Color3B color;
	ResBox(int type, pii size);
	void init();
	void addBox(ResBox* sonBox, pii posi,bool is_true) {
		son[posi.first][posi.second] = sonBox;
		if (is_true) {
			sonBox->father = this;
			sonBox->pos = posi;
		}
	}
};
#endif