#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

using pii = std::pair<int, int>;

class GameScene : public Layer {
protected:
    EventListenerKeyboard* _listener;
    EventListenerMouse* mouseListener;
    Vec2 startPos;
public:
    int lid;
    static Scene* scene(int lid, bool saved);
    virtual bool init();

    CREATE_FUNC(GameScene);

    void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void GameScene::onMouseScroll(Event* event);

    void GameScene::onUndo(Ref* pSender);

    void GameScene::onRestart(Ref* pSender);

    void GameScene::onMouseDown(Event* event);

    void  GameScene::onMouseUp(Event* event);

};

#endif /* defined(__GAME_SCENE_H__) */