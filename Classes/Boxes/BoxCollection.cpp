#include "BoxCollection.h"
#include "Box.h"
bool BoxCollection::init()
{
    if (!Node::init()) {
        return false;
    }

    // ��ʼ������

    return true;
}

void BoxCollection::addBox(cocos2d::Sprite* object,int x,int y)
{
    // ��������ӵ�������
    boxes[x][y] = object;
    dynamic_cast<Box*>(object)->x = x;
    dynamic_cast<Box*>(object)->y = y;
    dynamic_cast<Box*>(object)->father=this;
    object->setContentSize(Size(boxSize, boxSize));
    object->setPosition(Vec2((2*x-this->x+1)*boxSize/2, (this->y-2*y-1) * boxSize/2));
    // ��������Ϊ��ǰ�ڵ���ӽڵ�
    this->addChild(object,1);
}

void BoxCollection::addBox(int x, int y) {
    boxes[x][y] = Box::create();
    this->addChild(boxes[x][y]);

}
void BoxCollection::processObjects(cocos2d::Sprite* startObject, int dirX, int dirY)//
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
