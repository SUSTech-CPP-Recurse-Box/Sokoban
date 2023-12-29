#ifndef _BOX_H_
#define _BOX_H_

#include "cocos2d.h"
#include "BoxCollection.h"
#include "../Tools/MyColor.h"
USING_NS_CC;


class Box : public Sprite {
private:

public:
    long posX;//
    long posY;//
    Color3B color;//copy
    BoxCollection* father;
    float size;
    static Box* player;
    bool visible;
    bool true_body;//copy
    Box* actual_box;// copy
    Box();
    Box(Color3B color, Box* actual_box, long posX, long posY, float size, BoxCollection* father, bool true_body, bool player);
    virtual bool init();
    virtual void update(long posX, long posY);
    virtual bool set_to_player(Box* box);
    Box* copy(long posX, long posY, float size, BoxCollection* father, bool true_body, bool player);
    static Box* create()
    {
        Box* pRet = new(std::nothrow) Box();
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
    };
    static Box* create(Color3B color, Box* actual_box, long posX, long posY, float size, BoxCollection* father, bool true_body, bool player)
    {
        Box* pRet = new(std::nothrow) Box(color, actual_box, posX, posY, size, father,  true_body,  player);
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

#endif /* defined(__MW_CPP_Box_H__) */