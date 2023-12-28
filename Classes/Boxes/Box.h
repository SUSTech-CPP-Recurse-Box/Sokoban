#ifndef _BOX_H_
#define _BOX_H_

#include "cocos2d.h"
USING_NS_CC;


class Box : public Sprite {

private:
    Color3B color;
    

public:
    float size;
    static Box* player;
    bool visible;
    bool true_body;
    Box* actual_box;
    Box* father;
    Box();
    virtual bool init();
    virtual void update(int x,int y);
    virtual bool set_to_player(Box* box);
    CREATE_FUNC(Box);

};

#endif /* defined(__MW_CPP_Box_H__) */