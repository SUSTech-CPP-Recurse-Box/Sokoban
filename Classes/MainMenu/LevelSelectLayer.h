#ifndef __LEVEL_LAYER_H__
#define __LEVEL_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class LevelSelectLayer : public Layer {

public:
    static Scene* scene();
    void onLevelSelect(Ref* pSender, int idx);


    virtual bool init();
    CREATE_FUNC(LevelSelectLayer);
};

#endif /* defined(__LEVEL_LAYER_H__) */
