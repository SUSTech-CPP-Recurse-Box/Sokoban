#ifndef _BOX_COLLECTION_H_
#define _BOX_COLLECTION_H_
#include "cocos2d.h"
#include "../GameFrame/GameScene.h"

#include "../Tools/MyColor.h"
#define MAX_SIZE 10
USING_NS_CC;

class BoxCollection :public cocos2d::Node {
private:
    Color3B color;
    Sprite* panels[MAX_SIZE][MAX_SIZE];
    GameScene* gameScene;
public://todo:add position
    long posX;
    long posY;
    long x;
    long y;
    float size;//考虑直接通过layer计算
    float boxSize;
    BoxCollection* father;
    Node* boxes[MAX_SIZE][MAX_SIZE];

    int boxes_type[MAX_SIZE][MAX_SIZE];
    void addPanel();
    BoxCollection(long x, long y, GameScene* gameScene, float size) {
        this->x = x;
        this->y = y;
        this->gameScene = gameScene;
        this->size = size;
        this->boxSize = x > y ? (size / (x + 1)) : size / (y + 1);
        //todo: 这里的背景板不知道会不会出问题
        addPanel();
    }
    virtual bool init() override;
    void updateSize();
    void setContentSize(const cocos2d::Size& contentSize) override {
        Node::setContentSize(contentSize);
        size = contentSize.width;
        boxSize = x > y ? (size / (x + 1)) : size / (y + 1);
        updateSize();
    }
    //todo: there are something wrong with the headfile, which lead here to bu Sprite instead of Box, if anyone can fix it?
    //README: object should be Box and if the Box is a true body,else it would be false body
    void addBox(Sprite* object, long x, long y, bool true_body, bool player);
    //todo: add logic as addBox above to addCollection, need notice that the copy of Collection is not finished yet.
    void addCollection(BoxCollection* object, long x, long y);
    bool processObjects(cocos2d::Node* startObject, long dirX, long dirY);
    void addBox(long x, long y);

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
};

#endif
