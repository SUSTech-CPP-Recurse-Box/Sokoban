#include "controler.h"
#include "AudioEngine.h"
controler* controler::_instance = new controler();

controler* controler::get() {
    return _instance;
}

controler::controler() {
    big = nullptr;
    player = nullptr;
};

controler::~controler() {
};

void controler::init(int lid) {
    MyColor::setseed();
    this->lid = lid;
    Panel* panel = Panel::getInstance();
    panel->levelInit(lid);
    suc = false;
    needLoad = false;
    big = nullptr;
    player = nullptr;
    gs = nullptr;
    mv.clear();
    boxes.clear();
    boxeslist.clear();
    //===============================
    player = panel->player;

    if (player->father) {
        if (player->father->father) {
            big = player->father->father;
        }
        else {
            big = player->father;
        }
    }
    else {
        big = panel->boxes[0];
    }
    for (int i = 0; i < panel->boxes.size(); i++) {
        boxeslist.push_back(panel->boxes[i]);
    }
    if (!panel->epss.empty()) {
        ResBox::eps = panel->epss[0];
        boxeslist.push_back(panel->epss[0]);
    }
    if (!panel->infs.empty()) {
        ResBox::inf = panel->infs[0];
        boxeslist.push_back(panel->infs[0]);
    }
    ResBox::blank = new ResBox(1, { 5,5 });
    ResBox::big = big;
    ResBox::player = player;
}

void controler::initPanel(Sprite* fa, double size, pii s, Color3B color, ResBox* rb) {
    for (int i = 0; i < s.first; i++) {
        for (int j = 0; j < s.second; j++) {
            Sprite* sp = Sprite::create("MainMenu/boxes/panel.png");
            sp->setColor(color);
            sp->setContentSize(Size(size, size));
            sp->setPosition(Vec2((2 * i - s.first + 1) * size / 2, -(s.second - 2 * j - 1) * size / 2));
            //log("x:%lf;y:%lf", (2 * i - s.first + 1) * size , -(s.second - 2 * j - 1) * size );
            fa->addChild(sp);
            boxes.push_back(sp);
        }
    }
    for (int i = 0; i < rb->target_box.size(); i++) {
        Sprite* sp = Sprite::create("MainMenu/boxes/target_box.png");
        sp->setColor(color);
        sp->setContentSize(Size(size, size));
        sp->setPosition(Vec2((2 * rb->target_box[i].first - s.first + 1) * size / 2, -(s.second - 2 * rb->target_box[i].second - 1) * size / 2));
        //log("x:%lf;y:%lf", (2 * rb->target_box[i].first - s.first + 1) * size, -(s.second - 2 * rb->target_box[i].second - 1) * size);
        fa->addChild(sp);
        boxes.push_back(sp);
    }
    for (int i = 0; i < rb->target_people.size(); i++) {
        Sprite* sp = Sprite::create("MainMenu/boxes/traget_player.png");
        sp->setColor(color);
        sp->setContentSize(Size(size, size));
        sp->setPosition(Vec2((2 * rb->target_people[i].first - s.first + 1) * size / 2, -(s.second - 2 * rb->target_people[i].second - 1) * size / 2));
        //log("x:%lf;y:%lf", (2 * rb->target_people[i].first - s.first + 1) * size, -(s.second - 2 * rb->target_people[i].second - 1) * size);
        fa->addChild(sp);
        boxes.push_back(sp);
    }
}
void controler::draw(GameScene* gs, double size) {
    if (boxes.size() != 0) {
        boxes[0]->removeAllChildren();
        boxes[0]->removeFromParent();
        boxes.clear();
    }
    this->gs = gs;
    this->size = size;
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* s = Sprite::create();
    boxes.push_back(s);
    s->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    s->setColor(big->color);
    gs->addChild(s);
    Sprite* board = Sprite::create("MainMenu/boxes/around.png");
    board->setPosition(Vec2(0, 0));
    board->setContentSize(Size(size * 1.02, size * 1.02));
    board->setColor(big->color);
    s->addChild(board);
    initPanel(s, size / big->size.first, big->size, big->color, big);
    for (int i = 0; i < big->size.first; i++) {
        for (int j = 0; j < big->size.second; j++) {
            if (big->son[i][j]) {//绘图需要：颜色：来自物体，大小：来自父亲，传入，位置：来自父亲
                double new_size = size / big->size.first;
                Vec2 v = Vec2((2 * (i)-big->size.first + 1) * new_size / 2, -(big->size.second - 2 * (j)-1) * new_size / 2);
                draw(new_size, big->son[i][j], s, v);
            }
        }
    }
}

void controler::draw(double size, ResBox* draw, Sprite* father, Vec2 pos) {
    if (draw->type == 2 || draw->type == 3 || draw->type == 4) {

        Sprite* s;
        if (draw->type == 4) {
            s = Sprite::create("MainMenu/boxes/boundary.png");
            s->setColor(father->getColor());
        }
        else if (draw->type == 3) {
            s = Sprite::create("MainMenu/boxes/player.png");
            s->setColor(Color3B(255, 165, 0));

        }
        else {
            s = Sprite::create("MainMenu/boxes/default_box.png");
            s->setColor(Color3B(127, 255, 212));
        }
        s->setPosition(pos);
        s->setContentSize(Size(size, size));
        father->addChild(s);
        boxes.push_back(s);
    }
    else {
        Sprite* s = Sprite::create();
        s->setPosition(pos);
        s->setColor(draw->color);
        father->addChild(s);
        boxes.push_back(s);
        Sprite* board = Sprite::create("MainMenu/boxes/around.png");
        board->setPosition(Vec2(0, 0));
        board->setContentSize(Size(size * 1.02, size * 1.02));
        board->setColor(draw->color);
        s->addChild(board);
        initPanel(s, size / draw->size.first, draw->size, draw->color, draw);
        if (size < 0.1) {
            return;
        }
        for (int i = 0; i < draw->size.first; i++) {
            for (int j = 0; j < draw->size.second; j++) {
                if (draw->son[i][j]) {//绘图需要：颜色：来自物体，大小：来自父亲，传入，位置：来自父亲
                    double new_size = size / draw->size.first;
                    Vec2 v = Vec2((2 * (i)-draw->size.first + 1) * new_size / 2, -(draw->size.second - 2 * (j)-1) * new_size / 2);
                    controler::draw(new_size, draw->son[i][j], s, v);
                }
            }
        }
    }
}

bool controler::success() {
    int s = 1;
    for (int i = 0; i < boxeslist.size(); i++) {
        for (int j = 0; j < boxeslist[i]->target_box.size(); j++) {
            pii p = boxeslist[i]->target_box[j];
            if (!boxeslist[i]->son[p.first][p.second]) {
                s = 0;
                break;
            }
            if (boxeslist[i]->son[p.first][p.second]->type != 1 && boxeslist[i]->son[p.first][p.second]->type != 2) {
                s = 0;
                break;
            }
        }
        if (s == 0) {
            break;
        }
    }
    for (int i = 0; i < boxeslist.size(); i++) {
        for (int j = 0; j < boxeslist[i]->target_people.size(); j++) {
            pii p = boxeslist[i]->target_people[j];
            if (!boxeslist[i]->son[p.first][p.second]) {
                s = 0;
                break;
            }
            if (boxeslist[i]->son[p.first][p.second]->type != 3) {
                s = 0;
                break;
            }
        }
        if (s == 0) {
            break;
        }
    }
    if (s == 1) {
        log("success========================");
        suc = true;
        Size winSize = Director::getInstance()->getWinSize();
        auto levelTitle = Label::createWithTTF("Success!", "fonts/Marker Felt.ttf", 48);
        levelTitle->setPosition(Vec2(winSize.width / 2,
            winSize.height / 2));

        gs->addChild(levelTitle);

        // 停止并释放背景音乐
        //cocos2d::AudioEngine::stopAll();
        // 预加载背景音乐
        AudioEngine::preload("Music/success.mp3");

        // 播放背景音乐，-1 表示无限循环
        int bgmId = AudioEngine::play2d("Music/success.mp3", false);
        return true;
    }
    return false;

}

void controler::move(pii dir) {
    gs->trymove(std::to_string(dir.first+1) + std::to_string(dir.second+1));
    if (!suc) {
        player->father->processObjects(player, player->father, player->father, dir, player->pos, 0, player, player->pos, { 1,1 }, nullptr, 0);
        //if (big != player->father) {
        big = player->father;
        if (player->father->father) {
            big = player->father->father;
        }
        //}

        draw(gs, size);
        mv.push_back(dir);
        std::vector<pii> stepRec(mv);
        if (SaveManager::getInstance()->info != nullptr) {
            delete SaveManager::getInstance()->info;
            SaveManager::getInstance()->info = nullptr;

        }
        SaveManager::getInstance()->info = new SaveInfo(this->lid, {}, "");
        for (int i = 0; i < mv.size() - 1; ++i) {
            SaveManager::getInstance()->info->actions.push_back(mv[i]);
        };
        success();
    }
}
void controler::move1(pii dir) {
    if (!suc) {
        player->father->processObjects(player, player->father, player->father, dir, player->pos, 0, player, player->pos, { 1,1 }, nullptr, 0);
        //if (big != player->father) {
        big = player->father;
        if (player->father->father) {
            big = player->father->father;
        }
        //}

        draw(gs, size);
        mv.push_back(dir);
        std::vector<pii> stepRec(mv);
        if (SaveManager::getInstance()->info != nullptr) {
            delete SaveManager::getInstance()->info;
            SaveManager::getInstance()->info = nullptr;

        }
        SaveManager::getInstance()->info = new SaveInfo(this->lid, {}, "");
        for (int i = 0; i < mv.size() - 1; ++i) {
            SaveManager::getInstance()->info->actions.push_back(mv[i]);
        };
        success();
    }
}
void controler::reload(std::vector<pii> step) {
    if (this->needLoad) {
        for (int i = 0; i < step.size(); i++) {
            move(step[i]);
        }
    }
}

void controler::magnify(double a) {
    size += a;
    draw(gs, size);
}

//bool controler::processObject(ResBox* cur, pii dir) {
//	ResBox* curFather = cur->father;
//	if (cur->father == nullptr) {
//		return false;
//	}

//	if (cur->pos.first == 0) {

//	}
//}