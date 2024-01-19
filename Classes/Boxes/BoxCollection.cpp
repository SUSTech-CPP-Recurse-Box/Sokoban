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
    //log("--------");
    //log("size:%f",size);
    if (real) {
        actual_box = this;
    }
    this->boxSize = x > y ? (size / (x + 1)) : size / (y + 1);
    for (int i = 0; i < MAX_SIZE; i++) {
        for(int j=0;j<MAX_SIZE;j++){
            if (dynamic_cast<Box*>(boxes[i][j])){
                Box* tmp = dynamic_cast<Box*>(boxes[i][j]);
                this->boxes[i][j] = addBox(tmp, i, j, false, false);
            }
            else if (dynamic_cast<BoxCollection*>(boxes[i][j])) {
                this->boxes[i][j] = addCollection(dynamic_cast<BoxCollection*>(boxes[i][j]), i, j, false);
            }
            else {
                this->boxes[i][j] = nullptr;
            }
        }
    }
    //todo: copy the box in boxes and state
    
    log("boxSize:%f", boxSize);
    log("--------");
    addPanel();
}
//todo: (尝试)实现对整个地图的放大和缩小
Sprite* BoxCollection::addBox(Sprite* object, long x, long y,bool true_body,bool player)
{
    // 将物体添加到集合中
    boxes[x][y] = (dynamic_cast<Box*>(object)->copy(x, y, boxSize, this,true_body,player));
    boxes[x][y]->setPosition(Vec2((2 * x - this->x + 1) * boxSize / 2, (-this->y + 2 * y + 1) * boxSize / 2));
    // 将物体作为当前节点的子节点
    this->addChild(boxes[x][y], 1);
    dynamic_cast<Box*>(boxes[x][y])->father = this;
    return dynamic_cast<Sprite*>(boxes[x][y]);
}
BoxCollection* BoxCollection::copy(float size, long posX, long posY, BoxCollection* father,bool real, int level) {
    return BoxCollection::create(color, x, y, gameScene, size, posX, posY, boxes, father, actual_box, real,level);
}
BoxCollection* BoxCollection::addCollection(BoxCollection* object, long x, long y, bool real)
{
    // 将物体添加到集合中
    boxes[x][y] = object->copy(boxSize,x,y,this,real,level+1);
    boxes[x][y]->setPosition(Vec2((2 * x - this->x + 1) * boxSize / 2, (-this->y + 2 * y +1) * boxSize / 2));
    // 将物体作为当前节点的子节点
    this->addChild(boxes[x][y], 1);
    dynamic_cast<BoxCollection*>(boxes[x][y])->father = this;
    return dynamic_cast<BoxCollection*>(boxes[x][y]);
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

bool BoxCollection::processObjects(cocos2d::Node* startObject, long dirX, long dirY, int belong)//1:属于，0：进去，-1：出来
{
    int valid = 1;
    std::stack<Node*> myNode;
    myNode.push(startObject);
    Node* next = startObject;
    int next_x, next_y;
    int orgX, orgY;
    if (belong==1) {
        if (dynamic_cast<Box*>(next)) {
            next_x = dynamic_cast<Box*>(next)->posX + dirX;
            next_y = dynamic_cast<Box*>(next)->posY + dirY;
        }
        else {
            next_x = dynamic_cast<BoxCollection*>(next)->posX + dirX;
            next_y = dynamic_cast<BoxCollection*>(next)->posY + dirY;
        }
    }
    else if (belong == 0) {
        if (dirX != 0) {
            next_y = y-y/2-1;
            next_x = dirX > 0 ? 0 : x-1;
        }
        else {
            next_x= x-x/2-1;
            next_y = dirY > 0 ? 0 : y - 1;
        }
        orgX = next_x;
        orgY = next_y;
    }
    else if (belong == -1) {
        next_x = dynamic_cast<BoxCollection*>(startObject)->father->posX + dirX;
        next_y = dynamic_cast<BoxCollection*>(startObject)->father->posY + dirY;
    }
    while (1) {
        
        if (!(next_x >= 0 && next_x < x && next_y >= 0 && next_y < y)) {//边界
            if (this) {
                valid = 0;
                log("11111");
                break;
            }
            if (father) {
                valid = 0;
                log("22222222");
                break;
            }
            BoxCollection* father = this->father;
            while (!myNode.empty())
            {
                Node* nd = myNode.top();
                if (father->processObjects(nd, dirX, dirY, -1)) {
                    if (dynamic_cast<Box*>(myNode.top())) {
                        boxes[dynamic_cast<Box*>(myNode.top())->posX][dynamic_cast<Box*>(myNode.top())->posY] = nullptr;
                    }
                    else {
                        boxes[dynamic_cast<BoxCollection*>(myNode.top())->posX][dynamic_cast<BoxCollection*>(myNode.top())->posY] = nullptr;
                    }
                    myNode.top()->removeFromParent();
                    myNode.pop();
                    valid = 1;
                    break;
                }
            }
            valid = 0;
            break;
            
        }
        if (!dynamic_cast<Box*>(boxes[next_x][next_y]) && !dynamic_cast<BoxCollection*>(boxes[next_x][next_y])) {
            break;
        }
        if (boxes[next_x][next_y]!=nullptr&&dynamic_cast<Box*>(boxes[next_x][next_y])) {
            if (dynamic_cast<Box*>(boxes[next_x][next_y])->is_bondary) {
                valid = 0;
                break;
            }
        }
        
        myNode.push(boxes[next_x][next_y]);
        next = boxes[next_x][next_y];
        log("next_x:%ld;next_y:%ld;", next_x, next_y);
        if (dynamic_cast<Box*>(next)) {
            next_x = dynamic_cast<Box*>(next)->posX + dirX;
            next_y = dynamic_cast<Box*>(next)->posY + dirY;
        }
        else {
            next_x = dynamic_cast<BoxCollection*>(next)->posX + dirX;
            next_y = dynamic_cast<BoxCollection*>(next)->posY + dirY;
        }
    }
    //如果撞墙了依次往前看，看看是否能进去
    if (!valid) {
        while (!myNode.empty())
        {
            Node* nd = myNode.top();
            myNode.pop();
            if (dynamic_cast<BoxCollection*>(nd)) {
                if (dynamic_cast<BoxCollection*>(nd)->processObjects(myNode.top(), dirX, dirY, 0)) {
                    if (dynamic_cast<Box*>(myNode.top())) {
                        boxes[dynamic_cast<Box*>(myNode.top())->posX][dynamic_cast<Box*>(myNode.top())->posY] = nullptr;
                    }
                    else {
                        boxes[dynamic_cast<BoxCollection*>(myNode.top())->posX][dynamic_cast<BoxCollection*>(myNode.top())->posY] = nullptr;
                    }
                    myNode.top()->removeFromParent();
                    myNode.pop();
                    valid = 1;
                    break;
                }
            }
        }
    }
    if (valid) {
        while (!myNode.empty())
        {
            long next_x, next_y;
            Node* nd = myNode.top();
            myNode.pop();
            if (myNode.empty() && !belong) {
                next_x = orgX;
                next_y = orgY;
                if (dynamic_cast<Box*>(nd)) {
                    this->addBox(dynamic_cast<Box*>(nd), next_x, next_y, dynamic_cast<Box*>(nd)->true_body, nd == dynamic_cast<Box*>(nd)->player);
                }
                else {
                    dynamic_cast<BoxCollection*>(nd)->posX = next_x;
                    dynamic_cast<BoxCollection*>(nd)->posY = next_y;
                    dynamic_cast<BoxCollection*>(nd)->setContentSize(Size(boxSize, boxSize));
                    dynamic_cast<BoxCollection*>(nd)->father = this;
                    dynamic_cast<BoxCollection*>(nd)->size = boxSize;
                }
            }
            else {
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
                boxes[next_x][next_y] = nd;
                boxes[next_x - dirX][next_y - dirY] = nullptr;
                nd->runAction(MoveBy::create(0.2, Vec2(dirX * boxSize, dirY * boxSize)));

            }
        }
    }

    return valid;
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
