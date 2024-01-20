#include "GameScene.h"
#include "../Boxes/Box.h"
#include "../Boxes/BoxCollection.h"
#include "../MainMenu/SysMenuScene.h"
#include "../Boxes/controler.h"
#define DEFAULT_SPACE_SIZE 10


Scene* GameScene::scene()
{
    Scene* scene = Scene::create();
    GameScene* GameScene = GameScene::create();
    scene->addChild(GameScene);
    return scene;
}
//todo:这里增加传入参数用来分辨是哪个level
//todo:读入关卡配置文件
//todo:按照关卡配置文件生成地图
//todo:在地图中放置的箱子应为原始箱子的复制体（用于实现多重嵌套，分身等功能）

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();

    auto backGround = Sprite::create("MainMenu/MainBG.png");
    backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    log("x:%lf;y:%lf", winSize.width / 2, winSize.height / 2);
    addChild(backGround, 0);
    controler::get()->init();
    controler::get()->draw(this, 200);
    //====================================================================
    //auto defaultBox = BoxCollection::create(5, 5, this,winSize.height/2);
    //defaultBox->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    //this->addChild(defaultBox);
    //log("default panel boxSize: %f", defaultBox->boxSize);
    //auto player = Box::create();
    //auto b1 = Box::createBundary();
    //player->set_to_player(player);
    //defaultBox->addBox(player,0,3,true,true);
    //defaultBox->addBox(player, 3, 2, false, true);
    //auto smallBox = BoxCollection::create(5, 5, this, winSize.height / 2);
    //smallBox=defaultBox->addCollection(smallBox, 2, 4,true);
    //smallBox->addBox(b1, 2, 0, false, true);

    //log("smallBox panel boxSize: %f", smallBox->boxSize);
    //=====================================================================
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
//todo: 移动函数入口在这里
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        Box::player->father->processObjects(Box::player, 0, 1,true);
        log("go up");
    }else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        Box::player->father->processObjects(Box::player, 0, -1, true);
        log("go down");
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        Box::player->father->processObjects(Box::player, -1,0, true);
        log("go left");
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        Box::player->father->processObjects(Box::player, 1, 0, true);
        log("go right");
    }
}


