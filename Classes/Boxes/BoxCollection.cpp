#include "BoxCollection.h"
#include "Box.h"
bool BoxCollection::init()
{
    if (!Node::init()) {
        return false;
    }

    // 初始化集合

    return true;
}
//todo: 实现多层渲染（理论上把下一层BoxCollection直接addChild即可）
//todo: 实现箱子的大小调整
//todo: (尝试)实现对整个地图的放大和缩小
void BoxCollection::addBox(cocos2d::Sprite* object,int x,int y)
{
    // 将物体添加到集合中
    boxes[x][y] = object;
    dynamic_cast<Box*>(object)->x = x;
    dynamic_cast<Box*>(object)->y = y;
    dynamic_cast<Box*>(object)->father=this;
    object->setContentSize(Size(boxSize, boxSize));
    object->setPosition(Vec2((2*x-this->x+1)*boxSize/2, (this->y-2*y-1) * boxSize/2));
    // 将物体作为当前节点的子节点
    this->addChild(object,1);
}

void BoxCollection::addBox(int x, int y) {
    boxes[x][y] = Box::create();
    this->addChild(boxes[x][y]);

}
//todo: 在这里加逻辑判断是否可动，物体现在传入的是Sprite，需要改成node（Box继承自Sprite继承自node）
//todo: 现在这里没有任何规则
//todo: 需要写一个更优雅的移动作为一个函数
//todo: 需要把箱子位置计算提出一个函数
//todo: 这里的移动是通过playframe中的player移动传入player所在的BoxCollection（defaultBox）然后调用这个函数进行的
void BoxCollection::processObjects(cocos2d::Sprite* startObject, int dirX, int dirY)
{
    Box* box = dynamic_cast<Box*>(startObject);
    boxes[box->x][box->y] = nullptr;
    boxes[box->x + dirX][y + dirY] = box;
    box->runAction(MoveBy::create(0.2, Vec2(dirX * boxSize, dirY * boxSize)));
}
void BoxCollection::addPanel() {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            auto mySprite = Sprite::create("MainMenu/boxes/panel.png");
            mySprite->setContentSize(Size(boxSize, boxSize));
            mySprite->setPosition(Vec2((2 * i - this->x + 1) * boxSize / 2, (this->y - 2 * j - 1) * boxSize / 2));
            this->addChild(mySprite);
        }
    }
}
