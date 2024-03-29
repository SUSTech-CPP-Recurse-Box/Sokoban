#include "DesignLayer.h"
#include "SysMenuScene.h"
#include "GameFrame/GameScene.h"
#include "Tools/UserLevelManager.h"
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
    listener->onMouseMove = CC_CALLBACK_1(DesignLayer::onMouseMove, this);
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

    Vector<MenuItem*> designOptItems;
    Label* saveLabel = Label::createWithTTF("Save", "fonts/Marker Felt.ttf", 48);
    saveLabel->setColor(Color3B(31, 45, 150));
    MenuItemLabel* saveItem = MenuItemLabel::create(saveLabel,
        [&](Ref* sender) {
            std::vector<dataset*> data=DesignControler::get()->data;
            UserLevelManager::getInstance()->saveLevel(data);
        });
    designOptItems.pushBack(saveItem);

    Label* back = Label::createWithTTF("Go back", "fonts/Marker Felt.ttf", 48);
    back->setColor(Color3B(31, 45, 150));
    MenuItemLabel* backMain = MenuItemLabel::create(back,
        [&](Ref* sender) {
            Scene* scene = SysMenuScene::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
        });
    designOptItems.pushBack(backMain);

    Menu* designOptMenu = Menu::createWithArray(designOptItems);
    designOptMenu->alignItemsHorizontallyWithPadding(50);
    designOptMenu->setPosition(Vec2(winSize.width / 2, 48));
    addChild(designOptMenu, 1);


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
    targetPos.y = Director::getInstance()->getVisibleSize().height - targetPos.y;
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
    if (minDistance < 30) {
        //CCLOG("My String: %s", nearestSprite->getName().c_str());
        //CCLOG("Found nearest sprite!");
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            DesignControler::get()->setChosen(nearestSprite);

        }
        else {
            DesignControler::get()->displayBox(nearestSprite);
        }
        return;
    }
    nearestSprite = nullptr;
    minDistance = FLT_MAX;
    for (Sprite* sprite : DesignControler::get()->board) {
        float distance = sprite->getPosition().distance(targetPos);
        if (distance < minDistance) {
            minDistance = distance;
            nearestSprite = sprite;
        }
    }
    if (minDistance < 30) {
        DesignControler::get()->putBox(nearestSprite);
        //CCLOG("My String: %s", nearestSprite->getName().c_str());
        //CCLOG("Found nearest sprite!");
        return;
    }
    if (DesignControler::get()->l->getPosition().distance(targetPos) < 30) {
        if (DesignControler::get()->size > 1) {
            DesignControler::get()->size--;
            DesignControler::get()->size_dis->setString(std::to_string(DesignControler::get()->size));
        }
    }
    else if (DesignControler::get()->r->getPosition().distance(targetPos) < 30) {
        if (DesignControler::get()->size < 9) {
            DesignControler::get()->size++;
            DesignControler::get()->size_dis->setString(std::to_string(DesignControler::get()->size));
        }
    }

}
void DesignLayer::onMouseMove(EventMouse* event) {
    // 获取鼠标当前位置
    Vec2 mousePos = event->getLocationInView();
    mousePos = Director::getInstance()->convertToGL(mousePos);
    // 更新物体位置为鼠标位置
    mousePos.y = Director::getInstance()->getVisibleSize().height - mousePos.y;
    if (DesignControler::get()->chosen) {
        DesignControler::get()->chosen->setPosition(mousePos);
    }
}

