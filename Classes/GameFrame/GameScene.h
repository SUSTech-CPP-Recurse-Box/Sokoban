#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

using pii = std::pair<int, int>;

class GameScene : public Layer {
protected:
    EventListenerKeyboard* _listener;
    EventListenerMouse* mouseListener;
public:
    int lid;
    static Scene* scene(int lid, bool saved);
    virtual bool init();

    CREATE_FUNC(GameScene);

    void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void GameScene::onMouseScroll(Event* event);

    void GameScene::onUndo(Ref* pSender, int lid, std::vector<pii>);
};

#endif /* defined(__GAME_SCENE_H__) */