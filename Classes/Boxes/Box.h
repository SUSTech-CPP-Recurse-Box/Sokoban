#ifndef _BOX_H_
#define _BOX_H_

#include "cocos2d.h"
#include "BoxCollection.h"
USING_NS_CC;


class Box : public Sprite {
public:
    int x;
    int y;
    Color3B color;
    BoxCollection* father;
    float size;
    static Box* player;
    bool visible;
    bool true_body;
    Box* actual_box;
    Box();
    virtual bool init();
    void setSize(float size);
    virtual void update(int x,int y);
    virtual bool set_to_player(Box* box);
    CREATE_FUNC(Box);

};

#endif /* defined(__MW_CPP_Box_H__) */