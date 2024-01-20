#include "ResBox.h"
#include <cmath>
ResBox* ResBox::player = nullptr;
ResBox* ResBox::big = nullptr;

void ResBox::init() {
	for (int i = 0; i < RESBOX_MAX_SIZE; i++) {
		for (int j = 0; j < RESBOX_MAX_SIZE; j++) {
			son[i][j] = nullptr;
		}
	}
	father = nullptr;
}
ResBox::ResBox(int type, pii size) :
	type(type), size(size), color(MyColor::RandomDark())
{
	init();
}
//belong 1:进-1出0正常2上一个是出来，之后直接进入                                                                                            上一个  上两个
bool ResBox::processObjects(ResBox* startObject, ResBox* lastFather, ResBox* startFather, pii dir, pii pos, int belong, ResBox* first,pii pos_1, pii pos_2, ResBox* llFather) {
	int valid = 1;
	
	std::stack<ResBox*> mybox;
	std::stack<int> posx;
	std::stack<int> posy;
	mybox.push(startObject);

	ResBox* next = startObject;
	int next_x, next_y;
	if (belong == 0) {
		next_x = pos.first + dir.first;
		next_y = pos.second + dir.second;

	}
	else if (belong == 1) {
		if (dir.first != 0) {
			next_y = size.second - size.second / 2 - 1;
			next_x = dir.first > 0 ? 0 : size.first - 1;
		}
		else {
			next_x = size.first - size.first / 2 - 1;
			next_y = dir.second > 0 ? 0 : size.second - 1;
		}
	}
	else if (belong == 2) {//上一个是出来，之后直接进入
		if (dir.first != 0) {
			next_y = std::round((double)pos_2.second* size.second/llFather->size.second);
			next_x = dir.first > 0 ? 0 : size.first - 1;
		}
		else {
			next_x = std::round((double)pos_2.first * size.first / llFather->size.first);
			next_y = dir.second > 0 ? 0 : size.second - 1;
		}
	}
	else if (belong == -1) {
		next_x = lastFather->pos.first + dir.first;
		next_y = lastFather->pos.second + dir.second;

	}
	posx.push(next_x);
	posy.push(next_y);
	while (true)
	{
		if (!(next_x >= 0 && next_x < size.first && next_y >= 0 && next_y < size.second)) {
			if (!this->father) {
				valid = 0;
				break;
			}
			else {
				ResBox* fathers = this->father;
				//=========================  我自己，这一个父亲，第一个父亲，
				if (fathers->processObjects(mybox.top(), this, (mybox.size() == 1 && belong != 0) ? startFather : this,
					// 方向，父亲的位置，         出边界，原始箱子,我的位置
					dir, { posx.top(),posy.top() }, -1, first, { posx.top() - dir.first,posy.top() - dir.second },pos_1, lastFather)) {
					son[posx.top() - dir.first][posy.top() - dir.second] = nullptr;
					mybox.pop();
					posx.pop();
					posy.pop();
					valid = 1;
					break;
				}
			}

		}
		if (!son[next_x][next_y]) {//空
			break;
		}
		if (son[next_x][next_y]->type == 4) {
			valid = 0;
			break;
		}
		mybox.push(son[next_x][next_y]);

		next = son[next_x][next_y];
		next_x += dir.first;
		next_y += dir.second;
		posx.push(next_x);
		posy.push(next_y);
	}
	if (valid == 0) {
		while (!mybox.empty())
		{
			ResBox* nd = mybox.top();
			mybox.pop();
			posx.pop();
			posy.pop();
			if (nd->type == 1) {
				//=====================  我自己，我的父亲，      最开始的父亲，      
				if (nd->processObjects(mybox.top(), this, (mybox.size() == 1 && belong != 0) ? startFather : this,
					//方向，我的位置，            进边界，原始箱子
					dir, { posx.top(),posy.top() }, belong==-1?2:1, first, { posx.top() - dir.first,posy.top() - dir.second },pos_1, lastFather)) {
					if (!(belong != 0 && mybox.size() == 1)) {
						son[posx.top() - dir.first][posy.top() - dir.second] = nullptr;
					}
					mybox.pop();
					posx.pop();
					posy.pop();
					valid = 1;
					break;
				}
			}
		}
	}
	if (valid == 1) {
		while (!mybox.empty()) {
			long next_x, next_y;
			ResBox* nd = mybox.top();

			if (mybox.size() == 1 && belong != 0) {
				son[posx.top()][posy.top()] = nd;
				nd->pos = { posx.top(),posy.top() };
				if (nd->father == startFather) {
					nd->father = this;
				}
			}
			else {
				if (this == nd->father) {
					nd->pos = { posx.top(),posy.top() };
					son[posx.top()][posy.top()] = nd;
					son[posx.top() - dir.first][posy.top() - dir.second] = nullptr;
				}
			}
			mybox.pop();
			posx.pop();
			posy.pop();
		}
		return true;
	}
	return false;
}