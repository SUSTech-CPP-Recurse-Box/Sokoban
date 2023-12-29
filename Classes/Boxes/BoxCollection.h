#ifndef _BOX_COLLECTION_H_
#define _BOX_COLLECTION_H_
#include "cocos2d.h"
#include "../GameFrame/GameScene.h"
#define MAX_SIZE 10
USING_NS_CC;

class BoxCollection :public cocos2d::Node {
private:
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
    BoxCollection(long x, long y,GameScene* gameScene,float size) {
        this->x = x;
        this->y = y;
        this->gameScene = gameScene;
        this->size = size;
        this->boxSize = x > y ? (size / x) : size / y;
        //todo: 这里的背景板不知道会不会出问题
        addPanel();
    }
	virtual bool init() override;
    void updateSize();
    void setContentSize(const cocos2d::Size& contentSize) override {
        Node::setContentSize(contentSize);
        size = contentSize.width;
        boxSize = x > y ? (size / x) : size / y;
        updateSize();
    }
	void addBox(cocos2d::Sprite* object, long x, long y);
    void addCollection(BoxCollection* object, long x, long y);
	void processObjects(cocos2d::Sprite* startObject, long dirX, long dirY);
    void addBox(long x, long y);
    
    static BoxCollection* create(long x, long y,GameScene* gameScene,float size)
    { 
        BoxCollection* pRet = new(std::nothrow) BoxCollection(x,y, gameScene,size);
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
