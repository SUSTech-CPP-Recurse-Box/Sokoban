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
		if (type == 1) {
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
	bool processObjects(ResBox* startObject, pii dir, pii pos, int belong) {
		int valid = 1;
		std::stack<ResBox*> mybox;
		std::stack<int> posx;
		std::stack<int> posy;
		mybox.push(startObject);
		
		ResBox* next = startObject;
		int next_x, next_y;
		int org_x, org_y;
		if (belong==0) {
			next_x = pos.first + dir.first;
			next_y = pos.second + dir.second;
			posx.push(next_x);
			posy.push(next_y);
		}
		else {
			if (pos.first != 0) {
				next_y = size.second - size.second / 2 - 1;
				next_x = pos.first > 0 ? 0 : size.first - 1;
			}
			else {
				next_x = size.first - size.first / 2 - 1;
				next_y = pos.second > 0 ? 0 : size.second - 1;
			}
			org_x = next_x;
			org_y = next_y;
		}
		while (true)
		{
			if (!(next_x >= 0 && next_x < size.first && next_y >= 0 && next_y < size.second)) {
				valid = 0;//todo:出边界
				break;
			}
			if (!son[next_x][next_y]) {//空
				break;
			}
			if (son[next_x][next_y]->type==4) {
				valid == 0;
				break;
			}
		mybox.push(son[next_x][next_y]);
		
		next = son[next_x][next_y];
		next_x += dir.first;
		next_y += dir.second;
		posx.push(next_x);
		posy.push(next_y);
		}

		if (valid) {
			while (!mybox.empty()) {
				long next_x,next_y;
				ResBox* nd = mybox.top();
				
				if (mybox.empty()) {
					//todo:
				}
				else {
					if (this == nd->father) {
						nd->pos = { posx.top(),posy.top() };
						son[posx.top()][posy.top()] = nd;
						son[posx.top() - dir.first][posy.top() - dir.second]=nullptr;
					}
				}
				mybox.pop();
				posx.pop();
				posy.pop();
			}
		}
		return true;
	}
};
#endif