#ifndef __HELP_LAYER_H__
#define __HELP_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class HelpLayer : public Layer {

public:
    static Scene* scene();
    void onLevelSelect(Ref* pSender, int idx);


    virtual bool init();
    CREATE_FUNC(HelpLayer);
};

#endif /* defined(__HELP_LAYER_H__) */

