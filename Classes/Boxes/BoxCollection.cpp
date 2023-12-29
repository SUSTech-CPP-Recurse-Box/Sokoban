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
BoxCollection::BoxCollection(Color3B color, long x, long y, GameScene* gameScene,
    float size, long posX, long posY, Node* boxes[MAX_SIZE][MAX_SIZE],
    BoxCollection* father, BoxCollection* actual_box, bool real) 
    :x(x), y(y), gameScene(gameScene), size(size), color(color), father(father)
    , posX(posX), posY(posY) ,actual_box(actual_box){
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
//todo: (����)ʵ�ֶ�������ͼ�ķŴ����С
void BoxCollection::addBox(Sprite* object, long x, long y,bool true_body,bool player)
{
    // ���������ӵ�������
    boxes[x][y] = (dynamic_cast<Box*>(object)->copy(x, y, boxSize, this,true_body,player));
    boxes[x][y]->setPosition(Vec2((2 * x - this->x + 1) * boxSize / 2, (this->y - 2 * y - 1) * boxSize / 2));
    // ��������Ϊ��ǰ�ڵ���ӽڵ�
    this->addChild(boxes[x][y], 1);
}
BoxCollection* BoxCollection::copy(float size, long posX, long posY, BoxCollection* father,bool real) {
    return BoxCollection::create(color, x, y, gameScene, size, posX, posY, boxes, father, actual_box, real);
}
void BoxCollection::addCollection(BoxCollection* object, long x, long y, bool real)
{
    // ���������ӵ�������
    boxes[x][y] = object->copy(boxSize,x,y,this,real);
    boxes[x][y]->setPosition(Vec2((2 * x - this->x + 1) * boxSize / 2, (this->y - 2 * y - 1) * boxSize / 2));
    // ��������Ϊ��ǰ�ڵ���ӽڵ�
    this->addChild(boxes[x][y], 1);
}

void BoxCollection::addBox(long x, long y) {
    boxes[x][y] = Box::create();
    this->addChild(boxes[x][y]);
}
//��Box�̳���Sprite�̳���node��
//todo: ��������û���κι���
//todo: ��Ҫдһ�������ŵ��ƶ���Ϊһ������,��Ҫ���������ƶ����̣������ƶ�֮������ı任
//todo: ��Ҫ������λ�ü������һ������
//todo: ������ƶ���ͨ��playframe�е�player�ƶ�����player���ڵ�BoxCollection��defaultBox��Ȼ���������������е�
bool BoxCollection::processObjects(cocos2d::Node* startObject, long dirX, long dirY)
{
    if (dynamic_cast<Box*>(startObject)) {
        Box* box = dynamic_cast<Box*>(startObject);
        boxes[box->posX][box->posY] = nullptr;
        boxes[box->posX + dirX][y + dirY] = box;
        box->runAction(MoveBy::create(0.2, Vec2(dirX * boxSize, dirY * boxSize)));
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

    //todo:�����ڲ�ȫ������Ĵ�С
    log("boxSize:%f", boxSize);
    log("%d", x);
    for (long i = 0; i < x; i++) {
        for (long j = 0; j < y; j++) {
            panels[i][j]->setContentSize(Size(boxSize, boxSize));
            panels[i][j]->setPosition(Vec2((2 * i - x + 1) * boxSize / 2, (-2 * j + y - 1) * boxSize / 2));
        }
    }
}