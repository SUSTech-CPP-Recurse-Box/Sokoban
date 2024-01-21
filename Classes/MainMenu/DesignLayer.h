#ifndef __DESIGN_LAYER_H__
#define __DESIGN_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class DesignLayer : public Layer {

public:

	static Scene* scene();
	void onLoad(Ref* pSender);

	virtual bool init();
	CREATE_FUNC(DesignLayer);
	void onMouseDown(EventMouse* event);
	void onMouseMove(EventMouse* event);

};

#endif /* defined(__Design_LAYER_H__) */
