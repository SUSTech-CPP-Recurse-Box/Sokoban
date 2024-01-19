#ifndef _BOX_H_
#define _BOX_H_
#include "cocos2d.h"
#include "BoxCollection.h"
#include "../Tools/MyColor.h"

USING_NS_CC;

//todo:maybe some of the same variables should be init as a pointer so that
//todo:we do not need to update them everytime we change one
//todo: the update may have some error now
class Box : public Sprite {
public:
    long posX;//
    long posY;//
    int type;
    Color3B color;//copy
    BoxCollection* father;
    float size;
    static Box* player;
    bool visible;
    bool is_bondary=false;
    bool true_body;//copy
    Box* actual_box;// copy

    Box();
    Box( bool is_bondary);
    Box(Color3B color, Box* actual_box, long posX, long posY, float size, BoxCollection* father, bool true_body, bool player,bool is_bondary);
    virtual bool init();
    virtual void update(long posX, long posY);
    virtual bool set_to_player(Box* box);
    Box* copy(long posX, long posY, float size, BoxCollection* father, bool true_body, bool player);
    void set_to_bondary() {
        is_bondary = true;
        this->initWithFile("MainMenu/boxes/boundary.png");
    }
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
    static Box* createBundary()
    {
        Box* pRet = new(std::nothrow) Box(true);
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
    static Box* create(Color3B color, Box* actual_box, long posX, long posY, float size, BoxCollection* father, bool true_body, bool player,bool is_bondary)
    {
        Box* pRet = new(std::nothrow) Box(color, actual_box, posX, posY, size, father,  true_body,  player, is_bondary);
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