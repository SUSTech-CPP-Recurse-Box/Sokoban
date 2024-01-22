#include "GameScene.h"
#include "MainMenu/LevelSelectLayer.h"
#include "Boxes/controler.h"
#include "Boxes/Panel.h"
#include "Tools/SaveManager.h"
#include "AudioEngine.h"
#define DEFAULT_SPACE_SIZE 10


Scene* GameScene::scene(int lid, bool saved)
{
    Scene* scene = Scene::create();
    //todo:readfile

    controler::get()->init(lid);
    controler::get()->needLoad = saved;

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
    id = "1";
    Size winSize = Director::getInstance()->getWinSize();

    auto backGround = Sprite::create("MainMenu/MainBG.png");
    backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    log("x:%lf;y:%lf", winSize.width / 2, winSize.height / 2);
    addChild(backGround, 0);

    controler::get()->draw(this, 400);
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
    _listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    _listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    mouseListener = EventListenerMouse::create();
    mouseListener->onMouseScroll = CC_CALLBACK_1(GameScene::onMouseScroll, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


    auto levelTitle = Label::createWithTTF("Sokoban~", "fonts/Marker Felt.ttf", 48);
    levelTitle->setPosition(Vec2(winSize.width / 2,
        winSize.height - levelTitle->getContentSize().height));
    this->addChild(levelTitle, 1);

    MenuItemFont::setFontSize(20);
    MenuItemFont::setFontName("Arial");

    Vector<MenuItem*> optItems;
    Label* saveLabel = Label::createWithTTF("Save", "fonts/Marker Felt.ttf", 48);
    saveLabel->setColor(Color3B(31, 45, 150));
    MenuItemLabel* saveItem = MenuItemLabel::create(saveLabel,
        [&](Ref* sender) {
            controler* con = controler::get();
            SaveManager::getInstance()->saveGame(con->lid, con->mv);
        });
    optItems.pushBack(saveItem);

    Label* undoLabel = Label::createWithTTF("Undo", "fonts/Marker Felt.ttf", 48);
    undoLabel->setColor(Color3B(31, 45, 150));
    MenuItemLabel* undoItem = MenuItemLabel::create(undoLabel,
        CC_CALLBACK_1(GameScene::onUndo, this)
    );
    optItems.pushBack(undoItem);

    Label* restartLabel = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 48);
    restartLabel->setColor(Color3B(31, 45, 150));
    MenuItemLabel* restartItem = MenuItemLabel::create(restartLabel,
        CC_CALLBACK_1(GameScene::onRestart, this)
    );
    optItems.pushBack(restartItem);

    Label* back = Label::createWithTTF("Go back", "fonts/Marker Felt.ttf", 48);
    back->setColor(Color3B(31, 45, 150));
    MenuItemLabel* backMain = MenuItemLabel::create(back,
        [&](Ref* sender) {
            Scene* scene = LevelSelectLayer::scene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
        });
    optItems.pushBack(backMain);

    Menu* optMenu = Menu::createWithArray(optItems);
    optMenu->alignItemsHorizontallyWithPadding(100);
    optMenu->setPosition(Vec2(winSize.width / 2, 48));
    this->addChild(optMenu, 1);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::getmove), 1.0f);

    SaveInfo* info = SaveManager::getInstance()->info;
    if (info) {
        controler::get()->reload(info->actions);
    }




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

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W: {
        AudioEngine::preload("Music/move.mp3");

        // 播放背景音乐，-1 表示无限循环
        int bgmId = AudioEngine::play2d("Music/move.mp3", false);
        controler::get()->move({ 0, 1 });
        log("go up");
        break;
    }
    case EventKeyboard::KeyCode::KEY_S: {
        AudioEngine::preload("Music/move.mp3");

        // 播放背景音乐，-1 表示无限循环
        int bgmId = AudioEngine::play2d("Music/move.mp3", false);
        controler::get()->move({ 0, -1 });
        log("go down");
        break;
    }
    case EventKeyboard::KeyCode::KEY_A: {
        AudioEngine::preload("Music/move.mp3");

        // 播放背景音乐，-1 表示无限循环
        int bgmId = AudioEngine::play2d("Music/move.mp3", false);
        controler::get()->move({ -1,0 });
        log("go left");
        break;
    }
    case EventKeyboard::KeyCode::KEY_D: {
        AudioEngine::preload("Music/move.mp3");

        // 播放背景音乐，-1 表示无限循环
        int bgmId = AudioEngine::play2d("Music/move.mp3", false);
        controler::get()->move({ 1, 0 });
        log("go right");
        break;
    }
    case EventKeyboard::KeyCode::KEY_R: {
        this->onRestart(this);
        break;
    }
    case EventKeyboard::KeyCode::KEY_BACKSPACE: {
        this->onUndo(this);
        break;
    }
    }
}
void GameScene::onMouseScroll(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e)
    {
        float deltaY = e->getScrollY();
        controler::get()->magnify(-deltaY * 10);
        log("Mouse scrolled: %f", deltaY);
    }
}

void GameScene::onUndo(Ref* pSender) {
    AudioEngine::preload("Music/move.mp3");

    // 播放背景音乐，-1 表示无限循环
    int bgmId = AudioEngine::play2d("Music/move.mp3", false);
    int lid = controler::get()->lid;
    std::vector<pii> steps = controler::get()->mv;

    if (SaveManager::getInstance()->info == nullptr) {
        SaveManager::getInstance()->info = new SaveInfo(lid, steps, "");
    }

    Scene* scene = GameScene::scene(SaveManager::getInstance()->info->level_id, true);
    Director::getInstance()->replaceScene(TransitionFade::create(0, scene));
}


void GameScene::onRestart(Ref* pSender) {
    int lid = controler::get()->lid;

    Scene* scene = GameScene::scene(lid, false);
    Director::getInstance()->replaceScene(TransitionFade::create(0, scene));
}

void  GameScene::onMouseDown(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e)
    {

        startPos = Vec2(e->getCursorX(), e->getCursorY());

        log("Mouse button pressed at (%.2f, %.2f)", startPos.x, startPos.y);
    }
}

void  GameScene::onMouseUp(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e)
    {
        Vec2 endPos = Vec2(e->getCursorX(), e->getCursorY());

        float distance = startPos.distance(endPos);

        log("Mouse button released at (%.2f, %.2f). Distance moved: %.2f", endPos.x, endPos.y, distance);
    }
}
void GameScene::gm(network::HttpClient* sender, network::HttpResponse* response) {
    if (!response) {
        CCLOG("HttpRequest failed!");
        return;
    }

    long statusCode = response->getResponseCode();

    if (statusCode == 200) {
        // 如果响应状态码为200，表示请求成功
        CCLOG("HttpRequest succeeded!");

        // 获取响应数据
        std::vector<char>* buffer = response->getResponseData();
        std::string responseData(buffer->begin(), buffer->end());

        // 在这里解析服务器返回的数据
        for (int i = 0; i < responseData.size(); i++) {
            controler::get()->move1({ responseData[i++] - '1',responseData[i] - '1' });
        }
    }
    else {
        // 请求失败，输出错误信息
        CCLOG("HttpRequest failed. Status code: %ld", statusCode);
    }
}
void GameScene::getmove(float dt) {
    // 创建一个HttpRequest对象
    network::HttpRequest* request = new network::HttpRequest();
    // 设置请求的URL
    request->setUrl("http://10.24.50.187:9092/cpp/get?c=" + id);
    // 设置请求方式为POST
    request->setRequestType(network::HttpRequest::Type::POST);

    // 构造要发送的数据
    std::string postData = "121321323";
    // 设置请求体
    request->setRequestData(postData.c_str(), postData.length());

    // 设置回调函数，处理服务器的响应
    request->setResponseCallback(CC_CALLBACK_2(GameScene::gm, this));

    // 发送请求
    network::HttpClient::getInstance()->send(request);
    // 释放HttpRequest对象，避免内存泄漏
    request->release();
}


