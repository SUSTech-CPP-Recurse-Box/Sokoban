#include "BoxCollection.h"

bool BoxCollection::init()
{
    if (!Node::init()) {
        return false;
    }

    // ��ʼ������

    return true;
}

void BoxCollection::addObject(cocos2d::Sprite* object)
{
    // ��������ӵ�������
    objects.push_back(object);

    // ��������Ϊ��ǰ�ڵ���ӽڵ�
    this->addChild(object);
}

void BoxCollection::processObjects()
{
    // �������е���������
    for (auto object : objects)
    {
        // ��������Ӵ���������߼�
        // ���磬�ƶ�����ת�����ŵ�
        object->setPosition(object->getPosition() + cocos2d::Vec2(10, 0));
    }
}
