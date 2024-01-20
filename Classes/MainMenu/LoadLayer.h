#ifndef __LOAD_LAYER_H__
#define __LOAD_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class LoadLayer : public Layer {

public:
    static Scene* scene();
    void onLoad(Ref* pSender);

    virtual bool init();
    CREATE_FUNC(LoadLayer);

};

#endif /* defined(__LOAD_LAYER_H__) */
