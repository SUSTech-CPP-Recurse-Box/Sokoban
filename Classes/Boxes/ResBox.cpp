#include "ResBox.h"
void ResBox::init() {
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			son[i][j] = nullptr;
		}
	}
	trueFather = nullptr;
}
ResBox::ResBox(int type, pii size) :
	type(type), size(size)
{
	init();
}