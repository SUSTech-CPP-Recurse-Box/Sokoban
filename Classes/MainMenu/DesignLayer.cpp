#include "DesignLayer.h"
#include "SysMenuScene.h"
#include "GameFrame/GameScene.h"
#include "Tools/SaveManager.h"
#include "Boxes/DesignControler.h"

using namespace std;

Scene* DesignLayer::scene()
{
    Scene* scene = Scene::create();
    DesignLayer* designLayer = DesignLayer::create();
    scene->addChild(designLayer);
    return scene;
}

bool DesignLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(DesignLayer::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Size winSize = Director::getInstance()->getWinSize();

    auto backGround = Sprite::create("MainMenu/MainBG.png");

    backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    addChild(backGround, 0);

    auto designTitle = Label::createWithTTF("Design Game", "fonts/Marker Felt.ttf", 48);
    designTitle->setPosition(Vec2(winSize.width / 2,
        winSize.height - designTitle->getContentSize().height));

    this->addChild(designTitle, 1);


    MenuItemFont::setFontSize(20);
    MenuItemFont::setFontName("Arial");
    DesignControler::get()->init(this);



    Label* back = Label::createWithTTF("Go back", "fonts/Marker Felt.ttf", 48);
    back->setColor(Color3B(31, 45, 150));
    MenuItemLabel* backMain = MenuItemLabel::create(back,
        [&](Ref* sender) {
            Scene* scene = SysMenuScene::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
        });
    Menu* backMenu = Menu::create(backMain, nullptr);
    backMenu->setPosition(Vec2(winSize.width / 2, 48));
    addChild(backMenu, 1);


    return true;
}

void DesignLayer::onLoad(Ref* pSender) {
    SaveInfo* info = SaveManager::getInstance()->info;
    if (info != nullptr) {
        Scene* scene = GameScene::scene(info->level_id, true);
        Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
    }
}
void DesignLayer::onMouseDown(EventMouse* event) {
    // 获取鼠标点击位置
    Vec2 targetPos = event->getLocationInView();
    targetPos = Director::getInstance()->convertToGL(targetPos);

    // 查找离目标位置最近的Sprite
    Sprite* nearestSprite = nullptr;
    float minDistance = FLT_MAX;

    // 遍历所有Sprite，计算距离并找到最小距离的Sprite
    for (Sprite* sprite : DesignControler::get()->disp) {
        float distance = sprite->getPosition().distance(targetPos);
        if (distance < minDistance) {
            minDistance = distance;
            nearestSprite = sprite;
        }
    }
    CCLOG("My String: %s", nearestSprite->getName().c_str());

    if (nearestSprite) {
        // 在这里处理找到的最近Sprite，可以输出信息或执行其他逻辑
        CCLOG("Found nearest sprite!");
    }
}

