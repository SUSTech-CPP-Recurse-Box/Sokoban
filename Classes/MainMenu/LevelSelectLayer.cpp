#include "SysMenuScene.h"
#include "../GameFrame/GameScene.h"
#include "LevelSelectLayer.h"


Scene* LevelSelectLayer::scene()
{
    Scene* scene = Scene::create();
    LevelSelectLayer* levelLayer = LevelSelectLayer::create();
    scene->addChild(levelLayer);
    return scene;
}

bool LevelSelectLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size winSize = Director::getInstance()->getWinSize();

    auto backGround = Sprite::create("MainMenu/MainBG.png");

    backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    addChild(backGround, 0);

    auto levelTitle = Label::createWithTTF("Level Select", "fonts/Marker Felt.ttf", 48);
    levelTitle->setPosition(Vec2(winSize.width / 2,
        winSize.height - levelTitle->getContentSize().height));

    this->addChild(levelTitle, 1);


    MenuItemFont::setFontSize(20);
    MenuItemFont::setFontName("Arial");


    auto title1 = MenuItemFont::create("Sound");
    title1->setFontSize(26);
    title1->setFontName("Arial");
    title1->setEnabled(false);
    title1->setColor(Color3B(31, 45, 150));


    Vector<MenuItem*> levels;
    for (size_t i = 1; i <= 10; ++i)
    {
        std::string path = "MainMenu/levels/";
        //path += std::to_string(i) +".png";
        path += "1.png";
        auto levelItem = MenuItemImage::create(
            path,
            path,
            CC_CALLBACK_1(LevelSelectLayer::onLevelSelect, this, i));
        levels.pushBack(levelItem);
    }
    Menu* levelsLayerMenu = Menu::createWithArray(levels);
    levelsLayerMenu->alignItemsInColumns(3,3,4);
    levelsLayerMenu->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    addChild(levelsLayerMenu, 1);

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


void LevelSelectLayer::onLevelSelect(Ref* pSender, int lid)
{
    CCLOG("Select %d", lid);
    Scene* scene = GameScene::scene(lid);
    Director::getInstance()->replaceScene(TransitionFade::create(1.2f, scene));
}

