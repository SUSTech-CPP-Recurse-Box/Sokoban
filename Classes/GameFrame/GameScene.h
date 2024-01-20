#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Layer {
protected:
    EventListenerKeyboard* _listener;
public:
    int lid;
    static Scene* scene(int lid);
    virtual bool init();

    CREATE_FUNC(GameScene);

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

};

#endif /* defined(__GAME_SCENE_H__) */