#ifndef _MY_COLOR_H_
#define _MY_COLOR_H_
#include "cocos2d.h"
#include <cstdlib>
USING_NS_CC;
class MyColor {
private:
    static int lightColor[10][3];
    static int darkColor[10][3];

public:
    static cocos2d::Color3B RandomLight() {
        // 生成一个随机索引
        int randomIndex = rand() % 10;
        // 将颜色转换为 Color3B 类型并返回
        return cocos2d::Color3B(
            lightColor[randomIndex][0],
            lightColor[randomIndex][1],
            lightColor[randomIndex][2]);
    }
    static cocos2d::Color3B RandomDark() {
        // 生成一个随机索引
        int randomIndex = rand() % 10;
        // 将颜色转换为 Color3B 类型并返回
        return cocos2d::Color3B(
            darkColor[randomIndex][0],
            darkColor[randomIndex][1],
            darkColor[randomIndex][2]);
    }
};


#endif
