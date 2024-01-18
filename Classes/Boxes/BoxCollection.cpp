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
BoxCollection::BoxCollection(Color3B color, long x, long y, GameScene* gameScene,
    float size, long posX, long posY, Node* boxes[MAX_SIZE][MAX_SIZE],
    BoxCollection* father, BoxCollection* actual_box, bool real, int level)
    :x(x), y(y), gameScene(gameScene), size(size), color(color), father(father)
    , posX(posX), posY(posY) ,actual_box(actual_box),level(level){
    log("--------");
    log("size:%f",size);
    //todo: copy the box in boxes and state
    if (real) {
        actual_box = this;
    }
    this->boxSize = x > y ? (size / (x + 1)) : size / (y + 1);
    log("boxSize:%f", boxSize);
    log("--------");
    addPanel();
}
//todo: (尝试)实现对整个地图的放大和缩小
void BoxCollection::addBox(Sprite* object, long x, long y,bool true_body,bool player)
{
    // 将物体添加到集合中
    boxes[x][y] = (dynamic_cast<Box*>(object)->copy(x, y, boxSize, this,true_body,player));
    boxes[x][y]->setPosition(Vec2((2 * x - this->x + 1) * boxSize / 2, (-this->y + 2 * y +1) * boxSize / 2));
    // 将物体作为当前节点的子节点
    this->addChild(boxes[x][y], 1);
}
BoxCollection* BoxCollection::copy(float size, long posX, long posY, BoxCollection* father,bool real, int level) {
    return BoxCollection::create(color, x, y, gameScene, size, posX, posY, boxes, father, actual_box, real,level);
}
void BoxCollection::addCollection(BoxCollection* object, long x, long y, bool real)
{
    // 将物体添加到集合中
    boxes[x][y] = object->copy(boxSize,x,y,this,real,level+1);
    boxes[x][y]->setPosition(Vec2((2 * x - this->x + 1) * boxSize / 2, (-this->y + 2 * y +1) * boxSize / 2));
    // 将物体作为当前节点的子节点
    this->addChild(boxes[x][y], 1);
}

void BoxCollection::addBox(long x, long y) {
    boxes[x][y] = Box::create();
    this->addChild(boxes[x][y]);
}
//（Box继承自Sprite继承自node）
//todo: 现在这里没有任何规则
//todo: 需要写一个更优雅的移动作为一个函数,需要处理箱子移动过程，箱子移动之后坐标的变换
//todo: 需要把箱子位置计算提出一个函数
//todo: 这里的移动是通过playframe中的player移动传入player所在的BoxCollection（defaultBox）然后调用这个函数进行的

bool BoxCollection::processObjects(cocos2d::Node* startObject, long dirX, long dirY)
{
    int valid = 1;
    Box* box = dynamic_cast<Box*>(startObject);
    std::stack<Node*> myNode;
    myNode.push(box);
    Node* next = box;
    while (1) {
        int next_x, next_y;
        if (dynamic_cast<Box*>(next)) {
            next_x = dynamic_cast<Box*>(next)->posX + dirX;
            next_y = dynamic_cast<Box*>(next)->posY + dirY;
        }
        else {
            next_x = dynamic_cast<BoxCollection*>(next)->posX + dirX;
            next_y = dynamic_cast<BoxCollection*>(next)->posY + dirY;
        }
        if (!(next_x >= 0 && next_x < MAX_SIZE && next_y >= 0 && next_y < MAX_SIZE)) {
            valid = 0;
            break;
        }
        if (!dynamic_cast<Box*>(boxes[next_x][next_y])&& !dynamic_cast<BoxCollection*>(boxes[next_x][next_y])) {
            break;
        }
        myNode.push(boxes[next_x][next_y]);
        next = boxes[next_x][next_y];
        log("next_x:%ld;next_y:%ld;", next_x, next_y);
    }
    if (valid) {
        while (!myNode.empty())
        {
            int next_x,  next_y;
            Node* nd = myNode.top();
            if (dynamic_cast<Box*>(nd)) {
                next_x = dynamic_cast<Box*>(nd)->posX + dirX;
                next_y = dynamic_cast<Box*>(nd)->posY + dirY;
                dynamic_cast<Box*>(nd)->posX = next_x;
                dynamic_cast<Box*>(nd)->posY = next_y;

            }
            else {
                next_x = dynamic_cast<BoxCollection*>(nd)->posX + dirX;
                next_y = dynamic_cast<BoxCollection*>(nd)->posY + dirY;
                dynamic_cast<BoxCollection*>(nd)->posX = next_x;
                dynamic_cast<BoxCollection*>(nd)->posY = next_y;
            }
            boxes[next_x ][next_y ] = nd;
            boxes[next_x- dirX][next_y- dirY] = nullptr;
            nd->runAction(MoveBy::create(0.2, Vec2(dirX * boxSize, dirY * boxSize)));
            myNode.pop();
        }
    }
    return true;
}

void BoxCollection::addPanel() {
    for (long i = 0; i < x; i++) {
        for (long j = 0; j < y; j++) {
            panels[i][j] = Sprite::create("MainMenu/boxes/panel.png");
            panels[i][j]->setColor(color);
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
    log("%d", x);
    for (long i = 0; i < x; i++) {
        for (long j = 0; j < y; j++) {
            panels[i][j]->setContentSize(Size(boxSize, boxSize));
            panels[i][j]->setPosition(Vec2((2 * i - x + 1) * boxSize / 2, (-2 * j + y - 1) * boxSize / 2));
        }
    }
}
