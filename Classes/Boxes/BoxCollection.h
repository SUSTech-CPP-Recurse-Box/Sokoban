#ifndef _BOX_COLLECTION_H_
#define _BOX_COLLECTION_H_
#include "cocos2d.h"
USING_NS_CC;
class BoxCollection :public cocos2d::Node {
public:
	virtual bool init() override;
	void addObject(cocos2d::Sprite* object);
	void processObjects();
	CREATE_FUNC(BoxCollection);
private:
	std::vector<Sprite*> objects;
};

#endif
