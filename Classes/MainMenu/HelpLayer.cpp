#include "HelpLayer.h"

#include "SysMenuScene.h"

Scene* HelpLayer::scene()
{
    Scene* scene = Scene::create();
    HelpLayer* levelLayer = HelpLayer::create();
    scene->addChild(levelLayer);
    return scene;
}

bool HelpLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size winSize = Director::getInstance()->getWinSize();

    auto backGround = Sprite::create("MainMenu/MainBG.png");

    backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    addChild(backGround, 0);

    MenuItemFont::setFontSize(20);
    MenuItemFont::setFontName("Arial");

    std::string path = "MainMenu/help.png";
    auto helpItem = MenuItemImage::create(path, path);
    helpItem->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    addChild(helpItem, 1);


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



