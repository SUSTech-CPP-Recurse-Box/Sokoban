#include "MyColor.h"

// 在实现文件中进行静态成员变量的初始化
int MyColor::a = 0;

int MyColor::lightColor[10][3] = {
    {255, 250, 205}, // 柠檬雪纺
    {255, 245, 238}, // 贝壳
    {240, 255, 240}, // 蜜露
    {135, 206, 250}, // LightSkyBlue
    {255, 99, 71}, // 海蓝宝石
    {255, 228, 196}, // 浓汤1
    {187, 255, 255}, // 淡绿松石色1
    {255, 225, 255}, // 蓟1
    {127, 255, 212} ,   // 番茄1
    {255, 165, 0}    // 橙色
};

int MyColor::darkColor[10][3] = {
    {204, 204, 153}, // 柠檬雪纺
    {204, 194, 187}, // 贝壳
    {192, 204, 192}, // 蜜露
    { 90, 146, 179}, // LightSkyBlue
    { 84, 170, 141}, // 海蓝宝石
    {204, 183, 161}, // 浓汤1
    {140, 204, 204}, // 淡绿松石色1
    {204, 180, 204}, // 蓟1
    {204,  79,  56}, // 番茄1
    {204, 136,   0}  // 橙色
};

void MyColor::setseed()
{
    a = 0;
}

cocos2d::Color3B MyColor::RandomLight()
{
    // 生成一个随机索引
    int randomIndex = a++ % 10;
    // 将颜色转换为 Color3B 类型并返回
    return cocos2d::Color3B(
        lightColor[randomIndex][0],
        lightColor[randomIndex][1],
        lightColor[randomIndex][2]);
}

cocos2d::Color3B MyColor::RandomDark()
{
    // 生成一个随机索引
    int randomIndex = a++ % 10;
    // 将颜色转换为 Color3B 类型并返回
    return cocos2d::Color3B(
        darkColor[randomIndex][0],
        darkColor[randomIndex][1],
        darkColor[randomIndex][2]);
}
