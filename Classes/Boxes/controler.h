#ifndef _CONTROLER_H_
#define _CONTROLER_H_
#include "cocos2d.h"
USING_NS_CC;

class controler {
public:
	static controler* _instance;
	controler* get() {
		return _instance;
	}

};
#endif