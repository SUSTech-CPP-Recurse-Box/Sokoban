#include "BoxCollection.h"
#include "Box.h"
#include "..\Tools\MyColor.h"
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
void BoxCollection::addBox(cocos2d::Sprite* object, long x, long y)
{
    // 将物体添加到集合中
    boxes[x][y] = object;
    dynamic_cast<Box*>(object)->posX = x;
    dynamic_cast<Box*>(object)->posY = y;
    dynamic_cast<Box*>(object)->father=this;
    object->setContentSize(Size(boxSize, boxSize));
    object->setPosition(Vec2((2*x-this->x+1)*boxSize/2, (this->y-2*y-1) * boxSize/2));
    // 将物体作为当前节点的子节点
    this->addChild(object,1);
}
void BoxCollection::addCollection(BoxCollection* object, long x, long y)
{
    // 将物体添加到集合中
    boxes[x][y] = object;
    object->posX = x;
    object->posY = y;
    object->father = this;
    object->setContentSize(Size(boxSize, boxSize));
    object->setPosition(Vec2((2 * x - this->x + 1) * boxSize / 2, (this->y - 2 * y - 1) * boxSize / 2));
    // 将物体作为当前节点的子节点
    this->addChild(object, 1);
}

void BoxCollection::addBox(long x, long y) {
    boxes[x][y] = Box::create();
    this->addChild(boxes[x][y]);
}
//todo: 在这里加逻辑判断是否可动，物体现在传入的是Sprite，需要改成node（Box继承自Sprite继承自node）
//todo: 现在这里没有任何规则
//todo: 需要写一个更优雅的移动作为一个函数
//todo: 需要把箱子位置计算提出一个函数
//todo: 这里的移动是通过playframe中的player移动传入player所在的BoxCollection（defaultBox）然后调用这个函数进行的
void BoxCollection::processObjects(cocos2d::Sprite* startObject, long dirX, long dirY)
{
    Box* box = dynamic_cast<Box*>(startObject);
    boxes[box->posX][box->posY] = nullptr;
    boxes[box->posX + dirX][y + dirY] = box;
    box->runAction(MoveBy::create(0.2, Vec2(dirX * boxSize, dirY * boxSize)));
}
void BoxCollection::addPanel() {
    Color3B c = MyColor::RandomLight();
    for (long i = 0; i < x; i++) {
        for (long j = 0; j < y; j++) {
            panels[i][j] = Sprite::create("MainMenu/boxes/panel.png");
            panels[i][j]->setColor(c);
            panels[i][j]->setContentSize(Size(boxSize, boxSize));
            panels[i][j]->setPosition(Vec2((2 * i - this->x + 1) * boxSize / 2, (this->y - 2 * j - 1) * boxSize / 2));
            //log("i=%f;j=%f;posX=%f;posY=%f", i, j, (2 * i - this->x + 1) * boxSize / 2, (this->y - 2 * j - 1) * boxSize / 2);
            this->addChild(panels[i][j]);
        }
    }
}
void BoxCollection::updateSize() {
    
    //todo:更新内部全部方块的大小
    log("boxSize:%f", boxSize);
    log("%d",x);
    for (long i = 0; i < x; i++) {
        for (long j = 0; j < y; j++) {
            float new_x = (2 * i - x + 1) * boxSize / 2; 
            float new_y = (- 2 * j+y - 1) * boxSize / 2;
            log("i=%d;j=%d;posX=%f;posY=%f;this->x=%d;this->y=%d", i, j, (2 * i - x + 1) * boxSize / 2, (-2 * j + y - 1) * boxSize / 2, x, y);
            log(";this->x=%d;this->y=%d", x, y);
            panels[i][j]->setContentSize(Size(boxSize, boxSize));
            //if (i == 0 && j == 0) {
                panels[i][j]->runAction(MoveTo::create(0.2, Vec2(new_x, new_y)));
            //}
        }
        log("--------------------------");
    }
}
