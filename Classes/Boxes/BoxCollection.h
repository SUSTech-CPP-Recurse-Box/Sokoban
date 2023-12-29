#ifndef _BOX_COLLECTION_H_
#define _BOX_COLLECTION_H_
#include "cocos2d.h"
#include "../GameFrame/GameScene.h"
#define MAX_SIZE 10
USING_NS_CC;

class BoxCollection :public cocos2d::Node {
private:
    GameScene* gameScene;
public://todo:add position
	int x;
	int y;
    float size;//考虑直接通过layer计算
    float boxSize;
    BoxCollection* father;
	Node* boxes[MAX_SIZE][MAX_SIZE];

	int boxes_type[MAX_SIZE][MAX_SIZE];
    BoxCollection(int x, int y,GameScene* gameScene,float size) {
        this->x = x;
        this->y = y;
        this->gameScene = gameScene;
        this->size = size;
        this->boxSize = x > y ? (size / x) : size / y;
        //todo: 这里的背景板不知道会不会出问题
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                auto mySprite = Sprite::create("MainMenu/boxes/panel.png");
                mySprite->setContentSize(Size(boxSize, boxSize));
                mySprite->setPosition(Vec2((2 * i - this->x + 1) * boxSize / 2, (this->y - 2 * j - 1) * boxSize / 2));
                this->addChild(mySprite);
            }
        }
    }
	virtual bool init() override;
	void addBox(cocos2d::Sprite* object,int x,int y);
	void processObjects(cocos2d::Sprite* startObject,int dirX,int dirY);
    void addBox(int x,int y);
    void addPanel();
    static BoxCollection* create(int x,int y,GameScene* gameScene,float size)
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
