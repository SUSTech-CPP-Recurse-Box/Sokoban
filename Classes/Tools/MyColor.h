#ifndef _MY_COLOR_H_
#define _MY_COLOR_H_

#include "cocos2d.h"
#include <cstdlib>

#include <random>

USING_NS_CC;

class MyColor {
private:
    static int lightColor[10][3];
    static int darkColor[10][3];
    static int a;

public:
    static void setseed();
    
    static cocos2d::Color3B RandomLight();

    static cocos2d::Color3B RandomDark();
};


#endif
