#include "BoxCollection.h"

bool BoxCollection::init()
{
    if (!Node::init()) {
        return false;
    }

    // 初始化集合

    return true;
}

void BoxCollection::addObject(cocos2d::Sprite* object)
{
    // 将物体添加到集合中
    objects.push_back(object);

    // 将物体作为当前节点的子节点
    this->addChild(object);
}

void BoxCollection::processObjects()
{
    // 处理集合中的所有物体
    for (auto object : objects)
    {
        // 在这里添加处理物体的逻辑
        // 例如，移动、旋转、缩放等
        object->setPosition(object->getPosition() + cocos2d::Vec2(10, 0));
    }
}
