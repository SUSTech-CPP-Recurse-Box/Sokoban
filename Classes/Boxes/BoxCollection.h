#ifndef _BOX_COLLECTION_H_
#define _BOX_COLLECTION_H_
#include "cocos2d.h"
#include "../GameFrame/GameScene.h"
#include "../Tools/MyColor.h"
#include "../Tools/pos.h"
#include <stack>
#include <cmath>
#define MAX_SIZE 10
#define MAX_LEVEL 5
USING_NS_CC;
//todo:maybe some of the same variables should be init as a pointer so that
//todo:we do not need to update them everytime we change one

//todo: add bondary
class BoxCollection :public cocos2d::Node {
private:
    Color3B color;
    Sprite* panels[MAX_SIZE][MAX_SIZE];
    GameScene* gameScene;
public:
    int level;
    long posX;
    long posY;
    long box;
    long x;
    long y;
    float size;//考虑直接通过layer计算
    float boxSize;
    BoxCollection* actual_box;
    BoxCollection* father;
    Node* boxes[MAX_SIZE][MAX_SIZE];
    int state[MAX_SIZE][MAX_SIZE];//put all the bondary here
    void addPanel();
    BoxCollection(long x, long y, GameScene* gameScene, float size)
        :x(x),y(y),gameScene(gameScene),size(size),color(MyColor::RandomLight()),actual_box(this),level(0) {
        this->boxSize = x > y ? (size / (x + 1)) : size / (y + 1);
        addPanel();
        for (int i = 0; i < MAX_SIZE; ++i) {
            for (int j = 0; j < MAX_SIZE; ++j) {
                boxes[i][j] = nullptr;  // 或者指向你想要的初始节点
            }
        }
    }
    BoxCollection(Color3B color, long x, long y, GameScene* gameScene,
        float size, long posX, long posY, Node* boxes[MAX_SIZE][MAX_SIZE],
        BoxCollection* father, BoxCollection* actual_box,bool real,int level);
    virtual bool init() override;
    void updateSize();
    void setContentSize(const cocos2d::Size& contentSize) override {
        Node::setContentSize(contentSize);
        size = contentSize.width;
        boxSize = x > y ? (size / (x + 1)) : size / (y + 1);
        updateSize();
    }
    BoxCollection* copy(float size, long posX, long posY, BoxCollection* father, bool real, int level);
    //todo: there are something wrong with the headfile, which lead here to bu Sprite instead of Box, if anyone can fix it?
    //README: object should be Box and if the Box is a true body,else it would be false body
    Sprite* addBox(Sprite* object, long x, long y, bool true_body, bool player);
    BoxCollection* addCollection(BoxCollection* object, long x, long y,bool real);
    bool processObjects(cocos2d::Node* startObject, long dirX, long dirY, bool belong);
    void addBox(long x, long y);
    //pos* nextPos(pos* p,pos* move);
    static BoxCollection* create(long x, long y, GameScene* gameScene, float size)
    {
        BoxCollection* pRet = new(std::nothrow) BoxCollection(x, y, gameScene, size);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    static BoxCollection* create(Color3B color, long x, long y, GameScene* gameScene,
        float size, long posX, long posY, Node* boxes[MAX_SIZE][MAX_SIZE], BoxCollection* father,
        BoxCollection* actual_box, bool real, int level)
    {
        BoxCollection* pRet = new(std::nothrow) BoxCollection(color, x, y, gameScene,size,posX,posY,boxes,father, actual_box,real,level);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
};

#endif
