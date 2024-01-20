#include "ResBox.h"

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
	type(type), size(size),color(MyColor::RandomDark())
{
	init();
}
//belong 1:进-1出0正常
bool ResBox::processObjects(ResBox* startObject, ResBox* lastFather, pii dir, pii pos, int belong, ResBox* first) {
	int valid = 1;
	std::stack<ResBox*> mybox;
	std::stack<int> posx;
	std::stack<int> posy;
	mybox.push(startObject);

	ResBox* next = startObject;
	int next_x, next_y;
	int org_x, org_y;
	if (belong == 0) {
		next_x = pos.first + dir.first;
		next_y = pos.second + dir.second;
	}
	else if(belong == 1){
		if (pos.first != 0) {
			next_y = size.second - size.second / 2 - 1;
			next_x = dir.first > 0 ? 0 : size.first - 1;
		}
		else {
			next_x = size.first - size.first / 2 - 1;
			next_y = dir.second > 0 ? 0 : size.second - 1;
		}
		org_x = next_x;
		org_y = next_y;
	}
	else if (belong == -1) {
		next_x = startObject->father->pos.first+dir.first;
		next_y = startObject->father->pos.second+dir.second;

	}
	posx.push(next_x);
	posy.push(next_y);
	while (true)
	{
		if (!(next_x >= 0 && next_x < size.first && next_y >= 0 && next_y < size.second)) {
			if (!this->father) {
				valid = 0;//todo:出边界
				break;
			}
			else{
				ResBox* fathers = this->father;
				if (fathers->processObjects(mybox.top(),this, dir, this->pos, -1, first)) {
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
				if (nd->processObjects(mybox.top(), this,dir, { posx.top(),posy.top() }, 1, first)) {
					son[posx.top() - dir.first][posy.top() - dir.second] = nullptr;
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

			if (mybox.size() == 1 && belong!=0) {
				son[posx.top()][posy.top()] = nd;
				nd->pos = { posx.top(),posy.top() };
				if (nd->father==lastFather) {
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