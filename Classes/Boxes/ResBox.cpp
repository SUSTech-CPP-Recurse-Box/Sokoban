#include "ResBox.h"
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