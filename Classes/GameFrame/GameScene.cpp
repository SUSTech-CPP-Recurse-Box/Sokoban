#include "GameScene.h"
#include "../MainMenu/SysMenuScene.h"


Scene* GameScene::scene()
{
    Scene* scene = Scene::create();
    GameScene* GameScene = GameScene::create();
    scene->addChild(GameScene);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }



    Size winSize = Director::getInstance()->getWinSize();

    auto backGround = Sprite::create("MainMenu/MainBG.png");
    backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    addChild(backGround, 0);
    auto greenSprite = Sprite::create("MainMenu/MainBG.png");

    // 设置Sprite的颜色为绿色，可以使用Color3B或Color4B
    greenSprite->setColor(Color3B::GREEN);

    // 设置Sprite的位置
    greenSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));; // 根据你的需求设置位置

    // 设置Sprite的大小为10x10
    greenSprite->setContentSize(Size(10, 10));

    // 将Sprite添加到场景中
    this->addChild(greenSprite);
    _listener = EventListenerKeyboard::create();
    _listener->onKeyPressed=CC_CALLBACK_2(GameScene::onKeyPressed, this);
    _listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    auto levelTitle = Label::createWithTTF("Load Game", "fonts/Marker Felt.ttf", 48);
    levelTitle->setPosition(Vec2(winSize.width / 2,
        winSize.height - levelTitle->getContentSize().height));

    this->addChild(levelTitle, 1);


    MenuItemFont::setFontSize(20);
    MenuItemFont::setFontName("Arial");

    Label* back = Label::createWithTTF("Go back", "fonts/Marker Felt.ttf", 48);
    back->setColor(Color3B(31, 45, 150));
    MenuItemLabel* backMain = MenuItemLabel::create(back,
        [&](Ref* sender) {
            Scene* scene = SysMenuScene::create();
            Director::getInstance()->replaceScene(TransitionFade::create(1.2f, scene));
        });
    Menu* backMenu = Menu::create(backMain, nullptr);
    backMenu->setPosition(Vec2(winSize.width / 2, 48));
    addChild(backMenu, 1);


    return true;
}
void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        log("go up");
    }else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        log("go down");
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        log("go left");
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        log("go right");
    }
}


