#include "cocos2d.h"
#include <cstdlib>

class MyColor {
private:
    static int lightColor[10][3];

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
};

// 在实现文件中进行静态成员变量的初始化
int MyColor::lightColor[10][3] = {
    {255, 250, 205}, // 柠檬雪纺
    {255, 245, 238}, // 贝壳
    {240, 255, 240}, // 蜜露
    {135, 206, 250}, // LightSkyBlue
    {127, 255, 212}, // 海蓝宝石
    {255, 228, 196}, // 浓汤1
    {187, 255, 255}, // 淡绿松石色1
    {255, 225, 255}, // 蓟1
    {255, 99, 71},   // 番茄1
    {255, 165, 0}    // 橙色
};
