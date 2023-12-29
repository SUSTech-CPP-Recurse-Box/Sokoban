#include "cocos2d.h"
#include <cstdlib>

class MyColor {
private:
    static int lightColor[10][3];

public:
    static cocos2d::Color3B RandomLight() {
        // ����һ���������
        int randomIndex = rand() % 10;
        // ����ɫת��Ϊ Color3B ���Ͳ�����
        return cocos2d::Color3B(
            lightColor[randomIndex][0],
            lightColor[randomIndex][1],
            lightColor[randomIndex][2]);
    }
};

// ��ʵ���ļ��н��о�̬��Ա�����ĳ�ʼ��
int MyColor::lightColor[10][3] = {
    {255, 250, 205}, // ����ѩ��
    {255, 245, 238}, // ����
    {240, 255, 240}, // ��¶
    {135, 206, 250}, // LightSkyBlue
    {127, 255, 212}, // ������ʯ
    {255, 228, 196}, // Ũ��1
    {187, 255, 255}, // ������ʯɫ1
    {255, 225, 255}, // ��1
    {255, 99, 71},   // ����1
    {255, 165, 0}    // ��ɫ
};
