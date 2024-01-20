#include "LoadLayer.h"
#include "SysMenuScene.h"
#include "GameFrame/GameScene.h"
#include "Tools/SaveManager.h"

using namespace std;

Scene* LoadLayer::scene()
{
    Scene* scene = Scene::create();
    LoadLayer* loadLayer = LoadLayer::create();
    scene->addChild(loadLayer);
    return scene;
}

bool LoadLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }


    Size winSize = Director::getInstance()->getWinSize();

    auto backGround = Sprite::create("MainMenu/MainBG.png");

    backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    addChild(backGround, 0);

    auto loadTitle = Label::createWithTTF("Load Game", "fonts/Marker Felt.ttf", 48);
    loadTitle->setPosition(Vec2(winSize.width / 2,
        winSize.height - loadTitle->getContentSize().height));

    this->addChild(loadTitle, 1);


    MenuItemFont::setFontSize(20);
    MenuItemFont::setFontName("Arial");

    SaveInfo* levelInfo = SaveManager::getInstance()->loadGame();

    if (levelInfo != nullptr) {
        Vector<MenuItem*> saveInfos;
        Label* level_id_label = Label::createWithTTF("Level ID: " + to_string(levelInfo->level_id), "fonts/Marker Felt.ttf", 48);
        auto idItem = MenuItemLabel::create(level_id_label);
        saveInfos.pushBack(idItem);

        //level_id_label->setPosition(Vec2(winSize.width / 2,
        //    winSize.height - level_id_label->getContentSize().height - 48));
        //this->addChild(level_id_label, 1);

        std::string path = "MainMenu/levels/" + std::to_string(levelInfo->level_id) + ".png";
        auto imgItem = MenuItemImage::create(path, path);
        saveInfos.pushBack(imgItem);

        Label* moved_step_label = Label::createWithTTF("Steps Moved: " + to_string(levelInfo->actions.size()), "fonts/Marker Felt.ttf", 48);
        auto stepsItem = MenuItemLabel::create(moved_step_label);
        saveInfos.pushBack(stepsItem);

        Label* level_time_label = Label::createWithTTF("Save Time: " + levelInfo->time_str, "fonts/Marker Felt.ttf", 48);
        auto timeItem = MenuItemLabel::create(level_time_label);
        saveInfos.pushBack(timeItem);

        Menu* levelsInfoMenu = Menu::createWithArray(saveInfos);
        levelsInfoMenu->alignItemsInColumns(1, 1, 1, 1);
        levelsInfoMenu->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        addChild(levelsInfoMenu, 1);

        Label* playGame = Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 48);

        playGame->setColor(Color3B(31, 45, 150));
        MenuItemLabel* playGameAction = MenuItemLabel::create(playGame,
            CC_CALLBACK_1(LoadLayer::onLoad, this));
        Menu* playMenu = Menu::create(playGameAction, nullptr);
        playMenu->setPosition(Vec2(winSize.width / 2, 96 + 10));
        addChild(playMenu, 1);
    }
    else {
        Label* missing = Label::createWithTTF("File Missing or Broken!", "fonts/Marker Felt.ttf", 48);

        missing->setPosition(Vec2(winSize.width / 2,
            winSize.height - missing->getContentSize().height - 200));

        this->addChild(missing, 1);
    }


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

void LoadLayer::onLoad(Ref* pSender) {
    SaveInfo* info = SaveManager::getInstance()->info;
    if (info != nullptr) {
        Scene* scene = GameScene::scene(info->level_id, true);
        Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
    }
}


